#include "video.h"
#include "gdt.h"
#include "idt.h"
#include "io.h"
#include "std.h"

#define KERNEL_INFOS 0b011100000
#define KERNEL_WARNINGS 0b00000100

int kernel_main(Screen::Terminal test);
void init_pic();

extern "C" void kernel_start() {
    Screen::set_blink(false);
    Screen::Terminal terminal;
    terminal.clear();

    terminal.print_string("kernel: loading idt...\n", KERNEL_INFOS);
    init_idt();
    init_pic();
    terminal.print_string("kernel: idt loaded!\n", KERNEL_INFOS);

    terminal.print_string("kernel: loading gdt...\n", KERNEL_INFOS);
    init_gdt();
    asm("movw $0x18, %ax\n\tmovw %ax, %ss\n\tmovl $0x20000, %esp\n");
    terminal.print_string("kernel: gdt loaded!\n", KERNEL_INFOS);

    kernel_main(terminal);
}

int kernel_main(Screen::Terminal test) {
    sti;
    Screen::Terminal terminal;
    terminal.print_string("kernel: warning!\n", KERNEL_WARNINGS);
    terminal.print_string("Welcome to Echidna!\n");
    terminal.print_string("Find the project on github.com/Filadelphila/echidnaOS\n");
    while (1);
}
