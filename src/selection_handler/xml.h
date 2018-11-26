#ifndef SDK_FEATURE_TOOLSET_SELECTIONHANDLER_XML_H_
#define SDK_FEATURE_TOOLSET_SELECTIONHANDLER_XML_H_

#include "selection_handler.h"

class XMLSelectionHandler : public SelectionHandler
{
    public:

        XMLSelectionHandler(std::string SelectionFile);
        ~XMLSelectionHandler();

        virtual bool loadSelection(std::list<feature_ptr>& feature_list);
        virtual bool saveSelection(const std::list<feature_ptr>& feature_list);

};

#endif // SDK_FEATURE_TOOLSET_SELECTIONHANDLER_XML_H_
