#include "types.hpp"
#include "io.hpp"
#include "std.hpp"

#include "video.hpp"

using namespace Screen;

void move_cursor(u8 x, u8 y) {
    u16 cursor_position;
    cursor_position = y * 80 + x;
    outb(0x3d4, 0xf);
    outb(0x3d5, (u8) cursor_position);
    outb(0x3d4, 0xe);
    outb(0x3d5, (u8) (cursor_position >> 8));
}

void Screen::set_blink(bool blink) {
    inb(0x3da);
    outb(0x3c0, 0x30);
    u8 b = inb(0x3c1);
    if (!blink) {
        outb(0x3c0, (b & 0b11110111));
    } else {
        outb(0x3c0, (b & 0b00001000));
    }
}

bool Screen::is_blink() {
    inb(0x3da);
    outb(0x3c0, 0x30);
    u8 b = inb(0x3c1);
    if ((b & 0b11110111)) {
        return true;
    } else {
        return false;
    }
}

Terminal::Terminal() {
    this->framebuffer = screen;
    move_cursor(x, y);
}

Terminal::Terminal(unsigned char *framebuffer) {
    this->framebuffer = framebuffer;
    move_cursor(x, y);
}

void Terminal::clear()
{
    for (int i = 0; i < 0xfa0 / 2; i++) {
        framebuffer[i * 2] = 0x0;
        framebuffer[i * 2 + 1] = Screen::attribute;
    }
}

// scroll up the screen n times
void Terminal::scroll_up(u8 n) {
    // copy visible lines at the start of the screen
    for (int line = n; line <= 24; line++) {
        for (int byte = 0; byte < 80 * 2; byte++) {
            framebuffer[(line - n) * 80 * 2 + byte] = framebuffer[line * 80 * 2 + byte];
        }
    }
    // clear copied lines
    for (int line = 24 - n + 1; line <= 24; line++) {
        for (int byte = 0; byte < 80 * 2; byte+=2) {
            framebuffer[line * 80 * 2 + byte] = 0;
            framebuffer[line * 80 * 2 + byte + 1] = attribute;
        }
    }
    y -= n;
    if (y < 0) {
        y = 0;
    }
}

void Terminal::put_char(unsigned char c)
{
    switch (c) {
        case '\n':
            x = 0;
            y++;
            break;
        case '\t':
            x = x + 8 - (x % 8);
            break;
        case '\r':
            x = 0;
            break;
        case '\b':
            x--;
            break;
        default:
            framebuffer[x * 2 + y * 2 * 80] = c;
            framebuffer[x * 2 + y * 2 * 80 + 1] = Screen::attribute;
            x++;
            break;
    }
    if (x >= 80) {
        x = 0;
        y++;
    } else if (x < 0) {
        if (y > 0) {
            y--;
            x = 80 - 1;
        }
    }
    if (y > 24) {
        scroll_up(y - 24);
    }
    show_cursor();
}

void Terminal::print_string(const char *str)
{
    while (*str != 0) {
        put_char(*str);
        str++;
    }
}

void Terminal::print_string(const char *str, unsigned char attribute) {
    unsigned char previous_attribute = Screen::attribute;
    Screen::attribute = attribute;
    while (*str != 0) {
        put_char(*str);
        str++;
    }
    Screen::attribute = previous_attribute;
}

void Screen::show_cursor(void) {
    move_cursor(x, y);
}
