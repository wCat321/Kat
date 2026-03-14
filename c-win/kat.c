#include "kat.h"

#include "stdkat.h"

Element* E_root;
Panel* P_win;

void kat_init(int argc, char* argv)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Kat | Game Engine");
    GuiLoadStyle("./kat_style.rgs");
    SetTargetFPS(60);

    E_root = ElementCreate();
    P_win = PanelCreate();

    ElementAddChild(E_root, ELEMENT_AS(Element, P_win));
    PanelFillParent(P_win);

    Panel* P_main = HeaderPanelCreate("Kat");
    Panel* P_bottom = HeaderPanelCreate("Bottom");

    PanelAddChild(P_win, P_main);
    PanelAddChild(P_win, P_bottom);
    PanelResize(P_main, (Vector2) { 0, 0 }, (Vector2) { 100, 80 });
    PanelResize(P_bottom, (Vector2) { 0, 80 }, (Vector2) { 100, 100 });

    Panel* P_left = HeaderPanelCreate("Left");
    Panel* P_right = HeaderPanelCreate("Right");

    
    PanelAddChild(P_main, P_left);
    PanelAddChild(P_main, P_right);
    PanelResize(P_left, (Vector2) { 0, 0 }, (Vector2) { 15, 100 });
    PanelResize(P_right, (Vector2) { 85, 0 }, (Vector2) { 100, 100 });
}

int kat_launch()
{
    while (!WindowShouldClose())
    {
        if (IsWindowResized())
            PanelFillParent(P_win);

        ElementUpdateTree(E_root);
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        ElementDrawTree(E_root);

        EndDrawing();
    }

    ElementFreeTree(E_root);
    CloseWindow();

}