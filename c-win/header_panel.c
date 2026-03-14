#include "header_panel.h"

#include <stdlib.h>

void MAKE_HeaderPanel(Panel* panel, const char* text) 
{
    HeaderPanelData* data = (HeaderPanelData*)malloc(sizeof(HeaderPanelData));
    data->text = text;

    panel->data = data;
    panel->draw = DRAW_HeaderPanel;
    panel->update = UPDATE_HeaderPanel;
    panel->free = FREE_HeaderPanel;
}

void DRAW_HeaderPanel(Panel* panel)
{
    HeaderPanelData* data = panel->data;
    GuiPanel(panel->rect, data ? data->text : NULL);
}

void UPDATE_HeaderPanel(Panel* panel)
{

}

void FREE_HeaderPanel(Panel* panel)
{
    if (!panel) return;

    if (panel->data)
    {
        free(panel->data);
        panel->data = NULL;
    }
}