#pragma once

typedef struct Script Script;
typedef struct Element Element;
typedef void* Data;

typedef void (*ScriptReadyFn)(Script* self);
typedef void (*ScriptUpdateFn)(Script* self, float dt);
typedef void (*ScriptRemoveFn)(Script* self);
typedef void (*ScriptFreeFn)(Script* self);

struct Script
{
	/* Called when the owner Element is added to the scene. */
	ScriptReadyFn ready;
	/* Called every frame. */
	ScriptUpdateFn update;
	/* Called before a Script is removed from an Element. */
	ScriptRemoveFn remove;
	/* Called when a Script or its Element owner is freed. */
	ScriptFreeFn free;

	Element* owner;
	Data data;
};


Script* Script_New(); // Creates a default Script pointer.
void Script_Setup(Script* Script); // Initializes a Script to default values.
void Script_Remove(Script* Script); // Default Script removal function, added to Script->remove by Script_Setup;
void Script_Free(Script* Script); // Default Script freeing function, added to Script->free by Script_Setup.