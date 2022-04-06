#include <QtGui/qcheckbox.h>
#include <QtGui/QMessageBox>
#include <QtNetwork/qudpsocket.h>
#include <QtNetwork/qabstractsocket.h>
#include <QCryptographicHash>
#include <QtCore/qdir.h>

#include <dzapp.h>
#include <dzscene.h>
#include <dzmainwindow.h>
#include <dzshape.h>
#include <dzproperty.h>
#include <dzobject.h>
#include <dzpresentation.h>
#include <dznumericproperty.h>
#include <dzimageproperty.h>
#include <dzcolorproperty.h>
#include <dpcimages.h>

#include "QtCore/qmetaobject.h"
#include "dzmodifier.h"
#include "dzgeometry.h"
#include "dzweightmap.h"
#include "dzfacetshape.h"
#include "dzfacetmesh.h"
#include "dzfacegroup.h"
#include "dzprogress.h"
#include "dzcontentmgr.h"
#include "dzundostack.h"

#include "DzPlaygroundsAction.h"
#include "DzPlaygroundsDialog.h"
#include "DzBridgeMorphSelectionDialog.h"
#include "DzBridgeSubdivisionDialog.h"

#ifdef WIN32
#include <shellapi.h>
#endif

#include "dzbridge.h"

DzPlaygroundsAction::DzPlaygroundsAction() :
	DzBridgeAction(tr("&Playgrounds"), tr("Send the selected node to Playgrounds."))
{
	m_nNonInteractiveMode = 0;
	m_sAssetType = QString("SkeletalMesh");
	//Setup Icon
	QString iconName = "icon";
	QPixmap basePixmap = QPixmap::fromImage(getEmbeddedImage(iconName.toLatin1()));
	QIcon icon;
	icon.addPixmap(basePixmap, QIcon::Normal, QIcon::Off);
	QAction::setIcon(icon);

	m_bUndoTPose = false;
}

bool DzPlaygroundsAction::preProcessScene(DzNode* parentNode)
{
	// 2022-Mar-14 (DB): Apply G8-Tpose
	DzContentMgr* contentMgr = dzApp->getContentMgr();
	QString srcPath = ":/DazBridgePlaygrounds/g8-tpose.duf";
	QString tempPath = dzApp->getTempPath() + "/" + "g8-tpose.duf";
	QFile srcFile(srcPath);
	// copy to temp folder and merge tpose into scene
	if (srcFile.exists())
	{
		this->copyFile(&srcFile, &tempPath, true);
		if (contentMgr->openFile(tempPath, true))
		{
			m_bUndoTPose = true;
		}
		else
		{
			m_bUndoTPose = false;
		}
	}

	DzBridgeAction::preProcessScene(parentNode);

	return false;
}

bool DzPlaygroundsAction::undoPreProcessScene()
{
	DzBridgeAction::undoPreProcessScene();

	// undo the t-pose
	if (m_bUndoTPose)
	{
		dzUndoStack->undo();
	}

	return false;
}

bool DzPlaygroundsAction::createUI()
{
	// Check if the main window has been created yet.
	// If it hasn't, alert the user and exit early.
	DzMainWindow* mw = dzApp->getInterface();
	if (!mw)
	{
		if (m_nNonInteractiveMode == 0) QMessageBox::warning(0, tr("Error"),
			tr("The main window has not been created yet."), QMessageBox::Ok);

		return false;
	}

	// m_subdivisionDialog creation REQUIRES valid Character or Prop selected
	if (dzScene->getNumSelectedNodes() != 1)
	{
		if (m_nNonInteractiveMode == 0) QMessageBox::warning(0, tr("Error"),
			tr("Please select one Character or Prop to send."), QMessageBox::Ok);

		return false;
	}

	 // Create the dialog
	if (!m_bridgeDialog)
	{
		m_bridgeDialog = new DzPlaygroundsDialog(mw);
	}
	else
	{
		DzPlaygroundsDialog* playgroundsDialog = qobject_cast<DzPlaygroundsDialog*>(m_bridgeDialog);
		if (playgroundsDialog)
		{
			playgroundsDialog->resetToDefaults();
			playgroundsDialog->loadSavedSettings();
		}
	}

	if (!m_subdivisionDialog) m_subdivisionDialog = DZ_BRIDGE_NAMESPACE::DzBridgeSubdivisionDialog::Get(m_bridgeDialog);
	if (!m_morphSelectionDialog) m_morphSelectionDialog = DZ_BRIDGE_NAMESPACE::DzBridgeMorphSelectionDialog::Get(m_bridgeDialog);

	return true;
}

