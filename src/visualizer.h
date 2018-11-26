#ifndef SDK_FEATURE_TOOLSET_VISUALIZER_H_
#define SDK_FEATURE_TOOLSET_VISUALIZER_H_

#include "feature_ptr.h"

#include <list>

class Visualizer
{
    public:

        Visualizer();
        ~Visualizer();

        virtual bool generateFeatureModel(std::list<feature_ptr>& RootFeatures) = 0;
        virtual bool showFeatureModel(void) = 0;
};

#endif // SDK_FEATURE_TOOLSET_VISUALIZER_H_
