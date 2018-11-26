#ifndef SDK_FEATURE_TOOLSET_ANALYZER_H_
#define SDK_FEATURE_TOOLSET_ANALYZER_H_

#include "dependency_ptr.h"
#include "feature_ptr.h"
#include "selection_handler_ptr.h"
#include "visualizer_ptr.h"

#include <list>

class Analyzer
{
    public:

        static Analyzer& getInstance(void);

        bool addFeature(feature_ptr f);
        bool addDependency(dependency_ptr d);

        std::list<feature_ptr>& getAllDetectedFeatures(void);

        bool loadFeatureSelection(void);
        bool saveFeatureSelection(void);

        bool checkDependencies(void);

        bool generateFeatureModelGraph(void);
        bool showFeatureModelGraph(void);

    private:

        std::list<feature_ptr> _features;
        std::list<dependency_ptr> _dependencies;

        selection_handler_ptr _selectionHandler;

        visualizer_ptr _visualizer;

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

        bool determineRootFeatures(std::list<feature_ptr>& inputReference);

        void traverseSPLDefinition(bool& plausible, const feature_ptr& f);
};

#endif // SDK_FEATURE_TOOLSET_ANALYZER_H_
