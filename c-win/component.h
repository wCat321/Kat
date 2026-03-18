#pragma once


typedef struct Component Component;
typedef const char* ComponentType;

typedef void (*ComponentFreeFn)(Component* component);

struct Component
{
	ComponentType* type;
	ComponentFreeFn free;
};

void Component_Setup(Component* component);
void Component_Free(Component* component);

#define Component_Cast(type, componentPtr) (type*)(componentPtr)