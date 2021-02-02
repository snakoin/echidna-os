.extern isr_default_int, isr_kbd_int
.global _asm_default_int, _asm_irq_0

_asm_default_int:
    call isr_default_int
    mov $0x20, %al
    out %al, $0x20
    iret

_asm_irq_0:
    call isr_kbd_int
    movb $0x20, %al
    out %al, $0x20
    iret
