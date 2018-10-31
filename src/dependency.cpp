#include "analyzer.h"
#include "dependency.h"

Dependency::Dependency()
{
    Analyzer::getInstance().addDependency(this);
}

Dependency::~Dependency()
{
}

bool Dependency::addFeature(Feature* f)
{
    _features.push_front(f);
}

std::list<Feature*> Dependency::getFeatures(void)
{
    return _features;
}

bool Dependency::checkCondition(void)
{
    return false;
}
