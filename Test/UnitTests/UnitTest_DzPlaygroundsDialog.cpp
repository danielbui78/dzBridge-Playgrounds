#ifdef UNITTEST_DZBRIDGE

#include "UnitTest_DzPlaygroundsDialog.h"
#include "DzPlaygroundsDialog.h"


UnitTest_DzPlaygroundsDialog::UnitTest_DzPlaygroundsDialog()
{
	m_testObject = (QObject*) new DzPlaygroundsDialog();
}

bool UnitTest_DzPlaygroundsDialog::runUnitTests()
{
	RUNTEST(_DzBridgeUnityDialog);
	RUNTEST(getAssetsFolderEdit);
	RUNTEST(resetToDefaults);
	RUNTEST(loadSavedSettings);
	RUNTEST(HandleSelectAssetsFolderButton);
	RUNTEST(HandleInstallUnityFilesCheckBoxChange);
	RUNTEST(HandleAssetTypeComboChange);
	RUNTEST(HandleAssetFolderChanged);

	return true;
}

bool UnitTest_DzPlaygroundsDialog::_DzBridgeUnityDialog(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	TRY_METHODCALL(new DzPlaygroundsDialog());
	return bResult;
}

bool UnitTest_DzPlaygroundsDialog::getAssetsFolderEdit(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	TRY_METHODCALL(qobject_cast<DzPlaygroundsDialog*>(m_testObject)->getAssetsFolderEdit());
	return bResult;
}

bool UnitTest_DzPlaygroundsDialog::resetToDefaults(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	TRY_METHODCALL(qobject_cast<DzPlaygroundsDialog*>(m_testObject)->resetToDefaults());
	return bResult;
}

bool UnitTest_DzPlaygroundsDialog::loadSavedSettings(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	TRY_METHODCALL(qobject_cast<DzPlaygroundsDialog*>(m_testObject)->loadSavedSettings());
	return bResult;
}

bool UnitTest_DzPlaygroundsDialog::HandleSelectAssetsFolderButton(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	TRY_METHODCALL(qobject_cast<DzPlaygroundsDialog*>(m_testObject)->HandleSelectAssetsFolderButton());
	return bResult;
}

bool UnitTest_DzPlaygroundsDialog::HandleInstallUnityFilesCheckBoxChange(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	TRY_METHODCALL(qobject_cast<DzPlaygroundsDialog*>(m_testObject)->HandleInstallUnityFilesCheckBoxChange(0));
	return bResult;
}

bool UnitTest_DzPlaygroundsDialog::HandleAssetTypeComboChange(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	TRY_METHODCALL(qobject_cast<DzPlaygroundsDialog*>(m_testObject)->HandleAssetTypeComboChange(0));
	return bResult;
}

bool UnitTest_DzPlaygroundsDialog::HandleAssetFolderChanged(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	TRY_METHODCALL(qobject_cast<DzPlaygroundsDialog*>(m_testObject)->HandleAssetFolderChanged(""));
	return bResult;
}



#include "moc_UnitTest_DzPlaygroundsDialog.cpp"
#endif