#include "analyzer.h"
#include "dependency.h"
#include "feature.h"
#include "utils/log.h"

#include <typeinfo> /* typeid() */
#include <cstdlib> /* system() */
#include <string> /* std::string */
#include <fstream> /* std::fstream */

Analyzer& Analyzer::getInstance(void)
{
    /*
     * _instance is guaranteed to be destroyed.
     * It will be instantiated on first use.
     */
    static Analyzer _instance;

    return _instance;
}

Analyzer::Analyzer()
{
}

Analyzer::~Analyzer()
{
}

bool Analyzer::addFeature(Feature* f)
{
    _features.push_front(f);
}

bool Analyzer::addDependency(Dependency* d)
{
    _dependencies.push_front(d);
}

bool Analyzer::checkDependencies(void)
{
    for (auto it=_dependencies.begin(); it!=_dependencies.end(); ++it)
    {
        if (!((*it)->checkCondition()))
        {
            return false;
        }
    }

    Log().Get(INFO) << "All conditions are met in Analyzer::checkDependencies.";

    return true;
}

bool Analyzer::traverseSPLDefinition(std::stringstream& ss, Feature* f)
{
    for (auto it=f->getDependencies().begin(); it!=f->getDependencies().end(); ++it)
    {
        Dependency* d = *it;

        for (auto it2=d->getFeatures().begin(); it2!=d->getFeatures().end(); ++it2)
        {
            Feature* dependentFeature = *it2;

            ss << typeid(f).name() << " -> " << typeid(dependentFeature).name() << ";\n";
        }
    }

    return true;
}

bool Analyzer::generateFeatureModelGraph(void)
{
    Log().Get(INFO) << "Generate the feature model graph.";

    bool ok = true;
    std::stringstream ss;

    ss << "digraph G {\n";

    for (auto it=_features.begin(); it!=_features.end(); ++it)
    {
        ok = traverseSPLDefinition(ss, *it);
    }

    ss << "}\n";

    if (ok)
    {
        std::fstream* fs = new std::fstream();

        fs->open("graph.gv", std::ios::out | std::ios::trunc);

        if (fs->is_open())
        {
            std::string content = ss.str();
            fs->write(&content[0], content.size());
            fs->close();
        }

        delete fs;

        system("dot -Tps graph.gv -o graph.ps");
    }

    return ok;
}

bool Analyzer::showFeatureModelGraph(void)
{
    system("evince graph.ps");

    return false;
}
