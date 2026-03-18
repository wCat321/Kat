#pragma once

#include "raylib.h"
#include "raygui.h"

#include "script.h"
#include "component.h"

#include "element.h"

#include "gui.h"
#include "2d.h"

void Engine_New(int w, int h, const char* title);
int Engine_Start();

Element* Engine_SetRoot(Element* root);

Element* Engine_AddToScene(Element* parent, Element* child);

void Engine_Free(Element* tree);
void Engine_QueueFree(Element* tree);

