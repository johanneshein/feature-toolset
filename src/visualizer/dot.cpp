#include "dependency.h"
#include "feature.h"
#include "utils/log.h"
#include "visualizer/dot.h"

#include <cstdlib> /* system() */
#include <fstream> /* std::fstream */

DotVisualizer::DotVisualizer(std::string GraphDescriptionFile, std::string PostScriptFile) :
    _GraphDescriptionFile(GraphDescriptionFile),
    _PostScriptFile(PostScriptFile)
{
}

DotVisualizer::~DotVisualizer()
{
}

bool DotVisualizer::traverseSPLDefinition(std::stringstream& ss, const feature_ptr& f)
{
    auto dependency_list = f->getDependencies();

    if (!f->isPlausible() && f->isSelected())
    {
        ss << f->getName() << " [color = \"#FF00FF\"];\n";
    }
    else if (!f->isPlausible())
    {
        ss << f->getName() << " [color = \"#FF0000\"];\n";
    }
    else if (f->isSelected())
    {
        ss << f->getName() << " [color = \"#0000FF\"];\n";
    }

    Log().Get(DEBUG) << "Feature " << f->getName() << " has " << dependency_list.size() << " dependencies.";

    for (auto it=dependency_list.begin(); it!=dependency_list.end(); ++it)
    {
        dependency_ptr d = *it;

        auto feature_list = d->getFeatures();

        for (auto it2=feature_list.begin(); it2!=feature_list.end(); ++it2)
        {
            feature_ptr dependentFeature = *it2;

            std::string arrowhead = "";

            if (d->getDotArrowType().compare("normal") != 0)
            {
                arrowhead += "arrowhead = \"";
                arrowhead += d->getDotArrowType();
                arrowhead += "\"";
            }

            std::string label = "";

            if (d->getDotEgdeLabel().size() > 0)
            {
                label += "label = \"";
                label += d->getDotEgdeLabel();
                label += "\"";
            }

            std::string color = "";

            if (!d->isPlausible() && dependentFeature->isSelected())
            {
                color += "color = \"#FF00FF\"";
            }
            else if (!d->isPlausible())
            {
                color += "color = \"#FF0000\"";
            }
            else if (dependentFeature->isSelected())
            {
                color += "color = \"#0000FF\"";
            }

            ss << f->getName() << " -> " << dependentFeature->getName() << " [ " << arrowhead << " " << label << " " << color << " ];\n";

            traverseSPLDefinition(ss, dependentFeature);
        }
    }

    return true;
}

bool DotVisualizer::generateFeatureModel(std::list<feature_ptr>& RootFeatures)
{
    bool ok = true;
    std::stringstream ss;

    ss << "digraph G {\n";

    for (auto it=RootFeatures.begin(); it!=RootFeatures.end(); ++it)
    {
        feature_ptr root_feature = *it;

        ok &= traverseSPLDefinition(ss, root_feature);
    }

    ss << "}\n";

    if (ok)
    {
        std::fstream* fs = new std::fstream();

        fs->open(_GraphDescriptionFile, std::ios::out | std::ios::trunc);

        if (fs->is_open())
        {
            std::string content = ss.str();
            fs->write(&content[0], content.size());
            fs->close();
        }

        delete fs;
    }

    if (ok)
    {
        std::stringstream command;

        command << "dot -Tps " << _GraphDescriptionFile << " -o " << _PostScriptFile;

        system(command.str().c_str());
    }

    return ok;
}

bool DotVisualizer::showFeatureModel(void)
{
    std::stringstream command;

    command << "evince " << _PostScriptFile;

    system(command.str().c_str());

    return true;
}
