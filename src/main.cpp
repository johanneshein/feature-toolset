#include "analyzer.h"

#include "dependency_ptr.h"

#include "dependencies/mandatory.h"
#include "dependencies/optional.h"
#include "dependencies/or.h"
#include "dependencies/xor.h"

#include "feature_ptr.h"

#include "features/amd_athlon.h"
#include "features/hid.h"
#include "features/intel_i7.h"
#include "features/laufwerk.h"
#include "features/mainboard.h"
#include "features/maus.h"
#include "features/pc.h"
#include "features/prozessor.h"
#include "features/tastatur.h"

#include "utils/log.h"

#include <iostream> /* cin, cout */

int main(int argc, char* argv[])
{
    Log().Get(DEBUG) << "Define SPL";

    feature_ptr pc       (new PC);
    feature_ptr laufwerke(new Laufwerk);
    feature_ptr mainboard(new Mainboard);
    feature_ptr prozessor(new Prozessor);
    feature_ptr i7       (new Intel_I7);
    feature_ptr athlon   (new AMD_Athlon);
    feature_ptr hid      (new HID);
    feature_ptr tastatur (new Tastatur);
    feature_ptr maus     (new Maus);

    dependency_ptr m1(new Mandatory);
    m1->addFeature(laufwerke);
    pc->addDependency(m1);

    dependency_ptr m2(new Mandatory);
    m2->addFeature(mainboard);
    m2->addFeature(prozessor);
    pc->addDependency(m2);

    dependency_ptr m3(new Optional);
    m3->addFeature(hid);
    pc->addDependency(m3);

    dependency_ptr or1(new OR);
    or1->addFeature(tastatur);
    or1->addFeature(maus);
    hid->addDependency(or1);

    dependency_ptr xor2(new XOR);
    xor2->addFeature(i7);
    xor2->addFeature(athlon);
    prozessor->addDependency(xor2);

    Log().Get(DEBUG) << "Load SPL selection";
    Analyzer::getInstance().loadFeatureSelection();

    Log().Get(DEBUG) << "Make some SPL selections";

    std::cout << "Bitte wählen Sie die detektierten Features mit 'j' oder 'n' aus:" << std::endl;

    std::list<feature_ptr>& detected_feature_list = Analyzer::getInstance().getAllDetectedFeatures();

    std::string benutzer_eingabe;

    for (auto it=detected_feature_list.begin(); it!=detected_feature_list.end(); ++it)
    {
        feature_ptr detected_feature = *it;

        std::cout << detected_feature->getName() << "? (j/n) ";
        std::cin  >> benutzer_eingabe;

        if (benutzer_eingabe.compare("j") == 0)
        {
            detected_feature->select();
        }
    }

    Log().Get(DEBUG) << "Storage SPL selection";
    Analyzer::getInstance().saveFeatureSelection();

    if (Analyzer::getInstance().checkDependencies())
    {
        Log().Get(DEBUG) << "All feature conditions are met.";
    }
    else
    {
        Log().Get(WARNING) << "There are some unmet feature conditions!";
    }

    Log().Get(DEBUG) << "Generate feature model graph";
    Analyzer::getInstance().generateFeatureModelGraph();

    Log().Get(DEBUG) << "Show generated feature model graph";
    Analyzer::getInstance().showFeatureModelGraph();

    return 0;
}
