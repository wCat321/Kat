#pragma once

#include <stdlib.h>

typedef enum
{
    ELEMENT_BASE = 0,
    ELEMENT_PANEL,
    ELEMENT_2D,
    ELEMENT_3D,
    ELEMENT_CUSTOM
} ElementType;

typedef struct Element Element;

typedef void (*ElementDrawFn)(Element* element);
typedef void (*ElementUpdateFn)(Element* element);
typedef void (*ElementFreeFn)(Element* element);


struct Element
{
    ElementType type;
    char* name;

    Element* parent;

    Element** children;
    int childCount;
    int childCapacity;

    ElementDrawFn draw;
    ElementUpdateFn update;
    ElementFreeFn free;

};

Element* Element_Create(const char* name);
void Element_Init(Element* element, ElementType type);
void Element_Free(Element* element);

void Element_AddChild(Element* parent, Element* child);
void Element_RemoveChild(Element* parent, Element* child);

void Element_UpdateTree(Element* element);
void Element_DrawTree(Element* element);
void Element_FreeTree(Element* element);

typedef void (*ElementVisitor)(Element* element, int depth);
void Element_Traverse(Element* element, ElementVisitor visitor, size_t depth);

#define ELEMENT_AS(type, elementPtr) ((type*)(elementPtr))