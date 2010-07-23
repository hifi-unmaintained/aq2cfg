#include <stdio.h>
#include <stdlib.h>
#include <iup.h>

Ihandle *bind_current = NULL;

char *IupKeyToQuake(int c);

int IupQuakeBindingFocusEvent(Ihandle *ih)
{
    if(bind_current)
        IupStoreAttribute(bind_current, "BGCOLOR", NULL);
    IupStoreAttribute(ih, "BGCOLOR", "255 255 0");
    bind_current = ih;
}

int IupQuakeBindingKeyEvent(Ihandle *ih, int c)
{
    char *key = IupKeyToQuake(c);
    if(key[0] != 0) {
        IupStoreAttribute(ih, "VALUE", key);
        if(strcmp(key, "TAB"))
            IupNextField(ih);
    }
}

int IupQuakeBindingButtonEvent(Ihandle *ih, int button, int pressed, int x, int y, char *status)
{
    if(iup_isbutton1(status) && iup_isdouble(status))
        IupStoreAttribute(ih, "VALUE", "MOUSE1");

    if(iup_isbutton2(status))
        IupStoreAttribute(ih, "VALUE", "MOUSE3");

    if(iup_isbutton3(status))
        IupStoreAttribute(ih, "VALUE", "MOUSE2");

    if(iup_isbutton4(status))
        IupStoreAttribute(ih, "VALUE", "MOUSE4");

    if(iup_isbutton5(status))
        IupStoreAttribute(ih, "VALUE", "MOUSE4");

    return iup_isbutton1(status) && !iup_isdouble(status) ? 0 : IUP_IGNORE;
}

Ihandle *IupQuakeBinding(char *label, char *action, char *def)
{
    Ihandle *tmp = IupText(NULL);
    IupStoreAttribute(tmp, "VALUE", def);
    IupSetAttribute(tmp, "READONLY", "YES");
    IupSetCallback(tmp, "K_ANY", (Icallback)IupQuakeBindingKeyEvent);
    IupSetCallback(tmp, "BUTTON_CB", (Icallback)IupQuakeBindingButtonEvent);
    return IupSetAttributes(
        IupHbox(
            IupSetAttributes(
                IupLabel(label),
                "EXPAND=YES, ALIGNMENT=ALEFT:ACENTER"
            ),
            IupSetAttributes(
                IupSetCallbacks(tmp, "GETFOCUS_CB", (Icallback)IupQuakeBindingFocusEvent, NULL),
                "EXPAND=NO, SIZE=80x, ALIGNMENT=ALEFT:ACENTER"
            ),
            NULL
        ),
        "GAP=10"
    );
}

void IupQuakeBindingClear(Ihandle *ih)
{
    IupSetAttribute(bind_current, "VALUE", NULL);
    IupSetFocus(bind_current);
}

void IupQuakeBindingSelectSpecial(Ihandle *ih)
{
    static Ihandle *win = NULL;

    return; // TODO

    if(!win) {
        win = IupDialog(
                IupSetAttributes(
                    IupVbox(
                        IupSetAttributes(
                            IupLabel("Press a key or select a special key...\n\nHit ESC to abort."),
                            "ALIGNMENT=ACENTER"
                        ),
                        NULL
                    ),
                    "MARGIN=15x15"
                )
            );
        IupSetAttribute(win, "TITLE", "Select a key...");
        IupSetAttribute(win, "RESIZE", "NO");
    }

    IupPopup(win, IUP_CENTER, IUP_CENTER);
}

