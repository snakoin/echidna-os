.extern isr_default_int, isr_clock_int, isr_kbd_int
.global _asm_default_int, _asm_irq_0, _asm_irq_1

.macro save_registers
    pushal
    push %ds
    push %es
    push %fs
    push %gs
    push %ebx
    movw $0x10, %bx
    pop %ebx
.endm

.macro restore_registers
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popal
.endm

_asm_default_int:
    save_registers
    call isr_default_int
    mov $0x20, %al
    out %al, $0x20
    restore_registers
    iret

_asm_irq_0:
    save_registers
    call isr_clock_int
    movb $0x20, %al
    out %al, $0x20
    restore_registers
    iret

_asm_irq_1:
    save_registers
    call isr_kbd_int
    movb $0x20, %al
    out %al, $0x20
    restore_registers
    iret
