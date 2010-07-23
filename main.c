#include <stdio.h>

#include <iup.h>

Ihandle *IupQuakeBindingLayout();
Ihandle *IupQuakeMouseLayout();

int main(int argc, char **argv)
{
    Ihandle *win,*tabs,*buttons;

    IupOpen(&argc, &argv);      

    tabs = IupTabs(NULL);
    buttons = IupHbox(
        IupSetCallbacks(IupButton("&Quit", "ACTION"), "ACTION", (Icallback)IupExitLoop, NULL),
        IupFill(),
        IupButton("&Save", NULL),
        IupFill(),
        IupButton("&Launch game", NULL),
        NULL
    );

    win = IupDialog(
            IupSetAttributes(
                IupVbox(
                    IupSetAttributes(
                        IupLabel("Action Quake 2 Configuration"),
                        "EXPAND=YES, ALIGNMENT=ACENTER:ACENTER, FONT=\"sans-serif, Bold 18\""
                    ),
                    tabs,
                    buttons,
                    NULL
                ),
                "GAP=5"
            )
    );

    IupSetAttribute(win, "TITLE", "Action Quake 2 Configuration");
    IupSetAttribute(win, "RESIZE", "NO");

    IupAppend(tabs, IupQuakeBindingLayout());
    IupSetAttribute(tabs, "TABTITLE0", "Keyboard");

    IupAppend(tabs, IupQuakeMouseLayout());
    IupSetAttribute(tabs, "TABTITLE1", "Mouse");

    IupAppend(tabs, IupFill());
    IupSetAttribute(tabs, "TABTITLE2", "Audio");

    IupAppend(tabs, IupFill());
    IupSetAttribute(tabs, "TABTITLE3", "Video");

    IupAppend(tabs, IupFill());
    IupSetAttribute(tabs, "TABTITLE4", "Multiplayer");

    IupShow(win);
    IupMainLoop();
}
