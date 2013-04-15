// glittercutter - April 2013
//
// Use this to build: g++ -Os noppoo_choc_mini_linux.cpp -o noppoo_choc_mini_linux -l X11
//
// Fix the numlock not toggling and switching to a tty under X.
// Must be root to switch tty (use chvt).
//
// Strangely the caplocks led work properly if remapped to another key with xmodmap, ex.;
// remapping to 'control right': "keycode 0x69 = Caps_Lock"


#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define NUMLOCK_KEYCODE 77

#define F1_KEYCODE 67
#define F2_KEYCODE 68
#define F3_KEYCODE 69
#define F4_KEYCODE 70
#define F5_KEYCODE 71
#define F6_KEYCODE 72
#define F7_KEYCODE 73
#define F8_KEYCODE 74
#define F9_KEYCODE 75
#define F10_KEYCODE 76
#define F11_KEYCODE 95
#define F12_KEYCODE 96


Display* g_dpy;


// Cleanup
void atExit()
{
    XCloseDisplay(g_dpy);
}


int main()
{
    std::atexit(*atExit);

    g_dpy = XOpenDisplay(0);
    XEvent ev;
    Window grabWindow = DefaultRootWindow(g_dpy);

    const bool ownerEvents = false;
    const int pointerMode = GrabModeAsync;
    const int keyboardMode = GrabModeAsync;

    XGrabKey(g_dpy, NUMLOCK_KEYCODE, AnyModifier, grabWindow, ownerEvents, pointerMode, keyboardMode);

    const int mod = ControlMask | Mod1Mask;
    XGrabKey(g_dpy, F1_KEYCODE, mod, grabWindow, ownerEvents, pointerMode, keyboardMode);
    XGrabKey(g_dpy, F2_KEYCODE, mod, grabWindow, ownerEvents, pointerMode, keyboardMode);
    XGrabKey(g_dpy, F3_KEYCODE, mod, grabWindow, ownerEvents, pointerMode, keyboardMode);
    XGrabKey(g_dpy, F4_KEYCODE, mod, grabWindow, ownerEvents, pointerMode, keyboardMode);
    XGrabKey(g_dpy, F5_KEYCODE, mod, grabWindow, ownerEvents, pointerMode, keyboardMode);
    XGrabKey(g_dpy, F6_KEYCODE, mod, grabWindow, ownerEvents, pointerMode, keyboardMode);
    XGrabKey(g_dpy, F7_KEYCODE, mod, grabWindow, ownerEvents, pointerMode, keyboardMode);
    XGrabKey(g_dpy, F8_KEYCODE, mod, grabWindow, ownerEvents, pointerMode, keyboardMode);
    XGrabKey(g_dpy, F9_KEYCODE, mod, grabWindow, ownerEvents, pointerMode, keyboardMode);
    XGrabKey(g_dpy, F10_KEYCODE, mod, grabWindow, ownerEvents, pointerMode, keyboardMode);
    XGrabKey(g_dpy, F11_KEYCODE, mod, grabWindow, ownerEvents, pointerMode, keyboardMode);
    XGrabKey(g_dpy, F12_KEYCODE, mod, grabWindow, ownerEvents, pointerMode, keyboardMode);

    // Coudln't find a way to get an accurate state
    // We assume numlock is not enabled for our local state
    bool numlockEnabled = false;

    while (42)
    {
        XNextEvent(g_dpy, &ev);
        switch (ev.type)
        {
            case KeyPress:
            {
                if (ev.xkey.keycode == NUMLOCK_KEYCODE)
                {
                    std::string cmd("numlockx ");

                    if (numlockEnabled) cmd += "off";
                    else cmd += "on";

                    if (system(cmd.c_str()))
                    {
                        std::cout<<"Error executing: '"<<cmd<<"'"<<std::endl;
                        std::cout<<"Exiting..."<<std::endl;
                        return 1;
                    }

                    numlockEnabled = !numlockEnabled;
                }
                else
                {
                    std::string num;

                    switch (ev.xkey.keycode)
                    {
                        case F1_KEYCODE:
                            num = "1";
                            break;
                        case F2_KEYCODE:
                            num = "2";
                            break;
                        case F3_KEYCODE:
                            num = "3";
                            break;
                        case F4_KEYCODE:
                            num = "4";
                            break;
                        case F5_KEYCODE:
                            num = "5";
                            break;
                        case F6_KEYCODE:
                            num = "6";
                            break;
                        case F7_KEYCODE:
                            num = "7";
                            break;
                        case F8_KEYCODE:
                            num = "8";
                            break;
                        case F9_KEYCODE:
                            num = "9";
                            break;
                        case F10_KEYCODE:
                            num = "10";
                            break;
                        case F11_KEYCODE:
                            num = "11";
                            break;
                        case F12_KEYCODE:
                            num = "12";
                            break;
                        default:
                            break;
                    }

                    if (!num.empty())
                    {
                        if (system((std::string("chvt ")+num).c_str()))
                        {
                            std::cout<<"'chvt' must have root access"<<std::endl;
                            std::cout<<"Exiting..."<<std::endl;
                            return 1;
                        }
                    }
                }
            }

            default:
                break;
        }
    }

    return 0;
}
