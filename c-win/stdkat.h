#pragma once
#define STDKAT_H

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "gui.h"

#define WIN_LEFT 0
#define WIN_TOP 0
#define WIN_RIGHT (GetScreenWidth())
#define WIN_BOTTOM (GetScreenHeight())

#define WIN_TOP_LEFT 0, 0
#define WIN_TOP_RIGHT GetScreenWidth(), 0
#define WIN_BOTTOM_LEFT 0, GetScreenHeight()
#define WIN_BOTTOM_RIGHT GetScreenWidth(), GetScreenHeight()

#define WIN_WIDTH_P(x)  ((GetScreenWidth()  * (x)) / 100)
#define WIN_HEIGHT_P(x) ((GetScreenHeight() * (x)) / 100)