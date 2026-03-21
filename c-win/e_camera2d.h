#pragma once

typedef struct Camera2D Camera2D;
typedef struct Element E_Camera2D;

E_Camera2D* E_Camera2D_New();
void E_Camera2D_Setup(E_Camera2D* camera2d);

Camera2D E_Camera2D_GetCamera(E_Camera2D* camera2d);