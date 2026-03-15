#pragma once

#include <stdlib.h>

#include "raylib.h"
#include "raygui.h"

#include "element.h"

#include "gui.h"

typedef struct EngineData EngineData;

typedef void (*EngineStartFn)(void);
typedef void (*EngineFrameFn)(void);
typedef void (*EngineEndFn)(void);


struct EngineData
{
	EngineStartFn start;
	EngineFrameFn frame;
	EngineEndFn end;
};

void Engine_Init(int w, int h, const char* title);
int Engine_Start();

void Engine_SetRoot(Element* root);
void Engine_SetData(EngineData* data);

EngineData* EngineData_Create(void);
void EngineData_Init(EngineData* data);