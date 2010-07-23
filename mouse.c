#include <stdio.h>
#include <stdlib.h>
#include <iup.h>

Ihandle *IupQuakeMouseLayout()
{
    Ihandle *tab;

    tab = IupFill();
    IupSetAttributes(tab, "GAP=5");
    return tab;
}

