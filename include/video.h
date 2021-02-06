#ifndef VIDEO_H
#define VIDEO_H

#include "types.h"

namespace Screen {
    void set_blink(bool blink);
    bool is_blink();
    static char x, y = 0;
    static unsigned char attribute = 0b00000111;
    static unsigned char *screen = (unsigned char *) 0xb8000;
    class Terminal {
        private:
            unsigned char *framebuffer;
            void show_cursor(void);
        public:
            Terminal();
            Terminal(unsigned char *framebuffer);
            void clear(void);
            void scroll_up(u8 n);
            void put_char(unsigned char c);
            void print_string(const char *str);
            void print_string(const char *str, unsigned char attribute);
            void set_attribute(unsigned char attribute);
    };
}

#endif