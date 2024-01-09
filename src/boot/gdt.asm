gdt_start:
    dq 0x0                      ; the GDT starts with 8-byte of null

; GDT for code segment descriptor
gdt_code: 
    dw 0xffff                   ; segment length
    dw 0x0                      ; segment base
    db 0x0                      ; segment base
    
    ; flags: present privilige "descriptor type code/data" code conforming readable accessed
    ; ->        1       00               1                   1       0         1        0
    db 10011010b
    
    ; flags: granualarity "32bit default" "64bit seg" AVL limit
    ;             1              1             0       0   1111 (0xF)
    db 11001111b

    db 0x0                      ; segment base

; GDT for data segment descriptor
gdt_data:
    dw 0xffff                   ; segment length
    dw 0x0                      ; segment base
    db 0x0                      ; segment base

    ; flags: present privilige "descriptor type code/data" code "expand down" writable accessed
    ; ->        1       00                  1                0         0         1         0
    db 10010010b

    ; flags: granualarity "32bit default" "64bit seg" AVL limit
    ;             1              1             0       0   1111 (0xF)
    db 11001111b

    db 0x0                      ; segment base

gdt_end:

; GDT descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; size (16 bit), always one less of its true size
    dd gdt_start                ; address (32 bit)

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
