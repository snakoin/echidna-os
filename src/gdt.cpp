#include "types.h"
#include "std.h"

#define __GDT__
#include "gdt.h"

void init_gdt_desc(u32 base, u32 limite, u8 acces, u8 other,
                   struct gdtdesc *desc)
{
        desc->lim0_15 = (limite & 0xffff);
        desc->base0_15 = (base & 0xffff);
        desc->base16_23 = (base & 0xff0000) >> 16;
        desc->acces = acces;
        desc->lim16_19 = (limite & 0xf0000) >> 16;
        desc->other = (other & 0xf);
        desc->base24_31 = (base & 0xff000000) >> 24;
        return;
}

void init_gdt(void)
{
        // segment descriptor init
        init_gdt_desc(0x0, 0x0, 0x0, 0x0, &kgdt[0]);
        init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &kgdt[1]); // code
        init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &kgdt[2]); // data
        init_gdt_desc(0x0, 0x0, 0x97, 0x0D, &kgdt[3]); // stack

        init_gdt_desc(0x0, 0xfffff, 0xff, 0x0d, &kgdt[4]); // ucode
        init_gdt_desc(0x0, 0xfffff, 0xf3, 0x0d, &kgdt[5]); // udata
        init_gdt_desc(0x0, 0x0, 0xf7, 0x0d, &kgdt[6]); // ustack

        // structure init for gdtr
        kgdtr.limite = GDTSIZE * 8;
        kgdtr.base = GDTBASE;

        // copy gdt to its address
        memcopy((char *) kgdtr.base, (char *) kgdt, kgdtr.limite);

        // load gdtr register
        asm("lgdtl (kgdtr)");

        // segments init
        asm("movw $0x10, %ax\n \
            movw %ax, %ds\n \
            movw %ax, %es\n \
            movw %ax, %fs\n \
            movw %ax, %gs\n \
            ljmp $0x08, $next\n \
            next:\n");
}
