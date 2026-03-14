#include "element.h"

Element* ElementCreate(void)
{
    Element* element = malloc(sizeof(Element));
    if (!element) return NULL;

    ElementInit(element, ELEMENT_BASE);
    return element;
}

void ElementInit(Element* element, ElementType type)
{
    if (!element) return;

    element->type = type;

    element->parent = NULL;

    element->children = NULL;
    element->childCount = 0;
    element->childCapacity = 0;

    element->draw = NULL;
    element->update = NULL;
    element->free = ElementFree;
}

void ElementFree(Element* element) 
{
    free(element);
    element = NULL;
}

void ElementAddChild(Element* parent, Element* child)
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


void ElementRemoveChild(Element* parent, Element* child)
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


void ElementUpdateTree(Element* element)
{
    if (element->update)
        element->update(element);

    for (int i = 0; i < element->childCount; i++)
    {
        Element* child = ELEMENT_AS(Element, element->children[i]);
        ElementUpdateTree(child);
    }
}

void ElementDrawTree(Element* element)
{
    if (element->draw)
        element->draw(element);

    for (int i = 0; i < element->childCount; i++)
    {
        Element* child = ELEMENT_AS(Element, element->children[i]);
        ElementDrawTree(child);
    }
}

void ElementFreeTree(Element* element)
{
    for (int i = 0; i < element->childCount; i++)
    {
        Element* child = ELEMENT_AS(Element, element->children[i]);
        ElementFreeTree(child);
    }

    if (element->free)
        element->free(element);

}

void ElementTraverse(Element* element, ElementVisitor visitor)
{
    if (!element || !visitor) return;

    visitor(element);

    for (int i = 0; i < element->childCount; i++)
    {
        ElementTraverse(element->children[i], visitor);
    }
}