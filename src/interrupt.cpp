#include "types.h"
#include "video.h"
#include "io.h"
#include "std.h"

//Video::Terminal terminal((unsigned char *) 0xb8000);

extern "C" void isr_default_int(void) {
    return;
}

extern "C" void isr_kbd_int(void) {
    Screen::Terminal terminal;
    u8 i;
    do {
        i = inb(0x64);
    } while((i & 0x01) == 0);
    i = inb(0x60);
    if (i < 10) {
        terminal.scroll_up(4);
        return;
    }
    if (i < 0x80) {
        terminal.print_string("key pressed\n", 0b00001110);
    }
}
