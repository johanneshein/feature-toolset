#ifndef SDK_FEATURE_TOOLSET_ANALYZER_H_
#define SDK_FEATURE_TOOLSET_ANALYZER_H_

#include "dependency_fwd.h"
#include "feature_fwd.h"

#include <list>
#include <sstream> /* std::stringstream */

class Analyzer
{
    public:

        static Analyzer& getInstance(void);

        bool addFeature(Feature* f);
        bool addDependency(Dependency* d);

        bool checkDependencies(void);

        bool generateFeatureModelGraph(void);
        bool showFeatureModelGraph(void);

    protected:

        std::list<Feature*> _features;
        std::list<Dependency*> _dependencies;

    private:

        /*
         * Since this class is designed as a singleton pattern, the class's
         * constructor and destructor are private. The external access to our instantiated
         * object will be exclusively done via getInstance().
         */
        Analyzer();
        ~Analyzer();

        /*
         * Don't forget to declare a private copy and assignment constructor.
         * (The compiler can create some automatically if not defined but used anywhere.)
         * You want to make sure they are unacceptable otherwise you may accidentally
         * get copies of your singleton appearing.
         * Thus, do not implement them! Then you will get some compile errors if you try
         * to get copies of your singleton.
         */
        Analyzer(const Analyzer& a);
        void operator=(const Analyzer& a);

        bool traverseSPLDefinition(std::stringstream& ss, Feature* f);
};

#endif // SDK_FEATURE_TOOLSET_ANALYZER_H_
