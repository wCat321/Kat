#include "frametime.h"

#include <stdio.h>

Script* Script_FrameTime_New()
{
	Script* script = Script_New();
	script->update = Script_FrameTime_Update;
	return script;
}

void Script_FrameTime_Update(Script* script, float dt)
{
	printf("Frame time: %f\n", dt);
}