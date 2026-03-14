#pragma once

#include "raylib.h"

typedef struct Panel Panel;

struct Panel
{
    Panel* parent;

    Rectangle rect;        // full panel area
    Rectangle contentRect; // area children can occupy

    Vector2 start;         // percent start inside parent contentRect
    Vector2 end;           // percent end inside parent contentRect

    // optional padding / header offsets
    Vector4 contentMargin; // left, top, right, bottom

    Panel** children;
    int childCount;
    int childCapacity;
};

#define MakePanel(p) \
    Panel p;          \
    PanelInit(&p)

#define MakeFullPanel(p) \
    MakePanel(p); \
    PanelFill(&p)

void PanelInit(Panel* panel);

void PanelAddChild(Panel* parent, Panel* child);

Rectangle PanelResize(Panel* panel, Vector2 start, Vector2 end);
#define PanelFill(panel) PanelResize(panel, (Vector2){0,0}, (Vector2){100,100})

static Rectangle PanelComputeContentRect(Panel* panel);