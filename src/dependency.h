#ifndef SDK_FEATURE_TOOLSET_DEPENDENCY_H_
#define SDK_FEATURE_TOOLSET_DEPENDENCY_H_

#include <list>

#include "feature_ptr.h"

class Dependency : public std::enable_shared_from_this<Dependency>
{
    public:

        Dependency();
        ~Dependency();

        bool isPlausible(void);
        bool markAsProblematic(void);

        bool addFeature(feature_ptr);

        std::list<feature_ptr>& getFeatures(void);

        virtual bool checkCondition(void) = 0;

        virtual std::string getDotEgdeLabel(void) = 0;

        virtual std::string getDotArrowType(void) = 0;

    protected:

        std::list<feature_ptr> _features;

    private:

        bool _plausible;
};

#endif // SDK_FEATURE_TOOLSET_DEPENDENCY_H_
