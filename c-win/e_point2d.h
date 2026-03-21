#pragma once

#include "raylib.h"
#include "raymath.h"

typedef struct Element E_Point2D;

E_Point2D* E_Point2D_New();
void E_Point2D_Setup(E_Point2D* point2d);

Matrix E_Point2D_GetWorldMatrix(E_Point2D* point2d);

Vector2 E_Point2D_GetWorldPosition(E_Point2D* point2d);
float E_Point2D_GetWorldRotation(E_Point2D* point2d);
Vector2 E_Point2D_GetWorldScale(E_Point2D* point2d);

Vector2 E_Point2D_MatrixGetPosition(Matrix matrix);
float E_Point2D_MatrixGetRotation(Matrix matrix);
Vector2 E_Point2D_MatrixGetScale(Matrix matrix);
