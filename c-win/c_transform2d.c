#include "c_transform2d.h"

#include <stdlib.h>

ComponentType C_Transform2D_Type = "C_Transform2D";

C_Transform2D* C_Transform2D_New()
{
	C_Transform2D* transform2d = (C_Transform2D*)malloc(sizeof(C_Transform2D));
	if (!transform2d) return NULL;

	Component_Setup(Component_Cast(Component, transform2d));
	C_Transform2D_Setup(transform2d);
	return transform2d;
}

void C_Transform2D_Setup(C_Transform2D* transform2d)
{
	transform2d->base.type = &C_Transform2D_Type;
	transform2d->position = (Vector2){ 0,0 };
	transform2d->rotation = 0;
	transform2d->scale = (Vector2){ 1,1 };
}

Matrix C_Transform2D_GetLocalMatrix(C_Transform2D* transform2d)
{
	Matrix translation = MatrixTranslate(transform2d->position.x, transform2d->position.y, 0.0f);
	Matrix rotation = MatrixRotateZ(transform2d->rotation);
	Matrix scale = MatrixScale(transform2d->scale.x, transform2d->scale.y, 1.0f);

	return MatrixMultiply(translation,
		MatrixMultiply(rotation, scale));
}