#ifndef SDK_FEATURE_TOOLSET_DEPENDENCY_H_
#define SDK_FEATURE_TOOLSET_DEPENDENCY_H_

#include <list>

#include "feature_fwd.h"

class Dependency
{
    protected:

        std::list<Feature*> _features;

    public:

        Dependency();
        ~Dependency();

        bool addFeature(Feature* f);

        std::list<Feature*> getFeatures(void);

        virtual bool checkCondition(void) = 0;
};

#endif // SDK_FEATURE_TOOLSET_DEPENDENCY_H_
