#pragma once

typedef struct Element Element;
typedef struct Component Component;

typedef void (*ElementInitFn)(Element* element);
typedef void (*ElementReadyFn)(Element* element);
typedef void (*ElementDrawFn)(Element* element);
typedef void (*ElementUpdateFn)(Element* element, float dt);
typedef void (*ElementFreeFn)(Element* element);


struct Element
{
    char* name;

    Element* parent;

    ElementReadyFn ready;
    ElementDrawFn draw;
    ElementUpdateFn update;
    ElementFreeFn free;

    Element** children;
    int childCount;
    int childCapacity;

    Component** components;
    int componentCount;
    int componentCapacity;

};

Element* Element_New(const char* name);
void Element_Setup(Element* element);
void Element_Free(Element* element);

void Element_ReadyTree(Element* element);
void Element_UpdateTree(Element* element, float dt);
void Element_DrawTree(Element* element);
void Element_FreeTree(Element* element);

void Element_AddChild(Element* parent, Element* child);
void Element_RemoveChild(Element* parent, Element* child);

void Element_AddComponent(Element* element, Component* component);
void Element_RemoveComponent(Element* element, Component* component);

#define ELEMENT_CAST(type, elementPtr) ((type*)(elementPtr))