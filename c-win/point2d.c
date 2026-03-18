#include "point2d.h"

#include <stdlib.h>

Point2D* Point2D_New()
{
	Point2D* point2d = (Point2D*)malloc(sizeof(Point2D));
	if (!point2d) return NULL;

	Point2D_Setup(point2d);
    return point2d;
}

void Point2D_Setup(Point2D* point2d)
{
	if (!point2d) return;
    Element_Setup(&point2d->base);

	point2d->transform = Component_Cast(Transform2D, Element_AddComponent(&point2d->base, Component_Cast(Component, Transform2D_New())));

}

Vector2 Point2D_GetWorldPosition(Point2D* point2d)
{
	Vector2 output = { 0,0 };
	Element* current = Element_Cast(Element, point2d);

	while (current)
	{
		Transform2D* transform = Component_Cast(Transform2D, Element_GetComponent(current, Transform2D_Type));

		if (transform)
		{
			output.x += transform->position.x;
			output.y += transform->position.y;
		}

		current = current->parent;
	}

	return output;
}

float Point2D_GetWorldRotation(Point2D* point2d)
{
	float output = 0;
	Element* current = Element_Cast(Element, point2d);

	while (current)
	{
		Transform2D* transform = Component_Cast(Transform2D, Element_GetComponent(current, Transform2D_Type));

		if (transform)
		{
			output += transform->rotation;
		}

		current = current->parent;
	}

	return output;
}

Vector2 Point2D_GetWorldScale(Point2D* point2d)
{
	Vector2 output = { 0,0 };
	Element* current = Element_Cast(Element, point2d);

	while (current)
	{
		Transform2D* transform = Component_Cast(Transform2D, Element_GetComponent(current, Transform2D_Type));

		if (transform)
		{
			output.x += transform->scale.x;
			output.y += transform->scale.y;
		}

		current = current->parent;
	}

	return output;
}