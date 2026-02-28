# build.make - 主构建文件

include .path

# 源文件列表
SOURCES_C   := $(wildcard $(HAL_DIR)/*.c) $(wildcard $(KERNEL_DIR)/*.c)
SOURCES_CPP := $(wildcard $(KERNEL_DIR)/*.cpp)
SOURCES_ASM := $(wildcard $(SRC_DIR)/*.asm) $(wildcard $(HAL_DIR)/*.asm)

# 生成的目标文件
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES_C)) \
           $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES_CPP)) \
           $(patsubst $(SRC_DIR)/%.asm, $(OBJ_DIR)/%.o, $(SOURCES_ASM))

# 默认目标
all: $(KERNEL_BIN)

# 创建输出目录
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# 编译 C 文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# 编译 C++ 文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 编译汇编文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

# 编译 Rust 库（如果启用）
$(RUST_TARGET): $(RUST_DIR)/Cargo.toml $(RUST_DIR)/src/lib.rs
	cd $(RUST_DIR) && cargo build --target i686-unknown-none-gnu --release

# 链接内核
$(KERNEL_BIN): $(OBJECTS) $(RUST_LIB) $(SRC_DIR)/linker.ld | $(BIN_DIR)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(RUST_LIB)

# 清理
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(RUST_TARGET)

# 在 QEMU 中运行
run: $(KERNEL_BIN)
	qemu-system-i386 -kernel $<

.PHONY: all clean run