#include "kat.h"
#include "kat_engine.h"

#include "frametime.h"
#include "traverse.h"

void kat_init()
{
    Engine_New(1280, 720, "Kat Engine | Make Games");
    GuiLoadStyle("./kat_style.rgs");
    Element* E_root = Engine_SetRoot(Element_New());
    Element* E_second = Engine_AddToScene(E_root, Element_New());
    E_Point2D* P2_point = Engine_AddToScene(E_second, Element_Cast(Element, E_Point2D_New()));

    Script* traverse = Element_AddScript(E_root, Script_Traverse_New());
}


int Kat()
{
    kat_init();
    return Engine_Start();

}