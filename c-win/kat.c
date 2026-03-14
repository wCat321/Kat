#include "kat.h"

#include "stdkat.h"
int kat_init(int argc, char* argv)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(1280, 720, "Kat | Game Engine");
    GuiLoadStyle("./kat_style.rgs");
    SetTargetFPS(60);

    MakeFullPanel(p_root);

    MakePanel(p_main);
    MakePanel(p_bottom);

    MakePanel(p_left);
    MakePanel(p_right);
    MakePanel(p_center);

    PanelAddChild(&p_root, &p_main);
    PanelAddChild(&p_root, &p_bottom);

    PanelAddChild(&p_main, &p_left);
    PanelAddChild(&p_main, &p_center);
    PanelAddChild(&p_main, &p_right);

    PanelResize(&p_main, (Vector2) { 0, 0 }, (Vector2) { 100, 80 });
    PanelResize(&p_bottom, (Vector2) { 0, 80 }, (Vector2) { 100, 100 });

    PanelResize(&p_left, (Vector2) { 0, 0 }, (Vector2) { 15, 100 });
    PanelResize(&p_center, (Vector2) { 15, 0 }, (Vector2) { 85, 100 });
    PanelResize(&p_right, (Vector2) { 85, 0 }, (Vector2) { 100, 100 });

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        GuiPanel(p_left.rect, "Left");
        GuiPanel(p_center.rect, "Center");
        GuiPanel(p_right.rect, "Right");
        GuiPanel(p_bottom.rect, "Bottom");


        if (IsWindowResized()) PanelFill(&p_root);

        EndDrawing();
    }

    CloseWindow();
    return 0;

}

