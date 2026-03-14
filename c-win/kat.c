#include "kat.h"

#include "stdkat.h"
int kat_init(int argc, char* argv)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Kat | Game Engine");
    GuiLoadStyle("./kat_style.rgs");
    SetTargetFPS(60);

    Panel p_root;
    INIT_Panel(&p_root);
    PanelFill(&p_root);

    Panel p_main;
    INIT_Panel(&p_main);

    Panel p_bottom;
    INIT_Panel(&p_bottom);
    MAKE_HeaderPanel(&p_bottom, "Bottom");

    Panel p_left;
    INIT_Panel(&p_left);
    MAKE_HeaderPanel(&p_left, "Left");

    PanelAddChild(&p_root, &p_main);
    PanelAddChild(&p_root, &p_bottom);
    PanelResize(&p_main, (Vector2) { 0, 0 }, (Vector2){ 100, 80 });
    PanelResize(&p_bottom, (Vector2) { 0, 80 }, (Vector2) { 100, 100 });

    PanelAddChild(&p_main, &p_left);
    PanelResize(&p_left, (Vector2) { 0, 0 }, (Vector2) { 15, 100 });

    while (!WindowShouldClose())
    {
        if (IsWindowResized())
            PanelFill(&p_root);

        PanelUpdateTree(&p_root);

        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        PanelDrawTree(&p_root);

        EndDrawing();
    }

    CloseWindow();
    return 0;

}

