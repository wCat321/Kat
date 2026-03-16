#include "frametime.h"

#include <stdio.h>

Component* Component_FrameTime_Create()
{
	Component* component = Component_Create();
	component->update = Component_FrameTime_Update;
	return component;
}

void Component_FrameTime_Update(Component* component, float dt)
{
	printf("Frame time: %f\n", dt);
}