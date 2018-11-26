#ifndef SDK_FEATURE_TOOLSET_VISUALIZER_DOT_H_
#define SDK_FEATURE_TOOLSET_VISUALIZER_DOT_H_

#include "visualizer.h"

#include <list>
#include <string>
#include <sstream> /* std::stringstream */

class DotVisualizer : public Visualizer
{
    public:

        DotVisualizer(std::string GraphDescriptionFile, std::string PostScriptFile);
        ~DotVisualizer();

        virtual bool generateFeatureModel(std::list<feature_ptr>& RootFeatures);
        virtual bool showFeatureModel(void);

    private:

        std::string _GraphDescriptionFile;
        std::string _PostScriptFile;

        bool traverseSPLDefinition(std::stringstream& ss, const feature_ptr& f);
};

#endif // SDK_FEATURE_TOOLSET_VISUALIZER_DOT_H_
