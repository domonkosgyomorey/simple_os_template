; load 'dh' sectors from drive 'dl' into ES:BX
disk_load:
    pusha
    push dx

    mov ah, 0x02                ; read
    mov al, dh                  ; num of sectors
    mov cl, 0x02                ; sector
    mov ch, 0x00                ; cylinder
    mov dh, 0x00                ; head number

    int 0x13
    jc disk_error               ; if error (stored in the carry bit)

    pop dx
    cmp al, dh                  ; BIOS also sets 'al' to the # of sectors read. Compare it.
    jne sectors_error
    popa
    ret


disk_error:
    mov si, DISK_ERROR
    call bios_print
    call bios_print_nl
    ; ah = error code, dl = disk drive that dropped the error
    mov dh, ah
    mov si, dx 
    call bios_print_hex
    jmp disk_loop

sectors_error:
    mov si, SECTORS_ERROR
    call bios_print

disk_loop:
    jmp $


DISK_ERROR: db "Disk read error", 0
SECTORS_ERROR: db "Incorrect number of sectors read", 0