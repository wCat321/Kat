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

    Element* parent;

    Element** children;
    int childCount;
    int childCapacity;

    ElementDrawFn draw;
    ElementUpdateFn update;
    ElementFreeFn free;

};

Element* ElementCreate(void);
void ElementInit(Element* element, ElementType type);
void ElementFree(Element* element);

void ElementAddChild(Element* parent, Element* child);
void ElementRemoveChild(Element* parent, Element* child);

void ElementUpdateTree(Element* element);
void ElementDrawTree(Element* element);
void ElementFreeTree(Element* element);

typedef void (*ElementVisitor)(Element* element);
void ElementTraverse(Element* element, ElementVisitor visitor);

#define ELEMENT_AS(type, elementPtr) ((type*)(elementPtr))