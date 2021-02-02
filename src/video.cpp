#include "types.h"
#include "io.h"
#include "std.h"

#include "video.h"

using namespace Screen;

void move_cursor(u8 x, u8 y) {
    u16 cursor_position;
    cursor_position = y * 80 +x;
    outb(0x3d4, 0x0f);
    outb(0x3d5, (u8) cursor_position);
    outb(0x3d4, 0x0e);
    outb(0x3d5, (u8) (cursor_position >> 8));
}

void Screen::set_blink(bool blink) {
    inb(0x3da);
    outb(0x3c0, 0x30);
    u8 b = inb(0x3c1);
    if (blink) {
        outb(0x3c0, (b & 0xf7));
    } else {
        outb(0x3c0, (b & 0x8));
    }
}

bool Screen::is_blink() {
    inb(0x3da);
    outb(0x3c0, 0x30);
    u8 b = inb(0x3c1);
    if ((b & 0xf7)) {
        return true;
    } else {
        return false;
    }
}

Terminal::Terminal() {
    move_cursor(x, y);
}

void Terminal::clear()
{
    for (int i = 0; i < 0xfa0 / 2; i++) {
        Screen::screen[i * 2] = 0x0;
        Screen::screen[i * 2 + 1] = Screen::attribute;
    }
}

// scroll up the screen n times
void Terminal::scroll_up(u8 n) {
    // copy visible lines at the start of the screen
    for (int line = n; line <= 24; line++) {
        for (int byte = 0; byte < 80 * 2; byte++) {
            Screen::screen[(line - n) * 80 * 2 + byte] = Screen::screen[line * 80 * 2 + byte];
        }
    }
    // clear copied lines
    for (int line = 24; line <= 24; line++) {
        for (int byte = 0; byte < 80 * 2; byte+=2) {
            Screen::screen[line * 80 * 2 + byte] = 0;
            Screen::screen[line * 80 * 2 + byte + 1] = 0x07;
        }
    }
    y -= n;
    if (y < 0) y = 0;
}

void Terminal::put_char(unsigned char c)
{
    if (c == '\n') {
        x = 0;
        y++;
    } else if (c == '\t') {
        x = x + 8 - (x % 8);
    } else if (c == '\r') {
        x = 0;
    } else {
        Screen::screen[x * 2 + y * 2 * 80] = c;
        Screen::screen[x * 2 + y * 2 * 80 + 1] = Screen::attribute;
        x++;
    }
    if (x >= 80) {
        x = 0;
        y++;
    }
    if (y > 24) {
        scroll_up(y - 24);
    }
    show_cursor();
}

void Terminal::print_string(const char *string)
{
    while (*string != 0) {
        put_char(*string);
        string++;
    }
}

void Terminal::print_string(const char *string, unsigned char attribute) {
    unsigned char previous_attribute = Screen::attribute;
    Screen::attribute = attribute;
    while (*string != 0) {
        put_char(*string);
        string++;
    }
    //show_cursor();
    Screen::attribute = previous_attribute;
}

void Terminal::print_string(const char *string, char x, char y) {
    char previous_x = Screen::x;
    char previous_y = Screen::y;
    Screen::x = x;
    Screen::y = y;
    while(*string != 0) {
        put_char(*string);
        string++;
    }
    Screen::x = previous_x;
    Screen::y = previous_y;
}

void Terminal::set_attribute(unsigned char attribute) {
    Screen::attribute = attribute;
}

void Terminal::show_cursor(void) {
    move_cursor(x, y);
}

char Terminal::get_x() {
    return x;
}

char Terminal::get_y() {
    return y;
}
