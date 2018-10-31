#ifndef SDK_FEATURE_TOOLSET_DEPENDENCIES_XOR_H_
#define SDK_FEATURE_TOOLSET_DEPENDENCIES_XOR_H_

#include "dependency.h"

class XOR : public Dependency
{
        public:
                virtual bool checkCondition(void);
};

#endif // SDK_FEATURE_TOOLSET_DEPENDENCIES_XOR_H_