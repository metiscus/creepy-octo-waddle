#include "aiworld.h"
#include "object.h"
#include <algorithm>

//!Note only returns AIComponents in the given range
std::vector<ComponentPtr> AIWorld::QueryRange(const Vector2& center, float rangesqr)
{
    std::vector<ComponentPtr> nearby;
    for(auto comp : components_)
    {
	if((center - comp->GetParent()->GetPosition()).Length2() <= rangesqr)
	{
	    nearby.emplace_back(comp);
	}
    }
    return nearby;
}
