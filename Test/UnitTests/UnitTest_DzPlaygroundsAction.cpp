#ifdef UNITTEST_DZBRIDGE

#include "UnitTest_DzPlaygroundsAction.h"
#include "DzPlaygroundsAction.h"


UnitTest_DzPlaygroundsAction::UnitTest_DzPlaygroundsAction()
{
	m_testObject = (QObject*) new DzPlaygroundsAction();
}

bool UnitTest_DzPlaygroundsAction::runUnitTests()
{
	RUNTEST(_DzBridgeUnityAction);
	RUNTEST(setInstallUnityFiles);
	RUNTEST(getInstallUnityFiles);
	RUNTEST(executeAction);
	RUNTEST(createUI);
	RUNTEST(writeConfiguration);
	RUNTEST(setExportOptions);
	RUNTEST(createUnityFiles);
	RUNTEST(readGuiRootFolder);

	return true;
}

bool UnitTest_DzPlaygroundsAction::_DzBridgeUnityAction(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	TRY_METHODCALL(new DzPlaygroundsAction());
	return bResult;
}

bool UnitTest_DzPlaygroundsAction::setInstallUnityFiles(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	TRY_METHODCALL(qobject_cast<DzPlaygroundsAction*>(m_testObject)->setInstallUnityFiles(false));
	return bResult;
}

bool UnitTest_DzPlaygroundsAction::getInstallUnityFiles(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	TRY_METHODCALL(qobject_cast<DzPlaygroundsAction*>(m_testObject)->getInstallUnityFiles());
	return bResult;
}

bool UnitTest_DzPlaygroundsAction::executeAction(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	TRY_METHODCALL(qobject_cast<DzPlaygroundsAction*>(m_testObject)->executeAction());
	return bResult;
}

bool UnitTest_DzPlaygroundsAction::createUI(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	TRY_METHODCALL(qobject_cast<DzPlaygroundsAction*>(m_testObject)->createUI());
	return bResult;
}

bool UnitTest_DzPlaygroundsAction::writeConfiguration(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	TRY_METHODCALL(qobject_cast<DzPlaygroundsAction*>(m_testObject)->writeConfiguration());
	return bResult;
}

bool UnitTest_DzPlaygroundsAction::setExportOptions(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	DzFileIOSettings arg;
	TRY_METHODCALL(qobject_cast<DzPlaygroundsAction*>(m_testObject)->setExportOptions(arg));
	return bResult;
}

bool UnitTest_DzPlaygroundsAction::createUnityFiles(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	TRY_METHODCALL(qobject_cast<DzPlaygroundsAction*>(m_testObject)->createUnityFiles());
	return bResult;
}

bool UnitTest_DzPlaygroundsAction::readGuiRootFolder(UnitTest::TestResult* testResult)
{
	bool bResult = true;
	TRY_METHODCALL(qobject_cast<DzPlaygroundsAction*>(m_testObject)->readGuiRootFolder());
	return bResult;
}


#include "moc_UnitTest_DzPlaygroundsAction.cpp"

#endif