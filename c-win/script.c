#include "script.h"

#include <stdlib.h>

Script* Script_New()
{
	Script* script = (Script*)malloc(sizeof(Script));
	if (!script) return NULL;

	Script_Setup(script);
	return script;
}

void Script_Setup(Script* script)
{
	if (!script) return;

	script->ready = NULL;
	script->update = NULL;
	script->remove = NULL;
	script->free = Script_Free;

	script->owner = NULL;
	script->data = NULL;
}

void Script_Remove(Script* script)
{
	if (!script) return;
	script->owner = NULL;
}

void Script_Free(Script* script)
{
	if (!script) return;

	if (script->data)
		free(script->data);
	free(script);
}