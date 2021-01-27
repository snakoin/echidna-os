#ifndef VIDEO_H
#define VIDEO_H

class Video {
    private:
        unsigned char *screen;
        char x, y;
        unsigned char attribute;
        void put_char(unsigned char c);
    public:
        Video();
        void print_string(const char *string);
        void clear(void);
        void set_attribute(unsigned char attribute);
        void show_cursor(void);
};

#endif
