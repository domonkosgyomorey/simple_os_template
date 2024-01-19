SRC_ROOT = src
INCLUDE_ROOT = include
BUILD_DIR = build
C_SOURCES = $(wildcard $(SRC_ROOT)/boot/*.c $(SRC_ROOT)/drivers/*.c $(SRC_ROOT)/kernel/*.c $(SRC_ROOT)/libc/*.c $(SRC_ROOT)/shell/*.c)
HEADERS = $(wildcard $(INCLUDE_ROOT)/*.h $(INCLUDE_ROOT)/boot/*.h $(INCLUDE_ROOT)/kernel/*.h $(INCLUDE_ROOT)/drivers/*.h $(INCLUDE_ROOT)/libc/*.h $(INCLUDE_ROOT)/shell/*.h)
OBJ = ${C_SOURCES:$(SRC_ROOT)/%.c=$(BUILD_DIR)/%.o} $(BUILD_DIR)/kernel/interrupt.o 

CC = gcc
CFLAGS = -m32 -g -nostdlib -nostdinc -fno-builtin -pipe \
		 -Wall -Wextra -Werror -fno-pic \
		 -Werror=implicit-function-declaration \
		 -fcf-protection -nostartfiles -nodefaultlibs \
		 -I$(INCLUDE_ROOT)

os_img: $(BUILD_DIR)/boot/boot_main.bin $(BUILD_DIR)/kernel.bin
	cat $^ > os_img

$(BUILD_DIR)/kernel.bin: $(BUILD_DIR)/boot/kernel_entry.o ${OBJ}
	ld -m elf_i386 -Map=output.map --oformat binary -T linker.ld -o $@ $^ 

run: os_img
	qemu-system-i386 -fda os_img

$(BUILD_DIR)/%.o: $(SRC_ROOT)/%.c ${HEADERS}
	mkdir -p $(dir $@)
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_ROOT)/%.asm
	mkdir -p $(dir $@)
	nasm $< -f elf -o $@

$(BUILD_DIR)/%.bin: $(SRC_ROOT)/%.asm
	mkdir -p $(dir $@)
	nasm $< -f bin -o $@

clean:
	rm -rfv build/*