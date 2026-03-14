#include "header_panel.h"

#include <stdlib.h>

Panel* HeaderPanelCreate(const char* text) 
{
    Panel* panel = PanelCreate();
    if (!panel)
        return NULL;
    HeaderPanelData* data = (HeaderPanelData*)malloc(sizeof(HeaderPanelData));
    if (!data)
        return NULL;

    panel->contentMargin = (Vector4){0, 23, 0, 0};
    
    data->text = text;

    panel->data = data;
    panel->base.draw = HeaderPanelDraw;
    panel->base.update = HeaderPanelUpdate;
    panel->base.free = HeaderPanelFree;
}

void HeaderPanelDraw(Panel* panel)
{
    HeaderPanelData* data = panel->data;
    GuiPanel(panel->rect, data ? data->text : NULL);
}

void HeaderPanelUpdate(Panel* panel)
{

}

void HeaderPanelFree(Panel* panel)
{
    if (!panel) return;

    if (panel->data)
    {
        free(panel->data);
        panel->data = NULL;
    }
}