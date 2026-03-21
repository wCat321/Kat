#include "c_camera2D.h"

#include <stdlib.h>

ComponentType C_Camera2D_Type = "C_Camera2D";

C_Camera2D* C_Camera2D_New()
{
	C_Camera2D* camera2d = (C_Camera2D*)malloc(sizeof(C_Camera2D));
	if (!camera2d) return NULL;
	C_Camera2D_Setup(camera2d);
	return camera2d;
}

void C_Camera2D_Setup(C_Camera2D* camera2d)
{
	if (!camera2d) return;
	Component_Setup(&camera2d->base);
	camera2d->zoom = 1;
}