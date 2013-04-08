// glittercutter - April 2013
//
// Use this to build: g++ -Os noppoo_choc_mini_numlock.cpp -o noppoo_choc_mini_numlock -l X11
//
// Running this program in background fix the numlock not toggling under X.
//
// Caplocks led work properly if remapped to another key with xmodmap.
// Using control right here: ' keycode 0x69 = Caps_Lock '


#include <iostream>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define NUMLOCK_KEYCODE 77

int main()
{
    Display* dpy = XOpenDisplay(0);
    XEvent ev;
    Window grabWindow = DefaultRootWindow(dpy);

    const bool ownerEvents = false;
    const int pointerMode = GrabModeAsync;
    const int keyboardMode = GrabModeAsync;

    XGrabKey(dpy, NUMLOCK_KEYCODE, AnyModifier, grabWindow, ownerEvents, pointerMode, keyboardMode);

    // Coudln't find a way to get an accurate state
    // We assume numlock is not enabled for our local state
    bool numlockEnabled = false;

    while (42)
    {
        XNextEvent(dpy, &ev);
        switch (ev.type)
        {
            case KeyPress:
                switch (ev.xkey.keycode)
                {
                    case NUMLOCK_KEYCODE:
                    {
                        std::string cmd("numlockx ");

                        if (numlockEnabled) cmd += "off";
                        else cmd += "on";

                        if (system(cmd.c_str()))
                        {
                            std::cout<<"Error executing command: '"<<cmd<<"'"<<std::endl;
                            return 1;
                        }

                        numlockEnabled = !numlockEnabled;

                        break;
                    }
                }
                break;

            default:
                break;
        }
    }

    XCloseDisplay(dpy);
    return 0;
}
