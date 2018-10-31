#ifndef SDK_FEATURE_TOOLSET_FEATURE_H_
#define SDK_FEATURE_TOOLSET_FEATURE_H_

#include <list>

#include "dependency_fwd.h"

class Feature
{
  private:
    bool _selected;

    std::list<Dependency*> _dependencies;

  public:
    Feature();
    ~Feature();

    bool isSelected(void);
    bool select(void);

    void addDependency(Dependency* d);
	
	std::list<Dependency*> getDependencies(void);
};

#endif // SDK_FEATURE_TOOLSET_FEATURE_H_