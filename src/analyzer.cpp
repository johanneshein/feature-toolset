#include "analyzer.h"
#include "dependency.h"
#include "feature.h"
#include "selection_handler/xml.h"
#include "visualizer/dot.h"

Analyzer& Analyzer::getInstance(void)
{
    /*
     * _instance is guaranteed to be destroyed.
     * It will be instantiated on first use.
     */
    static Analyzer _instance;

    return _instance;
}

Analyzer::Analyzer() :
    _selectionHandler(new XMLSelectionHandler("project.xml")),
    _visualizer(new DotVisualizer("feature_model.gv", "feature_model.ps"))
{
}

Analyzer::~Analyzer()
{
}

bool Analyzer::addFeature(feature_ptr f)
{
    _features.push_front(f);

    return true;
}

bool Analyzer::addDependency(dependency_ptr d)
{
    _dependencies.push_front(d);

    return true;
}

std::list<feature_ptr>& Analyzer::getAllDetectedFeatures(void)
{
    return _features;
}

bool Analyzer::loadFeatureSelection(void)
{
    return _selectionHandler->loadSelection(_features);
}

bool Analyzer::saveFeatureSelection(void)
{
    return _selectionHandler->saveSelection(_features);
}

bool Analyzer::checkDependencies(void)
{
    std::list<feature_ptr> RootFeatures;

    bool Erfolg = determineRootFeatures(RootFeatures);

    if (Erfolg)
    {
        for (auto it1=RootFeatures.begin(); it1!=RootFeatures.end(); ++it1)
        {
            traverseSPLDefinition(Erfolg, *it1);
        }
    }

    return Erfolg;
}

bool Analyzer::generateFeatureModelGraph(void)
{
    std::list<feature_ptr> RootFeatures;

    bool Erfolg = determineRootFeatures(RootFeatures);

    if (Erfolg)
    {
        return _visualizer->generateFeatureModel(RootFeatures);
    }
    else
    {
        return false;
    }
}

bool Analyzer::showFeatureModelGraph(void)
{
    return _visualizer->showFeatureModel();
}

bool Analyzer::determineRootFeatures(std::list<feature_ptr>& inputReference)
{
    for (auto it1=_features.begin(); it1!=_features.end(); ++it1)
    {
        bool found = true;

        feature_ptr feature = *it1;

        for (auto it2=_dependencies.begin(); it2!=_dependencies.end(); ++it2)
        {
            dependency_ptr dep = *it2;

            std::list<feature_ptr>& dependentFeatures = dep->getFeatures();

            for (auto it3=dependentFeatures.begin(); it3!=dependentFeatures.end(); ++it3)
            {
                feature_ptr dependentFeature = *it3;

                if (feature->getName().compare(dependentFeature->getName()) == 0)
                {
                    found = false;
                }
            }
        }

        if (found)
        {
            inputReference.push_front(feature);
        }
    }

    if (inputReference.size() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Analyzer::traverseSPLDefinition(bool& plausible, const feature_ptr& f)
{
    std::list<dependency_ptr>& featureDependencies = f->getDependencies();

    for (auto it=featureDependencies.begin(); it!=featureDependencies.end(); ++it)
    {
        dependency_ptr d = *it;

        if ((f->isSelected()) && !d->checkCondition())
        {
            d->markAsProblematic();
            plausible = false;
        }

        std::list<feature_ptr>& dependentFeatures = d->getFeatures();

        for (auto it3=dependentFeatures.begin(); it3!=dependentFeatures.end(); ++it3)
        {
            feature_ptr dependentFeature = *it3;

            if (((dependentFeature->isSelected()) && (!d->checkCondition())) || ((f->isSelected()) && (!d->checkCondition())))
            {
                dependentFeature->markAsProblematic();
                plausible = false;
            }

            if ((dependentFeature->isSelected()) && (!f->isSelected()))
            {
                f->markAsProblematic();
                plausible = false;
            }

            traverseSPLDefinition(plausible, dependentFeature);
        }
    }
}
