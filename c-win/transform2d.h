#pragma once

#include "component.h"
#include "raylib.h"

extern ComponentType Transform2D_Type;

typedef struct Transform2D
{
	Component base;

	Vector2 position;
	float rotation;
	Vector2 scale;

} Transform2D;

Transform2D* Transform2D_New();
void Transform2D_Setup(Transform2D* transform2d);