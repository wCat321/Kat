#pragma once

#include "raylib.h"

typedef struct Panel Panel;

typedef void (*PanelDrawFn)(Panel* panel);
typedef void (*PanelUpdateFn)(Panel* panel);
typedef void (*PanelFreeFn)(Panel* panel);

struct Panel
{
    Panel* parent;

    Rectangle rect;
    Rectangle contentRect;

    Vector2 start;
    Vector2 end;

    Vector4 contentMargin;

    Panel** children;
    int childCount;
    int childCapacity;

    PanelDrawFn draw;
    PanelUpdateFn update;
    PanelFreeFn free;

    void* data;   // custom widget data
};

void INIT_Panel(Panel* panel);

void PanelAddChild(Panel* parent, Panel* child);

Rectangle PanelResize(Panel* panel, Vector2 start, Vector2 end);
#define PanelFill(panel) PanelResize(panel, (Vector2){0,0}, (Vector2){100,100})

static Rectangle PanelComputeContentRect(Panel* panel);

void PanelUpdateTree(Panel* panel);
void PanelDrawTree(Panel* panel);
void PanelFreeTree(Panel* panel);