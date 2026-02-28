# Makefile
CROSS =
CC      = $(CROSS)gcc
CXX     = $(CROSS)g++
AS      = nasm
LD      = $(CROSS)ld

CFLAGS   = -ffreestanding -O2 -Wall -Wextra -Iinclude
CXXFLAGS = -ffreestanding -O2 -Wall -Wextra -Iinclude -fno-exceptions -fno-rtti
ASFLAGS  = -f elf32
LDFLAGS  = -T linker.ld -ffreestanding -nostdlib -lgcc

OBJDIR = obj
SOURCES_C   = hal/io.c hal/vga.c hal/gdt.c hal/idt.c hal/pic.c hal/timer.c hal/keyboard.c kernel/mm.c
SOURCES_CPP = kernel/main.cpp kernel/print.cpp
SOURCES_ASM = boot.asm

OBJECTS = $(patsubst %.c, $(OBJDIR)/%.o, $(SOURCES_C)) \
          $(patsubst %.cpp, $(OBJDIR)/%.o, $(SOURCES_CPP)) \
          $(patsubst %.asm, $(OBJDIR)/%.o, $(SOURCES_ASM))

# Rust 部分（可选）
RUST_TARGET = rust/target/i686-unknown-none-gnu/release/libomege_rust.a
ifeq ($(wildcard rust),)
    RUST_LIB =
else
    RUST_LIB = $(RUST_TARGET)
    CFLAGS += -DRUST_ENABLED
    CXXFLAGS += -DRUST_ENABLED
endif

all: omege-uos.bin

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.asm
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

$(RUST_TARGET): rust/Cargo.toml rust/src/lib.rs
	cd rust && cargo build --target i686-unknown-none-gnu --release

omege-uos.bin: $(OBJECTS) $(RUST_LIB) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(RUST_LIB)

clean:
	rm -rf $(OBJDIR) omege-uos.bin rust/target

run: omege-uos.bin
	qemu-system-i386 -kernel $<

.PHONY: all clean run