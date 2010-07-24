#include <stdio.h>
#include <stdlib.h>
#include <iup.h>

Ihandle *IupQuakeSetToggle(char *title, char *key, char *val1, char *val2, int checked)
{
    Ihandle *tmp = IupToggle(title, "ACTION");
    IupStoreAttribute(tmp, "VALUE", (checked ? "ON" : "OFF"));
    return tmp;
}

int IupQuakeScaleUpdate(Ihandle *ih)
{
    char buf[16];
    Ihandle *label_value = IupGetChild(IupGetChild(IupGetParent(ih), 1), 1);
    snprintf(buf, 16, "%.1f", atof(IupGetAttribute(ih, "VALUE")));
    IupStoreAttribute(label_value, "TITLE", buf);
}

Ihandle *IupQuakeScale(char *title, float min, float max, float step, char *key, float def)
{
    Ihandle *scale,*label_value,*label_min,*label_max;

    char buf[128];

    scale = IupVal("HORIZONTAL");
    snprintf(buf, 128, "EXPAND=HORIZONTAL, MIN=%.1f, MAX=%.1f, VALUE=%.1f, STEP=0.01", min, max, def);
    IupSetAttributes(scale, buf);
    IupSetCallback(scale, "VALUECHANGED_CB", (Icallback)IupQuakeScaleUpdate);

    snprintf(buf, 16, "%.1f", def);
    label_value = IupLabel(buf);
    IupStoreAttribute(label_value, "EXPAND", "HORIZONTAL");
    IupStoreAttribute(label_value, "ALIGNMENT", "ACENTER:ACENTER");

    snprintf(buf, 16, "%.1f", min);
    label_min = IupLabel(buf);
    IupStoreAttribute(label_min, "ALIGNMENT", "ACENTER:ACENTER");
    snprintf(buf, 16, "%.1f", max);
    label_max = IupLabel(buf);
    IupStoreAttribute(label_max, "ALIGNMENT", "ACENTER:ACENTER");

    return IupVbox(
            IupLabel(title),
            IupHbox(
                label_min,
                label_value,
                label_max,
                NULL
            ),
            scale,
            NULL
    );
}

Ihandle *IupQuakeMouseLayout()
{
    Ihandle *tab;

    tab = IupSetAttributes(
            IupHbox(
                IupVbox(
                    IupQuakeSetToggle("Reverse mouse", "m_pitch", "-0.022", "0.022", 0),
                    IupQuakeSetToggle("Use automatic sensitivity scaling", "m_autosens", "1", "0", 1),
                    IupQuakeScale("Mouse sensitivity", 1.00, 20.00, 0.1, "sensitivity", 3.00),
                    NULL
                ),
                IupFill(),
                NULL
            ),
            "HOMOGENEOUS=YES"
        );
    IupSetAttributes(tab, "GAP=5");
    return tab;
}

