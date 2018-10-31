#include "analyzer.h"

#include "dependencies/mandatory.h"
#include "dependencies/optional.h"
#include "dependencies/or.h"
#include "dependencies/xor.h"

#include "features/amd_athlon.h"
#include "features/intel_i7.h"
#include "features/laufwerk.h"
#include "features/mainboard.h"
#include "features/pc.h"
#include "features/prozessor.h"

#include "utils/log.h"

int main(int argc, char* argv[])
{
    Log().Get(INFO) << "START FEATURE TOOLSET";

    Log().Get(DEBUG) << "Define SPL";

    PC* pc = new PC();

    Laufwerk* laufwerke = new Laufwerk();
    Mainboard* mainboard = new Mainboard();
    Prozessor* prozessor = new Prozessor();

    Intel_I7*   i7     = new Intel_I7();
    AMD_Athlon* athlon = new AMD_Athlon();

    Dependency* m1 = new Mandatory();
    m1->addFeature(laufwerke);

    pc->addDependency(m1);

    Dependency* m2 = new Mandatory();
    m2->addFeature(mainboard);
    m2->addFeature(prozessor);

    pc->addDependency(m2);

    Dependency* xor2 = new XOR();
    xor2->addFeature(i7);
    xor2->addFeature(athlon);

    prozessor->addDependency(xor2);

    Log().Get(DEBUG) << "Load SPL selection";
    // TODO with libxml++

    Log().Get(DEBUG) << "Make some SPL selections";
    // TODO with command line tool
    pc->select();
    laufwerke->select();
    mainboard->select();
    prozessor->select();

    Log().Get(DEBUG) << "Storage SPL selection";
    // TODO with libxml++

    Log().Get(DEBUG) << "Generate feature model graph";
    Analyzer::getInstance().generateFeatureModelGraph();
    Analyzer::getInstance().showFeatureModelGraph();

    return 0;
}
