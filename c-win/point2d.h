#pragma once

#include "element.h"
#include "transform2d.h"

typedef struct Point2D Point2D;

struct Point2D
{
	Element base;
	Transform2D* transform;
};

Point2D* Point2D_New();
void Point2D_Setup(Point2D* point2d);

Vector2 Point2D_GetWorldPosition(Point2D* point2d);
float Point2D_GetWorldRotation(Point2D* point2d);
Vector2 Point2D_GetWorldScale(Point2D* point2d);