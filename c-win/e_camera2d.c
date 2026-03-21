#include "e_camera2d.h"

#include "element.h"
#include "e_point2d.h"
#include "c_camera2d.h"

#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

E_Camera2D* E_Camera2D_New()
{
	E_Camera2D* camera2d = (E_Camera2D*)malloc(sizeof(E_Camera2D));
	if (!camera2d) return NULL;
	E_Camera2D_Setup(camera2d);
	return camera2d;
}

void E_Camera2D_Setup(E_Camera2D* camera2d)
{
	if (!camera2d) return;
	E_Point2D_Setup(camera2d);
	Element_AddComponent(camera2d, Component_Cast(Component, C_Camera2D_New()));
}

Camera2D E_Camera2D_GetCamera(E_Camera2D* camera2d)
{
	if (!camera2d)
	{
		Camera2D camera = { 0 };
		camera.zoom = 1;
		return camera;
	}

	C_Camera2D* cam_component = Component_Cast(C_Camera2D, Element_GetComponent(Element_Cast(Element, camera2d), C_Camera2D_Type));
	if (!cam_component)
	{
		Camera2D camera = { 0 };
		camera.zoom = 1;
		return camera;
	}

	Camera2D camera = { 0 };

	Matrix transform = E_Point2D_GetWorldMatrix(Element_Cast(E_Point2D, camera2d));

	camera.target = E_Point2D_MatrixGetPosition(transform);
	camera.rotation = E_Point2D_MatrixGetRotation(transform);
	camera.zoom = cam_component->zoom;

	return camera;
}

