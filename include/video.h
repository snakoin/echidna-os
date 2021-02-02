#ifndef VIDEO_H
#define VIDEO_H

#include "types.h"

namespace Screen {
    void set_blink(bool blink);
    bool is_blink();
    inline static char x, y = 0;
    inline static unsigned char attribute = 0b00000111;
    inline static unsigned char *screen = (unsigned char *) 0xb8000;
    class Terminal {
        private:
            void show_cursor(void);
        public:
            Terminal();
            void clear(void);
            void scroll_up(u8 n);
            void put_char(unsigned char c);
            void print_string(const char *string);
            void print_string(const char *string, unsigned char attribute);
            void print_string(const char *string, char x, char y);
            void set_attribute(unsigned char attribute);
            char get_x();
            char get_y();
    };
}

#endif
