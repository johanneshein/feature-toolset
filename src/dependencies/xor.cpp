#include "dependencies/xor.h"
#include "feature.h"

bool XOR::checkCondition(void)
{
    int count = 0;

    for (auto it=_features.begin(); it!=_features.end(); ++it)
    {
        if ((*it)->isSelected()) count++;
    }

    if (count == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string XOR::getDotEgdeLabel(void)
{
    return "=1";
}

std::string XOR::getDotArrowType(void)
{
    return "none";
}
