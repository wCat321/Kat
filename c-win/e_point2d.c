#include "e_point2d.h"

#include "element.h"
#include "c_transform2d.h"

#include <stdlib.h>

E_Point2D* E_Point2D_New()
{
	E_Point2D* point2d = (E_Point2D*)malloc(sizeof(E_Point2D));
	if (!point2d) return NULL;

	E_Point2D_Setup(point2d);
    return point2d;
}

void E_Point2D_Setup(E_Point2D* point2d)
{
	if (!point2d) return;
    Element_Setup(point2d);

	Element_AddComponent(point2d, Component_Cast(Component, C_Transform2D_New()));

}

Matrix E_Point2D_GetWorldMatrix(E_Point2D* point2d)
{
	Matrix result = MatrixIdentity();

	Element* current = Element_Cast(Element, point2d);

	while (current)
	{
		C_Transform2D* transform = Component_Cast(C_Transform2D, Element_GetComponent(current, C_Transform2D_Type));

		if (transform)
		{
			Matrix local = C_Transform2D_GetLocalMatrix(transform);

			result = MatrixMultiply(local, result);
		}

		current = current->parent;
	}

	return result;
}

Vector2 E_Point2D_GetWorldPosition(E_Point2D* point2d)
{
	Matrix world = E_Point2D_GetWorldMatrix(point2d);
	return E_Point2D_MatrixGetPosition(world);
}

float E_Point2D_GetWorldRotation(E_Point2D* point2d)
{
	Matrix world = E_Point2D_GetWorldMatrix(point2d);
	return E_Point2D_MatrixGetRotation(world);
}

Vector2 E_Point2D_GetWorldScale(E_Point2D* point2d)
{
	Matrix world = E_Point2D_GetWorldMatrix(point2d);
	return E_Point2D_MatrixGetScale(world);
}

Vector2 E_Point2D_MatrixGetPosition(Matrix matrix)
{
	Vector3 pos3 = Vector3Transform((Vector3) { 0, 0, 0 }, matrix);
	return (Vector2) { pos3.x, pos3.y };

}
float E_Point2D_MatrixGetRotation(Matrix matrix)
{
	return atan2f(matrix.m1, matrix.m0);
}
Vector2 E_Point2D_MatrixGetScale(Matrix matrix)
{
	float scaleX = sqrtf(matrix.m0 * matrix.m0 + matrix.m1 * matrix.m1);
	float scaleY = sqrtf(matrix.m4 * matrix.m4 + matrix.m5 * matrix.m5);

	return (Vector2) { scaleX, scaleY };

}
