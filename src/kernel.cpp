#include "video.h"
#include "gdt.h"

int kernel_main(Video video);

extern "C" void kernel_start() {
    Video video;
    video.print_string("Welcome to Echidna!\n");
    video.print_string("Find the project on github.com/Filadelphila/echidnaOS\n");

    video.set_attribute(0b00010111);
    video.print_string("kernel: loading new gdt...\n");
    init_gdt();
    asm(
            "movw $0x18, %ax\n"
            "movw %ax, %ss\n"
            "movl $0x20000, %esp\n"
            );
    kernel_main(video);
}

int kernel_main(Video video) {
    video.set_attribute(0b00100111);
    video.print_string("kernel: gdt loaded!\n");
    while (1);
}
