#include "dependencies/mandatory.h"
#include "feature.h"

bool Mandatory::checkCondition(void)
{
        int count = 0;

        for (auto it=_features.begin(); it!=_features.end(); ++it)
        {
                if ((*it)->isSelected()) count++;
        }

        if (count == _features.size()) return true;
        else                           return false;
}