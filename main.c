#include <stdio.h>

#include <iup.h>

Ihandle *IupQuakeBindingLayout();
Ihandle *IupQuakeMouseLayout();

int main(int argc, char **argv)
{
    Ihandle *win,*tabs,*buttons;

    IupOpen(&argc, &argv);      

    tabs = IupTabs(
        IupQuakeBindingLayout(),
        IupQuakeMouseLayout(),
        IupFill(),
        IupFill(),
        IupFill(),
        NULL
    );
    IupStoreAttribute(tabs, "TABTITLE0", "Keyboard");
    IupStoreAttribute(tabs, "TABTITLE1", "Mouse");
    IupStoreAttribute(tabs, "TABTITLE2", "Audio");
    IupStoreAttribute(tabs, "TABTITLE3", "Video");
    IupStoreAttribute(tabs, "TABTITLE4", "Multiplayer");

    IupStoreAttribute(tabs, "MARGIN", "2x2");

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
                    //buttons,
                    NULL
                ),
                "GAP=5, MARGIN=3x3"
            )
    );

    IupStoreAttribute(win, "TITLE", "Action Quake 2 Configuration");
    IupStoreAttribute(win, "RESIZE", "NO");

    IupShow(win);

    /* bug? */
    IupStoreAttribute(win, "SIZE", NULL);
    IupRefresh(win);

    IupMainLoop();
}
