#include "component.h"

#include <stdlib.h>

Component* Component_New()
{
	Component* component = (Component*)malloc(sizeof(Component));
	if (!component) return NULL;

	Component_Setup(component);
	return component;
}

void Component_Setup(Component* component)
{
	if (!component) return;

	component->ready = NULL;
	component->update = NULL;
	component->remove = NULL;
	component->free = Component_Free;

	component->owner = NULL;
	component->data = NULL;
}

void Component_Remove(Component* component)
{
	if (!component) return;
	component->owner = NULL;
}

void Component_Free(Component* component)
{
	if (!component) return;

	if (component->data)
		free(component->data);
	free(component);
}