void DzPlaygroundsAction::executeAction()
{
	// CreateUI() disabled for debugging -- 2022-Feb-25
	/*
		 // Create and show the dialog. If the user cancels, exit early,
		 // otherwise continue on and do the thing that required modal
		 // input from the user.
		 if (createUI() == false)
			 return;
	*/

	// Check if the main window has been created yet.
	// If it hasn't, alert the user and exit early.
	DzMainWindow* mw = dzApp->getInterface();
	if (!mw)
	{
		if (m_nNonInteractiveMode == 0)
		{
			QMessageBox::warning(0, tr("Error"),
				tr("The main window has not been created yet."), QMessageBox::Ok);
		}
		return;
	}

	// Create and show the dialog. If the user cancels, exit early,
	// otherwise continue on and do the thing that required modal
	// input from the user.
	if (dzScene->getNumSelectedNodes() != 1)
	{
		if (m_nNonInteractiveMode == 0)
		{
			QMessageBox::warning(0, tr("Error"),
				tr("Please select one Character or Prop to send."), QMessageBox::Ok);
		}
		return;
	}

	// Create the dialog
	if (m_bridgeDialog == nullptr)
	{
		m_bridgeDialog = new DzPlaygroundsDialog(mw);
	}
	else
	{
		if (m_nNonInteractiveMode == 0)
		{
			m_bridgeDialog->resetToDefaults();
			m_bridgeDialog->loadSavedSettings();
		}
	}

	// Prepare member variables when not using GUI
	if (m_nNonInteractiveMode == 1)
	{
//		if (m_sRootFolder != "") m_bridgeDialog->getIntermediateFolderEdit()->setText(m_sRootFolder);

		if (m_aMorphListOverride.isEmpty() == false)
		{
			m_bEnableMorphs = true;
			m_sMorphSelectionRule = m_aMorphListOverride.join("\n1\n");
			m_sMorphSelectionRule += "\n1\n.CTRLVS\n2\nAnything\n0";
			if (m_morphSelectionDialog == nullptr)
			{
				m_morphSelectionDialog = DZ_BRIDGE_NAMESPACE::DzBridgeMorphSelectionDialog::Get(m_bridgeDialog);
			}
			m_mMorphNameToLabel.clear();
			foreach(QString morphName, m_aMorphListOverride)
			{
				QString label = m_morphSelectionDialog->GetMorphLabelFromName(morphName);
				m_mMorphNameToLabel.insert(morphName, label);
			}
		}
		else
		{
			m_bEnableMorphs = false;
			m_sMorphSelectionRule = "";
			m_mMorphNameToLabel.clear();
		}

	}

	// If the Accept button was pressed, start the export
	int dlgResult = -1;
	if (m_nNonInteractiveMode == 0)
	{
		dlgResult = m_bridgeDialog->exec();
	}
	if (m_nNonInteractiveMode == 1 || dlgResult == QDialog::Accepted)
	{
		// DB 2021-10-11: Progress Bar
		DzProgress* exportProgress = new DzProgress("Sending to Playgrounds...", 10);

		// Read Common GUI values
		readGui(m_bridgeDialog);

		// Read Custom GUI values
		DzPlaygroundsDialog* playgroundsDialog = qobject_cast<DzPlaygroundsDialog*>(m_bridgeDialog);
		if (playgroundsDialog)
			m_bInstallUnityFiles = playgroundsDialog->installUnityFilesCheckBox->isChecked();
		// custom animation filename correction for Unity
		if (m_sAssetType == "Animation")
		{
			if (m_nNonInteractiveMode == 0)
			{
				// correct CharacterFolder
				m_sExportSubfolder = m_sAssetName.left(m_sAssetName.indexOf("@"));
				m_sDestinationPath = m_sRootFolder + "/" + m_sExportSubfolder + "/";
				// correct animation filename
				m_sDestinationFBX = m_sDestinationPath + m_sAssetName + ".fbx";
			}
		}

		//Create Daz3D folder if it doesn't exist
		QDir dir;
		dir.mkpath(m_sRootFolder);
		exportProgress->step();

		exportHD(exportProgress);

		// DB 2021-10-11: Progress Bar
		exportProgress->finish();

		// DB 2021-09-02: messagebox "Export Complete"
		if (m_nNonInteractiveMode == 0)
		{
			QMessageBox::information(0, "DazBridge: Playgrounds",
				tr("Export phase from Daz Studio complete. Please switch to Unity to begin Import phase."), QMessageBox::Ok);
			if (m_bInstallUnityFiles)
			{
				QString destPath = createUnityFiles(true);
#ifdef WIN32
				ShellExecute(0, 0, destPath.toLocal8Bit().data(), 0, 0, SW_SHOW);
#endif
			}
		}

	}
}

