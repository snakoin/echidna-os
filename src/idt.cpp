#define __IDT__
#include "idt.h"

#include "types.h"
#include "std.h"

extern "C" void _asm_default_int(void);
extern "C" void _asm_irq_0(void);

void init_idt_desc(u16 select, u32 offset, u16 type, struct idtdesc *desc) {
    desc->offset0_15 = (offset & 0xffff);
    desc->select = select;
    desc->type = type;
    desc->offset16_31 = (offset & 0xffff0000) >> 16;
}

void init_idt(void) {
    for (int i = 0; i < IDT_SIZE; i++) {
        init_idt_desc(0x08, (u32) _asm_default_int, INT_GATE, &kidt[i]);
    }
    init_idt_desc(0x08, (u32) _asm_irq_0, INT_GATE, &kidt[33]);

    kidtr.limite = IDT_SIZE * 8;
    kidtr.base = IDT_BASE;

    memcopy((char *) kidtr.base, (char *) kidt, kidtr.limite);

    asm("lidtl (kidtr)");
}
