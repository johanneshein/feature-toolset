#include "feature.h"
#include "selection_handler/xml.h"
#include "utils/file.h"
#include "utils/log.h"

#include <libxml++/libxml++.h>
#include <iostream>

XMLSelectionHandler::XMLSelectionHandler(std::string SelectionFile) :
    SelectionHandler(SelectionFile)
{
}

XMLSelectionHandler::~XMLSelectionHandler()
{
}

/*
void print_node(const xmlpp::Node* node, unsigned int indentation = 0)
{
  const Glib::ustring indent(indentation, ' ');
  std::cout << std::endl; //Separate nodes by an empty line.

  const auto nodeContent = dynamic_cast<const xmlpp::ContentNode*>(node);
  const auto nodeText = dynamic_cast<const xmlpp::TextNode*>(node);
  const auto nodeComment = dynamic_cast<const xmlpp::CommentNode*>(node);

  if(nodeText && nodeText->is_white_space()) //Let's ignore the indenting - you don't always want to do this.
    return;

  const auto nodename = node->get_name();

  if(!nodeText && !nodeComment && !nodename.empty()) //Let's not say "name: text".
  {
    const auto namespace_prefix = node->get_namespace_prefix();

    std::cout << indent << "Node name = ";
    if(!namespace_prefix.empty())
      std::cout << namespace_prefix << ":";
    std::cout << nodename << std::endl;
  }
  else if(nodeText) //Let's say when it's text. - e.g. let's say what that white space is.
  {
    std::cout << indent << "Text Node" << std::endl;
  }

  //Treat the various node types differently:
  if(nodeText)
  {
    std::cout << indent << "text = \"" << nodeText->get_content() << "\"" << std::endl;
  }
  else if(nodeComment)
  {
    std::cout << indent << "comment = " << nodeComment->get_content() << std::endl;
  }
  else if(nodeContent)
  {
    std::cout << indent << "content = " << nodeContent->get_content() << std::endl;
  }
  else if(const xmlpp::Element* nodeElement = dynamic_cast<const xmlpp::Element*>(node))
  {
    //A normal Element node:

    //line() works only for ElementNodes.
    std::cout << indent << "     line = " << node->get_line() << std::endl;

    //Print attributes:
    for (const auto& attribute : nodeElement->get_attributes())
    {
      const auto namespace_prefix = attribute->get_namespace_prefix();

      std::cout << indent << "  Attribute ";
      if(!namespace_prefix.empty())
        std::cout << namespace_prefix << ":";
        std::cout << attribute->get_name() << " = "
                << attribute->get_value() << std::endl;
    }

    const auto attribute = nodeElement->get_attribute("title");
    if(attribute)
    {
      std::cout << indent;
      if (dynamic_cast<const xmlpp::AttributeNode*>(attribute))
        std::cout << "AttributeNode ";
      else if (dynamic_cast<const xmlpp::AttributeDeclaration*>(attribute))
        std::cout << "AttributeDeclaration ";
      std::cout << "title = " << attribute->get_value() << std::endl;
    }
  }

  if(!nodeContent)
  {
    //Recurse through child nodes:
    for(const auto& child : node->get_children())
    {
      print_node(child, indentation + 2); //recursive
    }
  }
}
*/

