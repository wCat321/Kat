#include "component.h"

void Component_Setup(Component* component)
{
	component->free = Component_Free;
}

void Component_Free(Component* component)
{
	free(component);
}