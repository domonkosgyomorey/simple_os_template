[org 0x7c00]

    mov ah, 0x0                     ; graphicsal settings
    mov al, 0x13                     ; 0x13 for gaphics mode and 0x2 for text mode

    mov [GRAPHICS_MODE], al         ; save graphics mode for later
    int 0x10                        ; change graphics

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

    mov eax, [GRAPHICS_MODE]
    call KERNEL_OFFSET
    jmp $

%include "boot/print.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm"

BOOT_DRIVE db 0
GRAPHICS_MODE db 0

times 510 - ($-$$) db 0
dw 0xaa55