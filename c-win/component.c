#include "component.h"

#include <stdlib.h>

Component* Component_Create()
{
	Component* component = (Component*)malloc(sizeof(Component));
	if (!component) return NULL;

	Component_Init(component);
	return component;
}

void Component_Init(Component* component)
{
	if (!component) return;

	component->init = NULL;
	component->update = NULL;
	component->free = Component_Free;
	component->owner = NULL;
}

void Component_Free(Component* component)
{
	if (!component) return;

	component->owner = NULL;
	free(component);
}