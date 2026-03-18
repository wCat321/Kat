#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "kat_engine.h"
#include <stdlib.h>

typedef struct FreeQueue FreeQueue;
struct FreeQueue
{
    Element** elements;
    int elementCount;
    int elementCapacity;
};

Element* root;
FreeQueue* free_queue;

int game_start = 0;

void FreeQueue_Add(FreeQueue* queue, Element* element)
{
    if (!queue || !element) return;

    if (element->childCount)
        for (int i = 0; i < element->childCount; i++)
            FreeQueue_Add(queue, element->children[i]);

    if (queue->elementCount >= queue->elementCapacity)
    {
        int newCapacity = queue->elementCapacity ? queue->elementCapacity * 2 : 4;

        Element** tmp = realloc(queue->elements, newCapacity * sizeof(Element*));
        if (!tmp) return;

        queue->elements = tmp;
        queue->elementCapacity = newCapacity;
    }

    queue->elements[queue->elementCount++] = element;
}

void FreeQueue_Free(FreeQueue* queue)
{
    for (int i = 0; i < queue->elementCount; i++)
    {
        Element* element = queue->elements[i];
        if (!element) continue;

        for (int j = 0; j < element->scriptCount; j++)
        {
            Script* script = element->scripts[j];
            if (script && script->free)
                script->free(script);
        }

        element->scriptCount = 0;

        for (int j = 0; j < element->componentCount; j++)
        {
            Component* component = element->components[j];
            if (component && component->free)
                component->free(component);
        }

        element->componentCount = 0;

        if (element->free)
            element->free(element);
    }
    queue->elementCount = 0;
}

void Engine_New(int w, int h, const char* title)
{
    root = NULL;


    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(w, h, title);
}

int Engine_Start()
{
    FreeQueue q = { 0 };
    free_queue = &q;
    game_start = 1;
    if (root)
        Element_ReadyTree(root);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        if (free_queue->elementCount)
            FreeQueue_Free(free_queue);

        Element_UpdateTree(root, dt);

        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        Element_DrawTree(root);

        EndDrawing();
    }

    Element_FreeTree(root);
    GuiLoadStyleDefault();
    CloseWindow();

    return 0;
}

Element* Engine_SetRoot(Element* element)
{
    root = element;
    if (game_start)
        Element_ReadyTree(root);
    
    return root;
}

Element* Engine_AddToScene(Element* parent, Element* child)
{
    Element_AddChild(parent, child);
    if (game_start)
        Element_ReadyTree(child);

    return child;
}

void Engine_Free(Element* tree)
{
    FreeQueue queue = { 0 };
    FreeQueue_Add(&queue, tree);
    FreeQueue_Free(&queue);
}

void Engine_QueueFree(Element* tree)
{
    FreeQueue_Add(free_queue, tree);
}
