#include "element.h"

Element* Element_Create(const char* name)
{
    Element* element = malloc(sizeof(Element));
    if (!element) return NULL;

    Element_Init(element, ELEMENT_BASE);
    element->name = name;
    return element;
}

void Element_Init(Element* element, ElementType type)
{
    if (!element) return;

    element->type = type;

    element->parent = NULL;

    element->children = NULL;
    element->childCount = 0;
    element->childCapacity = 0;

    element->draw = NULL;
    element->update = NULL;
    element->free = Element_Free;
}

void Element_Free(Element* element) 
{
    free(element);
    element = NULL;
}

void Element_AddChild(Element* parent, Element* child)
{
    if (!parent || !child) return;

    if (parent->childCount >= parent->childCapacity)
    {
        int newCapacity = parent->childCapacity ? parent->childCapacity * 2 : 4;

        Element** tmp = realloc(parent->children, newCapacity * sizeof(Element*));
        if (!tmp) return;

        parent->children = tmp;
        parent->childCapacity = newCapacity;
    }

    parent->children[parent->childCount++] = child;
    child->parent = parent;
}


void Element_RemoveChild(Element* parent, Element* child)
{
    if (!parent || !child) return;

    for (int i = 0; i < parent->childCount; i++)
    {
        if (parent->children[i] == child)
        {
            for (int j = i; j < parent->childCount - 1; j++)
            {
                parent->children[j] = parent->children[j + 1];
            }

            parent->childCount--;
            child->parent = NULL;
            return;
        }
    }
}


void Element_UpdateTree(Element* element)
{
    if (element->update)
        element->update(element);

    for (int i = 0; i < element->childCount; i++)
    {
        Element* child = ELEMENT_AS(Element, element->children[i]);
        Element_UpdateTree(child);
    }
}

void Element_DrawTree(Element* element)
{
    if (element->draw)
        element->draw(element);

    for (int i = 0; i < element->childCount; i++)
    {
        Element* child = ELEMENT_AS(Element, element->children[i]);
        Element_DrawTree(child);
    }
}

void Element_FreeTree(Element* element)
{
    for (int i = 0; i < element->childCount; i++)
    {
        Element* child = ELEMENT_AS(Element, element->children[i]);
        Element_FreeTree(child);
    }

    if (element->free)
        element->free(element);

}

void Element_Traverse(Element* element, ElementVisitor visitor, int depth)
{
    if (!element || !visitor) return;

    visitor(element, depth);

    depth++;
    for (int i = 0; i < element->childCount; i++)
    {
        Element_Traverse(element->children[i], visitor, depth);
    }
}