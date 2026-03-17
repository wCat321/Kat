#include "kat.h"
#include "kat_engine.h"
#include <stdio.h>

#include "frametime.h"
#include "traverse.h"

Element* E_root;

void kat_init()
{
    Engine_New(1280, 720, "Kat Engine | Make Games");
    GuiLoadStyle("./kat_style.rgs");
    E_root = Element_New("ROOT");
    Engine_SetRoot(E_root);

    Element* E_second = Element_New("SECOND");
    Engine_AddToScene(E_root, E_second);

    Component* frame_time = Component_FrameTime_New();
    Component* traverse = Component_Traverse_New();
    Element_AddComponent(E_root, frame_time);
    Element_AddComponent(E_root, traverse);
}


int Kat()
{
    kat_init();
    return Engine_Start();

}