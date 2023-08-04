[org 0x7c00]
KERNEL_OFFSET equ 0x1000        ; The same one we used when linking the kernel

    mov [BOOT_DRIVE], dl        ; Remember that the BIOS sets us the boot drive in 'dl' on boot
    mov bp, 0x9000
    mov sp, bp

    mov bx, KERNEL_OFFSET       ; Read from disk and store in 0x1000
    mov dh, 31                  ; Our future kernel will be larger, make this big
    mov dl, [BOOT_DRIVE]
    call disk_load

    ; disable interrupts, load GDT,  etc. Finally jumps to 'BEGIN_PM'
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1                             ; set 32-bit mode bit in cr0
    mov cr0, eax
    jmp CODE_SEG:init_protected_mode        ; far jump by using a different segment

[bits 32]
init_protected_mode:
    mov ax, DATA_SEG                        ; update the segment registers
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000                        ; update the stack right at the top of the free space
    mov esp, ebp

    call KERNEL_OFFSET          ; Give control to the kernel
    jmp $                       ; Stay here when the kernel returns control to us (if ever)

%include "boot/print.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm"

BOOT_DRIVE db 0                 ; It is a good idea to store it in memory because 'dl' may get overwritten

times 510 - ($-$$) db 0
dw 0xaa55
