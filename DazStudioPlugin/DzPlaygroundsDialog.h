#pragma once
#include "dzbasicdialog.h"
#include <QtGui/qcombobox.h>
#include <QtCore/qsettings.h>
#include <DzBridgeDialog.h>

class QPushButton;
class QLineEdit;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QWidget;
class DzPlaygroundsAction;

class UnitTest_DzPlaygroundsDialog;

#include "dzbridge.h"

class DzPlaygroundsDialog : public DZ_BRIDGE_NAMESPACE::DzBridgeDialog{
	friend DzPlaygroundsAction;
	Q_OBJECT
	Q_PROPERTY(QWidget* assetsFolderEdit READ getAssetsFolderEdit)
public:
	Q_INVOKABLE QLineEdit* getAssetsFolderEdit() { return assetsFolderEdit; }

	/** Constructor **/
	 DzPlaygroundsDialog(QWidget *parent=nullptr);

	/** Destructor **/
	virtual ~DzPlaygroundsDialog() {}

	Q_INVOKABLE void resetToDefaults();

protected slots:
	void HandleSelectAssetsFolderButton();
	void HandleInstallUnityFilesCheckBoxChange(int state);
	void HandleAssetTypeComboChange(int state);
	void HandleAssetFolderChanged(const QString& directoryName);

protected:
	Q_INVOKABLE bool loadSavedSettings();

	QLineEdit* projectEdit;
	QPushButton* projectButton;
	QLineEdit* assetsFolderEdit;
	QPushButton* assetsFolderButton;

	QLabel* installOrOverwriteUnityFilesLabel;
	QCheckBox* installUnityFilesCheckBox;

#ifdef UNITTEST_DZBRIDGE
	friend class UnitTest_DzPlaygroundsDialog;
#endif
};
