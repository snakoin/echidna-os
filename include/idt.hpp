#include "types.hpp"

#define IDT_BASE 0x800
#define IDT_SIZE 0xff
#define INT_GATE 0x8e00

void init_idt_desc(u16, u32, u16, struct idtdesc *);
void init_idt(void);

struct idtdesc {
    u16 offset0_15;
    u16 select;
    u16 type;
    u16 offset16_31;
} __attribute__ ((packed));

struct idtr {
    u16 limite;
    u32 base;
} __attribute__ ((packed));

#ifdef __IDT__
    struct idtr kidtr;
    struct idtdesc kidt[IDT_SIZE];
#else
    extern struct idtr kidtr;
    extern struct idtdesc kidt[];
#endif
