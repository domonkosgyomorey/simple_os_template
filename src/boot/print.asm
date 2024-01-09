[bits 16]

; Print a null terminated string with BIOS
; parameters: si - string
bios_print:
    pusha
bios_print_start:
    lodsb
    cmp al, 0 
    je bios_print_done
    mov ah, 0x0e
    int 0x10
    jmp bios_print_start

bios_print_done:
    popa
    ret

bios_print_nl:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a            ; newline char
    int 0x10
    mov al, 0x0d            ; carriage return
    int 0x10
    
    popa
    ret

; Print a number in hex format
; params: 'dx' - number
bios_print_hex:
    pusha
    mov cx, 0

bios_hex_loop:
    cmp cx, 4
    je bios_hex_end
    
    mov ax, dx
    and ax, 0x000f
    add al, 0x30
    cmp al, 0x39
    jle bios_hex_skip
    add al, 7

bios_hex_skip:
    mov bx, bios_hex_out + 5
    sub bx, cx
    mov [bx], al
    ror dx, 4

    add cx, 1
    jmp bios_hex_loop

bios_hex_end:
    mov di, bios_hex_out
    call bios_print
    popa
    ret

bios_hex_out:
    db '0x0000',0

; Print a null terminated string into the VGA memory
; Parameters: esi - string
[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_OB_BLACK equ 0x0f

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY

print_string_pm_loop:
    lodsb
    mov ah, WHITE_OB_BLACK
    cmp al, 0
    je print_string_pm_done
    mov [edx], ax
    add edx, 2
    jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret
