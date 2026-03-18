#include "transform2d.h"

#include <stdlib.h>

ComponentType Transform2D_Type = "Transform2D";

Transform2D* Transform2D_New()
{
	Transform2D* transform2d = (Transform2D*)malloc(sizeof(Transform2D));
	if (!transform2d) return NULL;

	Component_Setup(Component_Cast(Component, transform2d));
	Transform2D_Setup(transform2d);
	return transform2d;
}

void Transform2D_Setup(Transform2D* transform2d)
{
	transform2d->base.type = &Transform2D_Type;
	transform2d->position = (Vector2){ 0,0 };
	transform2d->rotation = 0;
	transform2d->scale = (Vector2){ 0,0 };
}

