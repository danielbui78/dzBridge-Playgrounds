#include "dzplugin.h"
#include "dzapp.h"

#include "version.h"
#include "DzPlaygroundsAction.h"
#include "DzPlaygroundsDialog.h"

#include "dzbridge.h"

CPP_PLUGIN_DEFINITION("Daz To Playgounds Bridge");

DZ_PLUGIN_AUTHOR("Daz 3D, Inc");

DZ_PLUGIN_VERSION(PLUGIN_MAJOR, PLUGIN_MINOR, PLUGIN_REV, PLUGIN_BUILD);

DZ_PLUGIN_DESCRIPTION(QString(
	"<b>Pre-Release DazToPlaygrounds Bridge v%1.%2.%3.%4 </b><br>\
Bridge Collaboration Project<br><br>\
<a href = \"https://github.com/danielbui78-bridge-collab/\">Github</a><br><br>"
).arg(PLUGIN_MAJOR).arg(PLUGIN_MINOR).arg(PLUGIN_REV).arg(PLUGIN_BUILD));

DZ_PLUGIN_CLASS_GUID(DzPlaygroundsAction, a1e9fbef-0845-4062-9d73-547953f6a68d);
NEW_PLUGIN_CUSTOM_CLASS_GUID(DzPlaygroundsDialog, 31a1eb38-583a-4a3c-b5ce-cbe6140a0fb7);

#ifdef UNITTEST_DZBRIDGE

#include "UnitTest_DzPlaygroundsAction.h"
#include "UnitTest_DzPlaygroundsDialog.h"

DZ_PLUGIN_CLASS_GUID(UnitTest_DzPlaygroundsAction, da10d876-5934-43ae-be8b-db40268ce377);
DZ_PLUGIN_CLASS_GUID(UnitTest_DzPlaygroundsDialog, 7bdf77f1-ff85-4c4c-9512-3f803d05f9ed);

#endif