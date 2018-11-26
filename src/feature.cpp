#include "analyzer.h"
#include "feature.h"
#include "utils/log.h"

#include <typeinfo> /* typeid() */
#include <algorithm> /* remove_if() */
#include <cctype> /* isdigit() */

Feature::Feature() :
    _selected(false),
    _plausible(true)
{
    /*
     * This is a very clever solution for complex problem.
     * Without this line, shared_from_this() will failure!
     */
    auto wptr = std::shared_ptr<Feature>( this, [](Feature*){} );

    Analyzer::getInstance().addFeature(shared_from_this());
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
        Log().Get(ERROR) << "Feature '" << this->getName() << "' was already selected.";
        return false;
    }
    else
    {
        Log().Get(DEBUG) << "Feature '" << this->getName() << "' is now selected.";
        _selected = true;
        return true;
    }
}

bool Feature::isPlausible(void)
{
    return _plausible;
}

bool Feature::markAsProblematic(void)
{
    if (this->isPlausible())
    {
        Log().Get(DEBUG) << "Feature '" << this->getName() << "' has unmet conditions.";
        _plausible = false;
        return true;
    }
    else
    {
        Log().Get(ERROR) << "Feature '" << this->getName() << "' was already marked.";
        return false;
    }
}

std::string Feature::getName(void)
{
    std::string name_of_typeid = typeid(*this).name();
    name_of_typeid.erase(remove_if(name_of_typeid.begin(), name_of_typeid.end(), [](char c) { return isdigit(c); } ), name_of_typeid.end());

    return name_of_typeid;
}

void Feature::addDependency(dependency_ptr d)
{
    _dependencies.push_front(d);
}

std::list<dependency_ptr>& Feature::getDependencies(void)
{
    return _dependencies;
}
