#include "traverse.h"

#include "element.h"
#include <stdlib.h>

typedef struct
{
	int depth;
} TraverseData;

void traverse_tree(Element* element, int depth);
void print_name(Element* element, int depth);

Component* Component_Traverse_New()
{
	Component* component = Component_New();
	if (!component) return NULL;

	TraverseData* data = malloc(sizeof(TraverseData));
	if (!data)
	{
		Component_Free(component);
		return NULL;
	}

	data->depth = 0;
	
	component->ready = Component_Traverse_Ready;
	component->data = (void*)(data);
	return component;
}

void Component_Traverse_Ready(Component* component)
{
	if (!component || !component->data || !component->owner) return;
	TraverseData* data = (TraverseData*)component->data;

	traverse_tree(component->owner, data->depth);
}

void traverse_tree(Element* element, int depth)
{
	if (!element) return;

	print_name(element, depth);

	depth++;
	for (int i = 0; i < element->childCount; i++)
	{
		traverse_tree(element->children[i], depth);
	}
}

void print_name(Element* element, int depth)
{
	if (depth)
	{
		for (int i = 0; i < depth; i++)
			printf("  ");
		printf("\\-- ");
	}
	printf("Element Name: \"%s\" | Depth: %d\n", element->name, depth);
}