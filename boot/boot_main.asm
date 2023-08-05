[org 0x7c00]

    KERNEL_OFFSET equ 0x1000

    mov [BOOT_DRIVE], dl
    mov bp, 0x9000
    mov sp, bp

    mov bx, KERNEL_OFFSET       ; Read from disk and store in 0x1000
    mov dh, 31
    mov dl, [BOOT_DRIVE]
    call disk_load

    cli
    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 0x1                             ; set 32-bit mode bit in cr0
    mov cr0, eax
    jmp CODE_SEG:init_protected_mode

[bits 32]
init_protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call KERNEL_OFFSET
    jmp $

%include "boot/print.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm"

BOOT_DRIVE db 0

times 510 - ($-$$) db 0
dw 0xaa55
