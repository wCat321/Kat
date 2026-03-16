#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "kat_engine.h"
#include <stdlib.h>

Element* root;
EngineData* data;

void Engine_Init(int w, int h, const char* title)
{
    root = NULL;

    data = NULL;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(w, h, title);
    SetTargetFPS(60);
}

int Engine_Start()
{
    if (data && data->start)
        data->start();

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        if (data && data->frame)
            data->frame();

        Element_UpdateTree(root, dt);
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        Element_DrawTree(root);

        EndDrawing();
    }
    if (data && data->end)
        data->end();

    Element_FreeTree(root);
    CloseWindow();

    return 0;
}

void Engine_SetRoot(Element* element)
{
    root = element;
}

void Engine_SetData(EngineData* new_data)
{
    data = new_data;
}

EngineData* EngineData_Create(void)
{
    EngineData* data = (EngineData*)malloc(sizeof(EngineData));
    if (!data) return NULL;
    EngineData_Init(data);
    return data;
}

void EngineData_Init(EngineData* data)
{
    if (!data) return;

    data->start = NULL;
    data->frame = NULL;
    data->end = NULL;
}