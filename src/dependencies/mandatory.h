#ifndef SDK_FEATURE_TOOLSET_DEPENDENCIES_MANDATORY_H_
#define SDK_FEATURE_TOOLSET_DEPENDENCIES_MANDATORY_H_

#include "dependency.h"

class Mandatory : public Dependency
{
    public:

        virtual bool checkCondition(void);
};

#endif // SDK_FEATURE_TOOLSET_DEPENDENCIES_MANDATORY_H_
