#pragma once

#include "raylib.h"
#include "element.h"

typedef struct Panel Panel;

struct Panel
{
    Element base;

    Rectangle rect;
    Rectangle contentRect;

    Vector2 start;
    Vector2 end;

    Vector4 contentMargin;

    void* data;
};

Panel* PanelCreate(void);
void PanelInit(Panel* panel);

void PanelAddChild(Panel* parent, Panel* child);

Rectangle PanelResize(Panel* panel, Vector2 start, Vector2 end);
void PanelFillParent(Panel* panel);

Rectangle PanelComputeContentRect(Panel* panel);