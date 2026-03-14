#pragma once

#include "panel.h"
#include "raygui.h"

typedef struct {
    const char* text;
} HeaderPanelData;

Panel* HeaderPanelCreate(const char* text);

void HeaderPanelDraw(Panel* panel);
void HeaderPanelUpdate(Panel* panel);
void HeaderPanelFree(Panel* panel);
