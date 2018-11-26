#ifndef SDK_FEATURE_TOOLSET_DEPENDENCIES_XOR_H_
#define SDK_FEATURE_TOOLSET_DEPENDENCIES_XOR_H_

#include <string>

#include "dependency.h"

class XOR : public Dependency
{
    public:

        virtual bool checkCondition(void);

        virtual std::string getDotEgdeLabel(void);

        virtual std::string getDotArrowType(void);
};

#endif // SDK_FEATURE_TOOLSET_DEPENDENCIES_XOR_H_
