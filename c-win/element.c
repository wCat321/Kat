#include "element.h"

#include "component.h"
#include <stdlib.h>
#include <string.h>

Element* Element_Create(const char* name)
{
    Element* element = malloc(sizeof(Element));
    if (!element) return NULL;

    Element_Init(element);
    if (name)
    {
        size_t len = strlen(name) + 1;
        element->name = malloc(len);
        if (element->name)
            memcpy(element->name, name, len);
        else
            element->name = NULL;
    }
    else
    {
        element->name = NULL;
    }

    return element;
}

void Element_Init(Element* element)
{
    if (!element) return;

    element->parent = NULL;

    element->children = NULL;
    element->childCount = 0;
    element->childCapacity = 0;

    element->init = NULL;
    element->draw = NULL;
    element->update = NULL;
    element->free = Element_Free;

    element->components = NULL;
    element->componentCount = 0;
    element->componentCapacity = 0;
}

void Element_Free(Element* element)
{
    if (!element) return;

    free(element->name);
    free(element->children);
    free(element->components);

    free(element);
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
    if (child->parent)
        Element_RemoveChild(child->parent, child);
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

void Element_InitTree(Element* element)
{
    if (element->init)
        element->init(element);

    for (int i = 0; i < element->componentCount; i++)
    {
        Component* component = element->components[i];
        if (component->init)
			component->init(component);
    }

    for (int i = 0; i < element->childCount; i++)
    {
        Element* child = ELEMENT_CAST(Element, element->children[i]);
        Element_InitTree(child);
    }
}

void Element_UpdateTree(Element* element, float dt)
{
    if (element->update)
        element->update(element, dt);

    for (int i = 0; i < element->componentCount; i++)
    {
        Component* component = element->components[i];
		if (component->update)
			component->update(component, dt);
    }

    for (int i = 0; i < element->childCount; i++)
    {
        Element* child = ELEMENT_CAST(Element, element->children[i]);
        Element_UpdateTree(child, dt);
    }
}

void Element_DrawTree(Element* element)
{
    if (element->draw)
        element->draw(element);

    for (int i = 0; i < element->childCount; i++)
    {
        Element* child = ELEMENT_CAST(Element, element->children[i]);
        Element_DrawTree(child);
    }
}

void Element_FreeTree(Element* element)
{
    if (!element)
        return;

    for (int i = 0; i < element->componentCount; i++)
    {
        Component* component = element->components[i];
        if (component->free)
			component->free(component);
		element->components[i] = NULL;
    }

    element->componentCount = 0;

    for (int i = 0; i < element->childCount; i++)
    {
        Element* child = element->children[i];
        Element_FreeTree(child);
        element->children[i] = NULL;
    }

    element->childCount = 0;

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

void Element_AddComponent(Element* element, Component* component)
{
    if (!element || !component) return;

    if (element->componentCount >= element->componentCapacity)
    {
        int newCapacity = element->componentCapacity ? element->componentCapacity * 2 : 4;

        Component** tmp = realloc(element->components, newCapacity * sizeof(Component*));
        if (!tmp) return;

        element->components = tmp;
        element->componentCapacity = newCapacity;
    }

    element->components[element->componentCount++] = component;
    component->owner = element;
}

void Element_RemoveComponent(Element* element, Component* component)
{
    if (!element || !component) return;

    for (int i = 0; i < element->componentCount; i++)
    {
        if (element->components[i] == component)
        {
            for (int j = i; j < element->componentCount - 1; j++)
            {
                element->components[j] = element->components[j + 1];
            }

            element->componentCount--;
            component->owner = NULL;
            return;
        }
    }
}