#include "kat.h"
#include "kat_engine.h"

void kat_start(void);
void print_name(Element* element, int depth);

Element* E_root;


void kat_init()
{
    Engine_Init(1280, 720, "Kat Engine | Make Games");

    EngineData* data = EngineData_Create();
    data->start = kat_start;

    GuiLoadStyle("./kat_style.rgs");
    E_root = Element_Create("ROOT");
    Engine_SetRoot(E_root);

    Element* E_second = Element_Create("SECOND");
    Element* E_third = Element_Create("THIRD");
    Element* E_fourth = Element_Create("FOURTH");
    Element* E_fifth = Element_Create("FIFTH");

    Element_AddChild(E_root, E_second);
    Element_AddChild(E_root, E_third);
    Element_AddChild(E_second, E_fourth);
    Element_AddChild(E_second, E_fifth);

    Engine_SetRoot(E_root);
    Engine_SetData(data);
}


int kat_launch()
{
    return Engine_Start();
}

void kat_start(void)
{
    Element_Traverse(E_root, print_name, 0);
}

void print_name(Element* element, int depth)
{
    if (depth)
    {
        for (int i = 0; i < depth; i++)
            printf("  ");
        printf("\\-- ");
    }
    printf("Element Name: \"%s\" | Depth: %d\n", element->name, depth);
}