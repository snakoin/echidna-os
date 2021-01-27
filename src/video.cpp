#include "types.h"
#include "io.h"

#include "video.h"

void move_cursor(u8 x, u8 y) {
    u16 cursor_position;
    cursor_position = y * 80 +x;
    outb(0x3d4, 0x0f);
    outb(0x3d5, (u8) cursor_position);
    outb(0x3d4, 0x0e);
    outb(0x3d5, (u8) (cursor_position >> 8));
}

Video::Video() : screen((unsigned char *) 0xb8000), x(0), y(0), attribute(0b00000111)
{}

void Video::print_string(const char *string)
{
    while (*string != 0) {
        put_char(*string);
        string++;
    }
    show_cursor();
}

void Video::clear()
{
    for (int i = 0; i < 0xfa0; i++) {
        screen[i * 2 + 1] = attribute;
    }
}

void Video::put_char(unsigned char c)
{
    if (c == '\n') {
        x = 0;
        y++;
        return;
    }
    if (c == '\t') {
        x = x + 8 - (x % 8);
        return;
    }
    if (c == '\r') {
        x = 0;
        return;
    }
    screen[x * 2 + y * 2 * 80] = c;
    screen[x * 2 + y * 2 * 80 + 1] = attribute;
    x++;
    if (x == 80) {
        x = 0;
        y++;
    }
    // TODO: scrolling system
    if (y == 24) {
        x = 0;
        y = 0;
    }
}

void Video::set_attribute(unsigned char attribute) {
    this->attribute = attribute;
}

void Video::show_cursor(void) {
    move_cursor(x, y);
}
