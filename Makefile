C_SOURCES = $(wildcard kernel/*.c drivers/*.c x86_64/*.c libc/*.c shell/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h x86_64/*.h libc/*.h shell/*.h)
OBJ = ${C_SOURCES:.c=.o x86_64/interrupt.o} 

CC = gcc
CFLAGS = -g -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs \
		 -Wall -Wextra -Werror -no-pie -fno-pic

os_img: boot/boot_main.bin kernel.bin
	cat $^ > os_img

kernel.bin: boot/kernel_entry.o ${OBJ}
	ld -m elf_i386	-o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/kernel_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ 

run: os_img
	qemu-system-i386 -fda os_img

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o libc/*.o shell/*.o