QString DzPlaygroundsAction::createUnityFiles(bool replace)
{
	if (!m_bInstallUnityFiles)
		return "";

	QString srcPath = ":/DazBridgePlaygrounds/daztoplaygrounds.unitypackage";
	QFile srcFile(srcPath);
	QString destPath = m_sRootFolder + "/DazToPlaygrounds - Doubleclick to Install.unitypackage";
	this->copyFile(&srcFile, &destPath, replace);
	srcFile.close();

	return destPath;
}

void DzPlaygroundsAction::writeConfiguration()
{
	QString DTUfilename = m_sDestinationPath + m_sAssetName + ".dtu";
	QFile DTUfile(DTUfilename);
	DTUfile.open(QIODevice::WriteOnly);
	DzJsonWriter writer(&DTUfile);
	writer.startObject(true);

	writeDTUHeader(writer);

	if (m_sAssetType.toLower().contains("mesh"))
	{
		writeAllMaterials(m_pSelectedNode, writer);
		writeAllMorphs(writer);
		writeAllSubdivisions(writer);
		writeAllDforceInfo(m_pSelectedNode, writer);
	}

	if (m_sAssetType == "Pose")
	{
		writeAllPoses(writer);
	}

	if (m_sAssetType == "Environment")
	{
		writeEnvironment(writer);
	}

	writer.finishObject();
	DTUfile.close();
}

// Setup custom FBX export options
void DzPlaygroundsAction::setExportOptions(DzFileIOSettings& ExportOptions)
{
	ExportOptions.setBoolValue("doEmbed", false);
	ExportOptions.setBoolValue("doDiffuseOpacity", false);
	ExportOptions.setBoolValue("doCopyTextures", false);

}

QString DzPlaygroundsAction::readGuiRootFolder()
{
	QString rootFolder = QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation) + QDir::separator() + "DazToPlaygrounds";

	if (m_bridgeDialog)
	{
		QLineEdit* assetsFolderEdit = nullptr;
		DzPlaygroundsDialog* playgroundsDialog = qobject_cast<DzPlaygroundsDialog*>(m_bridgeDialog);

		if (playgroundsDialog)
			assetsFolderEdit = playgroundsDialog->getAssetsFolderEdit();

		if (assetsFolderEdit)
			rootFolder = assetsFolderEdit->text().replace("\\", "/") + "/Daz3D";
	}
	return rootFolder;
}

#include "moc_DzPlaygroundsAction.cpp"
