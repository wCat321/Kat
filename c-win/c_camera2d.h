#pragma once

#include "component.h"
#include "raylib.h"
#include "raymath.h"

typedef struct Camera2D Camera2D;

extern ComponentType C_Camera2D_Type;

typedef struct C_Camera2D
{
	Component base;
	
	float zoom;
} C_Camera2D;

C_Camera2D* C_Camera2D_New();
void C_Camera2D_Setup(C_Camera2D* camera2d);