Ihandle *IupQuakeBindingLayout()
{
    Ihandle *tab;

    tab = IupVbox(
            IupHbox(
                IupVbox(
                    IupSetAttributes(
                        IupFrame(
                            IupVbox(
                                IupQuakeBinding("Move forward", "+forward", "W"),
                                IupQuakeBinding("Move back", "+back", "S"),
                                IupQuakeBinding("Move left", "+left", "A"),
                                IupQuakeBinding("Move right", "+right", "D"),
                                IupQuakeBinding("Jump", "+moveup", "MOUSE2"),
                                IupQuakeBinding("Duck", "+movedown", "C"),
                                IupQuakeBinding("Open door", "open door", "SPACE"),
                                NULL
                            )
                        ),
                        "TITLE=Movement, MARGIN=3, EXPAND=HORIZONTAL"
                    ),
                    IupSetAttributes(
                        IupFrame(
                            IupVbox(
                                IupQuakeBinding("Chat message", "say", "T"),
                                IupQuakeBinding("Team message", "say_team", "Y"),
                                NULL
                            )
                        ),
                        "TITLE=Communication, MARGIN=3, EXPAND=HORIZONTAL"
                    ),
                    IupSetAttributes(
                        IupFrame(
                            IupVbox(
                                IupQuakeBinding("Display multiplayer scores", "cmd help", "F2"),
                                IupQuakeBinding("Select team and weapon", "inven", "TAB"),
                                IupQuakeBinding("Take screen shot", "screenshotjpg", "F11"),
                                IupQuakeBinding("Quit game", "quit", "F12"),
                                NULL
                            )
                        ),
                        "TITLE=Miscellaneous, MARGIN=3, EXPAND=HORIZONTAL"
                    ),
                    IupFill(),
                    NULL
                ),
                IupVbox(
                    IupSetAttributes(
                        IupFrame(
                            IupVbox(
                                IupQuakeBinding("Primary attack", "+attack", "MOUSE1"),
                                IupQuakeBinding("Weapon mode", "weapon", "CTRL"),
                                IupQuakeBinding("Reload weapon", "reload", "R"),
                                IupQuakeBinding("Sniper zoom in", "lens in", "MWHEELUP"),
                                IupQuakeBinding("Sniper zoom out", "lens out", "MWHEELDOWN"),
                                IupQuakeBinding("Walk", "-speed", "SHIFT"),
                                IupQuakeBinding("Flashlight", "flashlight", "H"),
                                IupQuakeBinding("Primary weapon", "use special", "Q"),
                                IupQuakeBinding("MK23 Pistol", "use blaster", "1"),
                                IupQuakeBinding("Akimbo pistols", "use A 2nd pistol", "2"),
                                IupQuakeBinding("Combat knife", "use combat knife", "3"),
                                IupQuakeBinding("Grenade", "use m26 fragmentation grenade", "F"),
                                IupQuakeBinding("Previous weapon", NULL, NULL),
                                IupQuakeBinding("Next weapon", NULL, NULL),
                                IupQuakeBinding("Drop weapon", "drop weapon", "Z"),
                                IupQuakeBinding("Drop item", "drop item", "X"),
                                NULL
                            )
                        ),
                        "TITLE=Combat, MARGIN=3, EXPAND=HORIZONTAL"
                    ),
                    NULL
                ),
                NULL
            ),
            IupSetAttributes(
                IupHbox(
                    IupButton(" Use Defaults ", NULL),
                    IupFill(),
                    IupSetCallbacks(IupButton(" &Edit key ", "ACTION"), "ACTION", (Icallback)IupQuakeBindingSelectSpecial, NULL),
                    IupSetCallbacks(IupButton(" &Clear key ", "ACTION"), "ACTION", (Icallback)IupQuakeBindingClear, NULL),
                    NULL
                ),
                "GAP=5"
            ),
            NULL
    );
    IupSetAttributes(tab, "GAP=5");
    return tab;
}

char *IupKeyToQuake(int c)
{
    static char key_pressed[16] = { 0 };
    key_pressed[0] = 0;

    if(c > 32 && c < 127 && c != ';') {
        sprintf(key_pressed, "%c", toupper(c));
    } else {
        switch(c) {
#if 0
    special keys:
        ALT
        CTRL
        SHIFT
        CAPSLOCK
	KP_ENTER
	KP_SLASH
	KP_MINUS
	KP_PLUS
        KP_HOME
        KP_PGUP
        KP_PGDN
        KP_INS
        KP_DEL
        KP_UPARROW
        KP_LEFTARROW
        KP_RIGHTARROW
        KP_DOWNARROW
        MOUSE1
        MOUSE2
        MOUSE3
        MOUSE4
        MOUSE5
        MOUSE6
        MOUSE7
        MOUSE8
        MWHEELUP
        MWHEELDOWN
#endif
            case ';': sprintf(key_pressed, "SEMICOLON"); break;
            case K_UP: sprintf(key_pressed, "UPARROW"); break;
            case K_LEFT: sprintf(key_pressed, "LEFTARROW"); break;
            case 133: sprintf(key_pressed, "KP_5"); break;
            case K_RIGHT: sprintf(key_pressed, "RIGHTARROW"); break;
            case K_DOWN: sprintf(key_pressed, "DOWNARROW"); break;
            case K_PAUSE: sprintf(key_pressed, "PAUSE"); break;
            case K_SP: sprintf(key_pressed, "SPACE"); break;
            case K_CR: sprintf(key_pressed, "ENTER"); break;
            case K_TAB: sprintf(key_pressed, "TAB"); break;
            case K_BS: sprintf(key_pressed, "BACKSPACE"); break;
            case K_F1: sprintf(key_pressed, "F1"); break;
            case K_F2: sprintf(key_pressed, "F2"); break;
            case K_F3: sprintf(key_pressed, "F3"); break;
            case K_F4: sprintf(key_pressed, "F4"); break;
            case K_F5: sprintf(key_pressed, "F5"); break;
            case K_F6: sprintf(key_pressed, "F6"); break;
            case K_F7: sprintf(key_pressed, "F7"); break;
            case K_F8: sprintf(key_pressed, "F8"); break;
            case K_F9: sprintf(key_pressed, "F9"); break;
            case K_F10: sprintf(key_pressed, "F10"); break;
            case K_F11: sprintf(key_pressed, "F11"); break;
            case K_F12: sprintf(key_pressed, "F12"); break;

            case K_INS: sprintf(key_pressed, "INS"); break;
            case K_DEL: sprintf(key_pressed, "DEL"); break;
            case K_PGDN: sprintf(key_pressed, "PGDN"); break;
            case K_PGUP: sprintf(key_pressed, "PGUP"); break;
            case K_HOME: sprintf(key_pressed, "HOME"); break;
            case K_END: sprintf(key_pressed, "END"); break;
            default:
                printf("key %d\n", c);
        }
    }

    return key_pressed;
}

