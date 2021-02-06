#include "video.h"
#include "gdt.h"
#include "idt.h"
#include "io.h"

#define KERNEL_INFOS 0b00001110
#define KERNEL_DEFAULT 0b00001111
#define GIT_ADDRESS "https://github.com/Filadelphila/echidna-os"

void init_pic();
int kernel_main();

extern "C" void kernel_start() {
    Screen::set_blink(false);
    Screen::Terminal terminal;
    terminal.clear();

    init_idt();
    terminal.print_string("kernel: idt loaded\n", KERNEL_INFOS);

    init_pic();
    terminal.print_string("kernel: pic configured\n", KERNEL_INFOS);

    init_gdt();
    asm("movw $0x18, %ax\n\tmovw %ax, %ss\n\tmovl $0x20000, %esp\n");

    kernel_main();
}

void task_1(void) {
    while(1);
}

int kernel_main() {
    Screen::Terminal terminal;
    terminal.print_string("kernel: gdt loaded!\n", KERNEL_INFOS);

    sti;
    terminal.print_string("kernel: allowing interrupt\n", KERNEL_INFOS);

    terminal.print_string("Find EchidnaOS project on "GIT_ADDRESS"\n", KERNEL_DEFAULT);
    while(1);
}