bool XMLSelectionHandler::loadSelection(std::list<feature_ptr>& feature_list)
{
    if (fileExists(_File))
    {
        try
        {
            bool validate = false;
            bool set_throw_messages = false;
            bool throw_messages = false;
            bool substitute_entities = true;
            bool include_default_attributes = false;

            xmlpp::DomParser parser;

            if (validate)
            {
                parser.set_validate();
            }

            if (set_throw_messages)
            {
                parser.set_throw_messages(throw_messages);
            }

            parser.set_substitute_entities(substitute_entities);

            parser.set_include_default_attributes(include_default_attributes);

            parser.parse_file(_File);

            const auto pRootNode = parser.get_document()->get_root_node();

            const auto NodeSet = pRootNode->find("//feature");

            Log().Get(DEBUG) << "Features found: " << NodeSet.size();

            for (auto it=NodeSet.begin(); it!=NodeSet.end(); ++it)
            {
                xmlpp::Node* featureNode = *it;

                const xmlpp::Element* featureElement = dynamic_cast<const xmlpp::Element*>(featureNode);

                if (featureElement)
                {
                    for (auto it=feature_list.begin(); it!=feature_list.end(); ++it)
                    {
                        feature_ptr feature = *it;

                        if (feature->getName().compare(featureElement->get_first_child_text()->get_content()) == 0)
                        {
                            if (featureElement->get_attribute_value("selected").compare("1") == 0)
                            {
                                if (!feature->select())
                                {
                                    Log().Get(ERROR) << "Das Feature '" << feature->getName() << "' wurde bereits selektiert.";
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
        catch (const std::exception& ex)
        {
            Log().Get(ERROR) << "Exception caught: " << ex.what();
            return false;
        }
    }
    else
    {
        try
        {
            xmlpp::Document doc;

            const auto root = doc.create_root_node("project");

            const auto name = root->add_child_element("name");
            name->add_child_text("Feature Toolset C++");

            const auto features = root->add_child_element("features");

            for (auto it=feature_list.begin(); it!=feature_list.end(); ++it)
            {
                feature_ptr f = *it;

                const auto added_feature_xml = features->add_child_element("feature");
                added_feature_xml->set_attribute("selected", "0");
                added_feature_xml->add_child_text(f->getName());
            }

            doc.write_to_file_formatted(_File);
        }
        catch (const std::exception& ex)
        {
            Log().Get(ERROR) << "Exception caught: " << ex.what();
            return false;
        }
    }

    return true;
}

bool XMLSelectionHandler::saveSelection(const std::list<feature_ptr>& feature_list)
{
    if (fileExists(_File))
    {
        try
        {
            bool validate = false;
            bool set_throw_messages = false;
            bool throw_messages = false;
            bool substitute_entities = true;
            bool include_default_attributes = false;

            xmlpp::DomParser parser;

            if (validate)
            {
                parser.set_validate();
            }

            if (set_throw_messages)
            {
                parser.set_throw_messages(throw_messages);
            }

            parser.set_substitute_entities(substitute_entities);

            parser.set_include_default_attributes(include_default_attributes);

            parser.parse_file(_File);

            const auto doc = parser.get_document();

            const auto pRootNode = doc->get_root_node();

            const auto NodeSet = pRootNode->find("//feature");

            const auto NodeSetForAdding = pRootNode->find("//features");

            Log().Get(DEBUG) << "Features found: " << NodeSet.size();
            Log().Get(DEBUG) << "NodeSetForAdding size: " << NodeSetForAdding.size();

            for (auto it=feature_list.begin(); it!=feature_list.end(); ++it)
            {
                feature_ptr feature = *it;
                bool featureFound = false;

                for (auto it=NodeSet.begin(); it!=NodeSet.end(); ++it)
                {
                    xmlpp::Node* featureNode = *it;

                    xmlpp::Element* featureElement = dynamic_cast<xmlpp::Element*>(featureNode);

                    if (featureElement)
                    {
                        if (feature->getName().compare(featureElement->get_first_child_text()->get_content()) == 0)
                        {
                            featureFound = true;

                            if (feature->isSelected())
                            {
                                featureElement->set_attribute("selected", "1");
                            }
                            else
                            {
                                featureElement->set_attribute("selected", "0");
                            }
                        }
                    }
                }

                if (!featureFound)
                {
                    xmlpp::Element* features = dynamic_cast<xmlpp::Element*>(NodeSetForAdding.front());

                    const auto added_feature_xml = features->add_child_element("feature");

                    if (feature->isSelected())
                    {
                        added_feature_xml->set_attribute("selected", "1");
                    }
                    else
                    {
                        added_feature_xml->set_attribute("selected", "0");
                    }

                    added_feature_xml->add_child_text(feature->getName());
                }
            }

            doc->write_to_file_formatted(_File);
        }
        catch (const std::exception& ex)
        {
            Log().Get(ERROR) << "Exception caught: " << ex.what();
            return false;
        }
    }
    else
    {
        try
        {
            xmlpp::Document doc;

            const auto root = doc.create_root_node("project");

            const auto name = root->add_child_element("name");
            name->add_child_text("Feature Toolset C++");

            const auto features = root->add_child_element("features");

            for (auto it=feature_list.begin(); it!=feature_list.end(); ++it)
            {
                feature_ptr f = *it;

                const auto added_feature_xml = features->add_child_element("feature");

                if (f->isSelected())
                {
                    added_feature_xml->set_attribute("selected", "1");
                }
                else
                {
                    added_feature_xml->set_attribute("selected", "0");
                }

                added_feature_xml->add_child_text(f->getName());
            }

            doc.write_to_file_formatted(_File);
        }
        catch (const std::exception& ex)
        {
            Log().Get(ERROR) << "Exception caught: " << ex.what();
            return false;
        }
    }

    return true;
}
