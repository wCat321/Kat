#pragma once

#include "raylib.h"
#include "raygui.h"

#include "component.h"

#include "element.h"

#include "gui.h"

void Engine_New(int w, int h, const char* title);
int Engine_Start();

void Engine_SetRoot(Element* root);

void Engine_AddToScene(Element* parent, Element* child);

void Engine_Free(Element* tree);
void Engine_QueueFree(Element* tree);

