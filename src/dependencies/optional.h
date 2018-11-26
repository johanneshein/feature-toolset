#ifndef SDK_FEATURE_TOOLSET_DEPENDENCIES_OPTIONAL_H_
#define SDK_FEATURE_TOOLSET_DEPENDENCIES_OPTIONAL_H_

#include <string>

#include "dependency.h"

class Optional : public Dependency
{
    public:

        virtual bool checkCondition(void);

        virtual std::string getDotEgdeLabel(void);

        virtual std::string getDotArrowType(void);
};

#endif // SDK_FEATURE_TOOLSET_DEPENDENCIES_OPTIONAL_H_
