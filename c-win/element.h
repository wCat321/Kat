#pragma once

typedef struct Element Element;
typedef struct Script Script;
typedef struct Component Component;
typedef const char* ComponentType;

typedef void (*ElementInitFn)(Element* element);
typedef void (*ElementReadyFn)(Element* element);
typedef void (*ElementDrawFn)(Element* element);
typedef void (*ElementUpdateFn)(Element* element, float dt);
typedef void (*ElementFreeFn)(Element* element);


struct Element
{
    Element* parent;

    ElementReadyFn ready;
    ElementDrawFn draw;
    ElementUpdateFn update;
    ElementFreeFn free;

    Element** children;
    int childCount;
    int childCapacity;

    Script** scripts;
    int scriptCount;
    int scriptCapacity;

    Component** components;
    int componentCount;
    int componentCapacity;

};

Element* Element_New();
void Element_Setup(Element* element);
void Element_Free(Element* element);

void Element_ReadyTree(Element* element);
void Element_UpdateTree(Element* element, float dt);
void Element_DrawTree(Element* element);
void Element_FreeTree(Element* element);

Element* Element_AddChild(Element* parent, Element* child);
void Element_RemoveChild(Element* parent, Element* child);

Script* Element_AddScript(Element* element, Script* script);
void Element_RemoveScript(Element* element, Script* script);

Component* Element_AddComponent(Element* element, Component* component);
void Element_RemoveComponent(Element* element, ComponentType* type);
Component* Element_GetComponent(Element* element, ComponentType* type);

#define Element_Cast(type, elementPtr) (type*)(elementPtr)
