#pragma once

typedef struct Component Component;
typedef struct Element Element;
typedef void* Data;

typedef void (*ComponentReadyFn)(Component* self);
typedef void (*ComponentUpdateFn)(Component* self, float dt);
typedef void (*ComponentRemoveFn)(Component* self);
typedef void (*ComponentFreeFn)(Component* self);

struct Component
{
	/* Called when the owner Element is added to the scene. */
	ComponentReadyFn ready;
	/* Called every frame. */
	ComponentUpdateFn update;
	/* Called before a Component is removed from an Element. */
	ComponentRemoveFn remove;
	/* Called when a Component or its Element owner is freed. */
	ComponentFreeFn free;

	Element* owner;
	Data data;
};


Component* Component_New(); // Creates a default Component pointer.
void Component_Setup(Component* component); // Initializes a Component to default values.
void Component_Remove(Component* component); // Default Component removal function, added to component->remove by Component_Setup;
void Component_Free(Component* component); // Default Component freeing function, added to component->free by Component_Setup.