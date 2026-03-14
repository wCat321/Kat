#include "panel.h"

#include <stdlib.h>
#include "raylib.h"

void PanelInit(Panel* panel)
{
    if (!panel) return;

    panel->parent = NULL;

    panel->rect = (Rectangle){ 0,0,0,0 };
    panel->contentRect = (Rectangle){ 0,0,0,0 };

    panel->start = (Vector2){ 0,0 };
    panel->end = (Vector2){ 0,0 };

    panel->contentMargin = (Vector4){ 0,0,0,0 };

    panel->children = NULL;
    panel->childCount = 0;
    panel->childCapacity = 0;
}

static Rectangle PanelComputeContentRect(Panel* panel)
{
    Rectangle r = panel->rect;

    r.x += panel->contentMargin.x;
    r.y += panel->contentMargin.y;

    r.width -= panel->contentMargin.x + panel->contentMargin.z;
    r.height -= panel->contentMargin.y + panel->contentMargin.w;

    return r;
}

Rectangle PanelResize(Panel* panel, Vector2 start, Vector2 end)
{
    panel->start = start;
    panel->end = end;

    Rectangle parentRect;

    if (panel->parent)
        parentRect = panel->parent->contentRect;
    else
        parentRect = (Rectangle){ 0,0,GetScreenWidth(),GetScreenHeight() };

    panel->rect.x = parentRect.x + parentRect.width * (start.x / 100.0f);
    panel->rect.y = parentRect.y + parentRect.height * (start.y / 100.0f);

    panel->rect.width = parentRect.width * ((end.x - start.x) / 100.0f);
    panel->rect.height = parentRect.height * ((end.y - start.y) / 100.0f);

    panel->contentRect = PanelComputeContentRect(panel);

    for (int i = 0; i < panel->childCount; i++)
    {
        Panel* child = panel->children[i];
        PanelResize(child, child->start, child->end);
    }

    return panel->rect;
}

void PanelAddChild(Panel* parent, Panel* child)
{
    if (!parent || !child) return; // defensive: ignore invalid input

    if (parent->childCount >= parent->childCapacity)
    {
        int newCapacity = parent->childCapacity ? parent->childCapacity * 2 : 4;

        Panel** tmp = realloc(parent->children, newCapacity * sizeof(Panel*));
        if (!tmp)
        {
            // Allocation failed; leave parent unchanged
            return;
        }

        parent->children = tmp;
        parent->childCapacity = newCapacity;
    }

    parent->children[parent->childCount] = child;
    child->parent = parent;
    parent->childCount++;
}
