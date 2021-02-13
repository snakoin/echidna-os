.section .multiboot2
header_start:
    .long 0xe85250d6 # magic number
    .long 0 # protected mode code
    .long header_end - header_start # header_length

    # checksum
    .long 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    # required end tag
    .int 0 # type
    .int 0 # flags
    .long 8 # size
header_end:

# stack
.section .bss
.align 16
stack_bottom:
.lcomm stack 0x4000
stack_top:

.global asm_start

.extern kernel_start

.section .text
asm_start:
    movl $stack_top, %esp
    call kernel_start
    hlt
