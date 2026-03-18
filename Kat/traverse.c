#include "traverse.h"

#include "element.h"
#include <stdlib.h>


void traverse_tree(Element* element, int depth);
void print_name(Element* element, int depth);

Script* Script_Traverse_New()
{
	Script* script = Script_New();
	if (!script) return NULL;

	script->ready = Script_Traverse_Ready;
	return script;
}

void Script_Traverse_Ready(Script* script)
{
	if (!script || !script->owner) return;

	traverse_tree(script->owner, 0);
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
	printf("Element: %p | Depth: %d\n", &element, depth);
}