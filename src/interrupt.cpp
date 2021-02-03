#include "types.h"
#include "video.h"
#include "io.h"
#include "std.h"

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
    if (i < 0x80) {
        char number[5];
        itoa(i, number, 16);
        terminal.print_string("0x", 0b00000111);
        terminal.print_string(number, 0b00000111);
        terminal.put_char('\n');
    }
}
