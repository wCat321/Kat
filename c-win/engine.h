#pragma once

typedef struct Element Element;
typedef struct Element E_Camera2D;

void Engine_New(int w, int h, const char* title);
int Engine_Start();

Element* Engine_SetRoot(Element* root);

Element* Engine_AddToScene(Element* parent, Element* child);

void Engine_Free(Element* tree);
void Engine_QueueFree(Element* tree);

E_Camera2D* Engine_SetActiveCamera2D(E_Camera2D* camera2d);
//void Engine_SetActiveCamera3D(E_Camera3D* camera3d); //TODO: Add 3D elements