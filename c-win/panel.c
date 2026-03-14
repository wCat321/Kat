#include "panel.h"

Panel* PanelCreate(void)
{
    Panel* panel = malloc(sizeof(Panel));
    if (!panel) return NULL;

    PanelInit(panel);
    return panel;
}

void PanelInit(Panel* panel)
{
    if (!panel) return;

    ElementInit(ELEMENT_AS(Element, panel), ELEMENT_PANEL);

    panel->rect = (Rectangle){ 0 };
    panel->contentRect = (Rectangle){ 0 };

    panel->start = (Vector2){ 0,0 };
    panel->end = (Vector2){ 100,100 };

    panel->contentMargin = (Vector4){ 0,0,0,0 };

    panel->data = NULL;
}

void PanelAddChild(Panel* parent, Panel* child)
{
    ElementAddChild(&parent->base, &child->base);
}

Rectangle PanelComputeContentRect(Panel* panel)
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

    Element* parentElement = panel->base.parent;

    if (parentElement && parentElement->type == ELEMENT_PANEL)
    {
        Panel* parent = (Panel*)parentElement;
        parentRect = parent->contentRect;
    }
    else
    {
        parentRect = (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() };
    }

    panel->rect.x = parentRect.x + parentRect.width * (start.x / 100.0f);
    panel->rect.y = parentRect.y + parentRect.height * (start.y / 100.0f);

    panel->rect.width = parentRect.width * ((end.x - start.x) / 100.0f);
    panel->rect.height = parentRect.height * ((end.y - start.y) / 100.0f);

    panel->contentRect = PanelComputeContentRect(panel);

    for (int i = 0; i < panel->base.childCount; i++)
    {
        Element* childElement = panel->base.children[i];

        if (childElement->type == ELEMENT_PANEL)
        {
            Panel* child = (Panel*)childElement;
            PanelResize(child, child->start, child->end);
        }
    }

    return panel->rect;
}

void PanelFillParent(Panel* panel)
{
    PanelResize(panel, (Vector2) { 0, 0 }, (Vector2) { 100, 100 });
}

