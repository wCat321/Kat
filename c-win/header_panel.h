#pragma once
#define HEADER_PANEL_H


#include "panel.h"
#include "raygui.h"

typedef struct {
    const char* text;
} HeaderPanelData;

void DRAW_HeaderPanel(Panel* panel);
void UPDATE_HeaderPanel(Panel* panel);
void FREE_HeaderPanel(Panel* panel);

void MAKE_HeaderPanel(Panel* panel, const char* text);