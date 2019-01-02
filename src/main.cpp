#include "analyzer.h"

#include "dependency_ptr.h"

#include "dependencies/mandatory.h"
#include "dependencies/optional.h"
#include "dependencies/or.h"
#include "dependencies/xor.h"

#include "feature_ptr.h"

#include "features/amd_athlon.h"
#include "features/blueray.h"
#include "features/dvd.h"
#include "features/hdd.h"
#include "features/hid.h"
#include "features/intel_i7.h"
#include "features/laufwerk.h"
#include "features/mainboard.h"
#include "features/maus.h"
#include "features/pc.h"
#include "features/prozessor.h"
#include "features/ssd.h"
#include "features/tastatur.h"

#include "utils/log.h"

#include <iostream> /* cin, cout */

#define clear() printf("\033[H\033[J")

int main(int argc, char* argv[])
{
    feature_ptr pc       (new PC);
    feature_ptr laufwerke(new Laufwerk);
    feature_ptr blueray  (new Blueray);
    feature_ptr dvd      (new DVD);
    feature_ptr hdd      (new HDD);
    feature_ptr ssd      (new SSD);
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

    dependency_ptr or2(new OR);
    or2->addFeature(blueray);
    or2->addFeature(dvd);
    or2->addFeature(hdd);
    or2->addFeature(ssd);
    laufwerke->addDependency(or2);

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

    char input;

    do
    {
        clear();

        std::cout << "FEATURE TOOLSET C++" << std::endl;
        std::cout << "-------------------" << std::endl;
        std::cout << "Optionen:" << std::endl;
        std::cout << "(1) Load SPL selection" << std::endl;
        std::cout << "(2) Make SPL selections" << std::endl;
        std::cout << "(3) Check selection" << std::endl;
        std::cout << "(4) Save SPL selection" << std::endl;
        std::cout << "(5) Generate and show feature model" << std::endl;
        std::cout << "(q) Quit" << std::endl;
        std::cout << "Ihre Auswahl: ";

        std::cin  >> input;

        std::list<feature_ptr>& detected_feature_list = Analyzer::getInstance().getAllDetectedFeatures();;
        feature_ptr detected_feature;
        std::string benutzer_eingabe;

        switch (input)
        {
            case '1':
                Analyzer::getInstance().loadFeatureSelection();
                break;

            case '2':
                clear();

                std::cout << "FEATURE TOOLSET C++" << std::endl;
                std::cout << "-------------------" << std::endl;
                std::cout << "Bitte wählen Sie die detektierten Features mit 'j' oder 'n' aus:" << std::endl;

                for (auto it=detected_feature_list.begin(); it!=detected_feature_list.end(); ++it)
                {
                    detected_feature = *it;

                    std::cout << detected_feature->getName() << "? (j/n) ";
                    std::cin  >> benutzer_eingabe;

                    if (benutzer_eingabe.compare("j") == 0)
                    {
                        detected_feature->select();
                    }
                }
                break;

            case '3':
                if (Analyzer::getInstance().checkDependencies())
                {
                    Log().Get(DEBUG) << "All feature conditions are met.";
                }
                else
                {
                    Log().Get(WARNING) << "There are some unmet feature conditions!";
                }
                break;

            case '4':
                Analyzer::getInstance().saveFeatureSelection();
                break;

            case '5':
                Analyzer::getInstance().checkDependencies();
                Analyzer::getInstance().generateFeatureModelGraph();
                Analyzer::getInstance().showFeatureModelGraph();
                break;
        }

    }
    while(input != 'q');

    return 0;
}
