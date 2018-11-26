#ifndef SDK_FEATURE_TOOLSET_SELECTIONHANDLER_H_
#define SDK_FEATURE_TOOLSET_SELECTIONHANDLER_H_

#include "feature_ptr.h"

#include <string>
#include <list>

class SelectionHandler
{
    public:

        SelectionHandler(const std::string& selectionFile);
        ~SelectionHandler();

        virtual bool loadSelection(std::list<feature_ptr>& featureList) = 0;
        virtual bool saveSelection(const std::list<feature_ptr>& featureList) = 0;

    protected:

        std::string _File;
};

#endif // SDK_FEATURE_TOOLSET_SELECTIONHANDLER_H_
