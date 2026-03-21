#pragma once

#include "component.h"
#include "raylib.h"
#include "raymath.h"

extern ComponentType C_Transform2D_Type;

typedef struct C_Transform2D
{
	Component base;

	Vector2 position;
	float rotation;
	Vector2 scale;

} C_Transform2D;

C_Transform2D* C_Transform2D_New();
void C_Transform2D_Setup(C_Transform2D* transform2d);

Matrix C_Transform2D_GetLocalMatrix(C_Transform2D* transform2d);