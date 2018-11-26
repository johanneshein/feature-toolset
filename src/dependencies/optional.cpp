#include "dependencies/optional.h"
#include "feature.h"

bool Optional::checkCondition(void)
{
    return true;
}

std::string Optional::getDotEgdeLabel(void)
{
    return "";
}

std::string Optional::getDotArrowType(void)
{
    return "odot";
}
