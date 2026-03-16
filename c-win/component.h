#pragma once

typedef struct Component Component;
typedef struct Element Element;

typedef void (*ComponentInitFn)(Component* self);
typedef void (*ComponentUpdateFn)(Component* self, float dt);
typedef void (*ComponentFreeFn)(Component* self);

struct Component
{
	ComponentInitFn init;
	ComponentUpdateFn update;
	ComponentFreeFn free;

	Element* owner;
};

Component* Component_Create();
void Component_Init(Component* component);
void Component_Free(Component* component);