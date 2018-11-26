#include "analyzer.h"
#include "dependency.h"

Dependency::Dependency() :
    _plausible(true)
{
    /* This is a very clever solution for complex problem. */
    auto wptr = std::shared_ptr<Dependency>( this, [](Dependency*){} );

    Analyzer::getInstance().addDependency(shared_from_this());
}

Dependency::~Dependency()
{
}

bool Dependency::isPlausible(void)
{
    return _plausible;
}

bool Dependency::markAsProblematic(void)
{
    if (this->isPlausible())
    {
        _plausible = false;
        return true;
    }
    else
    {
        return false;
    }
}

bool Dependency::addFeature(feature_ptr f)
{
    _features.push_front(f);

    return true;
}

std::list<feature_ptr>& Dependency::getFeatures(void)
{
    return _features;
}

bool Dependency::checkCondition(void)
{
    return false;
}
