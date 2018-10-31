#ifndef SDK_FEATURE_TOOLSET_DEPENDENCIES_OR_H_
#define SDK_FEATURE_TOOLSET_DEPENDENCIES_OR_H_

#include "dependency.h"

class OR : public Dependency
{
        public:
                virtual bool checkCondition(void);
};

#endif // SDK_FEATURE_TOOLSET_DEPENDENCIES_OR_H_