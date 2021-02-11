#include "types.h"
#include "video.h"
#include "io.h"
#include "std.h"
#include "keyboard.h"

extern "C" void isr_default_int(void) {
    Screen::Terminal terminal;
    //terminal.print_string("default int\n");
    return;
}

extern "C" void isr_clock_int(void) {
    static int tic = 0;
    static int sec = 0;
    tic++;
    if (tic % 100 == 0) {
        sec++;
        tic = 0;
        Screen::Terminal terminal;
        terminal.print_string("clock\n");
    }
}

extern "C" void isr_kbd_int(void) {
    u8 i;
    static bool lshift;
    static bool rshift;
    static bool alt;
    static bool ctrl;
    static bool altgr;
    static bool df;

    do {
        i = inb(0x64);
    } while((i & 0x01) == 0);

    i = inb(0x60);
    i--;

    Screen::Terminal terminal;
    if (i < 0x80) {
        switch(i) {
            case 0x29:
                lshift = true;
                break;
            case 0x35:
                rshift = true;
                break;
            case 0x1c:
                ctrl = true;
                break;
            case 0x37:
                if (df) {
                    altgr = true;
                    df = false;
                } else {
                    alt = true;
                }
                break;
            default:
                unsigned int c = 0;
                if (altgr && (rshift || lshift)) {
                    c = i * 4 + 3;
                } else if (lshift || rshift) {
                    c = i * 4 + 1;
                } else if (altgr) {
                    c = i * 4 + 2;
                } else {
                    c = i * 4 + 0;
                }
                if (azerty_map[c] != 0) {
                    terminal.put_char(azerty_map[c]);
                }
                break;
        }
    } else {
        i -= 0x80;
        switch(i) {
            case 0x29:
                lshift = false;
                break;
            case 0x35:
                rshift = false;
                break;
            case 0x1c:
                ctrl = false;
                break;
            case 0x37:
                if (df) {
                    altgr = false;
                    df = false;
                } else {
                    alt = false;
                }
                break;
            case (0xdf-0x80):
                df = true;
                break;
        }
    }
}
