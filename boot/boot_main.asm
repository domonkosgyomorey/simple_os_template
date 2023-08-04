[org 0x7c00]
KERNEL_OFFSET equ 0x1000        ; The same one we used when linking the kernel

    mov [BOOT_DRIVE], dl        ; Remember that the BIOS sets us the boot drive in 'dl' on boot
    mov bp, 0x9000
    mov sp, bp

    mov si, MSG_REAL_MODE 
    call bios_print
    call bios_print_nl

    ; read the kernel from disk
    mov si, MSG_LOAD_KERNEL
    call bios_print
    call bios_print_nl

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

    mov esi, MSG_PROT_MODE
    call print_string_pm
    call KERNEL_OFFSET          ; Give control to the kernel
    jmp $                       ; Stay here when the kernel returns control to us (if ever)

%include "boot/print.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm"

BOOT_DRIVE db 0                 ; It is a good idea to store it in memory because 'dl' may get overwritten
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE db "Landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

times 510 - ($-$$) db 0
dw 0xaa55
