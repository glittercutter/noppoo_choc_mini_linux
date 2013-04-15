noppoo_choc_mini_linux
==============================

Use this to build: g++ -Os noppoo_choc_mini_linux.cpp -o noppoo_choc_mini_linux -l X11

Fix the numlock not toggling and switching to a tty under X.
Must be root to switch tty (use chvt).

Strangely the caplocks led work properly if remapped to another key with xmodmap, ex.;
remapping to 'control right': "keycode 0x69 = Caps_Lock"
