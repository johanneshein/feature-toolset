#include "analyzer.h"
#include "feature.h"
#include "utils/log.h"

#include <typeinfo>

Feature::Feature() :
    _selected(false)
{
    Analyzer::getInstance().addFeature(this);
}

Feature::~Feature()
{
}

bool Feature::isSelected(void)
{
    return _selected;
}

bool Feature::select(void)
{
    if (this->isSelected())
    {
        Log().Get(ERROR) << "This feature '" << typeid(this).name() << "' was already selected.";
        return false;
    }
    else
    {
        Log().Get(INFO) << "The feature '" << typeid(this).name() << "' is now selected.";
        _selected = true;
        return true;
    }
}

void Feature::addDependency(Dependency* d)
{
    _dependencies.push_front(d);
}

std::list<Dependency*> Feature::getDependencies(void)
{
    return _dependencies;
}
