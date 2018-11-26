#ifndef SDK_FEATURE_TOOLSET_FEATURE_H_
#define SDK_FEATURE_TOOLSET_FEATURE_H_

#include <list>

#include "dependency_ptr.h"

class Feature : public std::enable_shared_from_this<Feature>
{
    public:

        Feature();
        ~Feature();

        bool isSelected(void);
        virtual bool select(void);

        bool isPlausible(void);
        bool markAsProblematic(void);

        virtual std::string getName(void);

        void addDependency(dependency_ptr d);

        std::list<dependency_ptr>& getDependencies(void);

    private:

        bool _selected;

        bool _plausible;

        std::list<dependency_ptr> _dependencies;
};

#endif // SDK_FEATURE_TOOLSET_FEATURE_H_
