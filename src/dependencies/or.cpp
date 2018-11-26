#include "dependencies/or.h"
#include "feature.h"

bool OR::checkCondition(void)
{
    int count = 0;

    for (auto it=_features.begin(); it!=_features.end(); ++it)
    {
        if ((*it)->isSelected()) count++;
    }

    if (count >= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string OR::getDotEgdeLabel(void)
{
    return ">0";
}

std::string OR::getDotArrowType(void)
{
    return "none";
}
