#pragma once
#include <dzaction.h>
#include <dznode.h>
#include <dzjsonwriter.h>
#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>
#include <DzBridgeAction.h>
#include "DzPlaygroundsDialog.h"

class UnitTest_DzPlaygroundsAction;

#include "dzbridge.h"

class DzPlaygroundsAction : public DZ_BRIDGE_NAMESPACE::DzBridgeAction {
	 Q_OBJECT
	 Q_PROPERTY(bool InstallUnityFiles READ getInstallUnityFiles WRITE setInstallUnityFiles)
public:
	DzPlaygroundsAction();

	// Override DzBridgeAction: Pre-Process Scene data to workaround FbxExporter issues, called by Export() before FbxExport operation.
	bool preProcessScene(DzNode* parentNode = nullptr);
	// Override DzBridgeAction: Undo changes made by preProcessScene(), called by Export() after FbxExport operation.
	bool undoPreProcessScene();

	void setInstallUnityFiles(bool arg) { m_bInstallUnityFiles = arg; }
	bool getInstallUnityFiles() { return m_bInstallUnityFiles; }

protected:
	 bool m_bInstallUnityFiles;
	 bool m_bUndoTPose;

	 void executeAction();
	 Q_INVOKABLE bool createUI();
	 Q_INVOKABLE void writeConfiguration();
	 Q_INVOKABLE void setExportOptions(DzFileIOSettings& ExportOptions);
	 Q_INVOKABLE QString createUnityFiles(bool replace = true);
	 QString readGuiRootFolder();

#ifdef UNITTEST_DZBRIDGE
	friend class UnitTest_DzPlaygroundsAction;
#endif

};
