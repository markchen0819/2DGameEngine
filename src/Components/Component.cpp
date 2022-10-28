#include "../Allheaders.h"

Component::Component() { }
Component::~Component() { }

GameObject* Component::GetOwner()
{
	return owner;
}

void Component::SetOwner(GameObject* gobj)
{
	owner = gobj;
}
