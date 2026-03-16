#pragma once

typedef struct Element Element;
typedef struct Component Component;

typedef void (*ElementInitFn)(Element* element);
typedef void (*ElementDrawFn)(Element* element);
typedef void (*ElementUpdateFn)(Element* element, float dt);
typedef void (*ElementFreeFn)(Element* element);


struct Element
{
    char* name;

    Element* parent;

    Element** children;
    int childCount;
    int childCapacity;

    ElementInitFn init;
    ElementDrawFn draw;
    ElementUpdateFn update;
    ElementFreeFn free;

    Component** components;
    int componentCount;
    int componentCapacity;

};

Element* Element_Create(const char* name);
void Element_Init(Element* element);
void Element_Free(Element* element);

void Element_AddChild(Element* parent, Element* child);
void Element_RemoveChild(Element* parent, Element* child);

void Element_InitTree(Element* element);
void Element_UpdateTree(Element* element, float dt);
void Element_DrawTree(Element* element);
void Element_FreeTree(Element* element);

typedef void (*ElementVisitor)(Element* element, int depth);
void Element_Traverse(Element* element, ElementVisitor visitor, int depth);

void Element_AddComponent(Element* element, Component* component);
void Element_RemoveComponent(Element* element, Component* component);

#define ELEMENT_CAST(type, elementPtr) ((type*)(elementPtr))