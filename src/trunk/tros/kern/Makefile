include src/trunk/tros/kern/init/Makefile
include src/trunk/tros/kern/gdt/Makefile
include src/trunk/tros/kern/interrupts/Makefile

TROS_KERN_DIR := $(SRC_DIR)/trunk/tros/kern

TROS_KERN_SRCS_NASM := $(wildcard $(TROS_KERN_DIR)/*.asm)
TROS_KERN_SRCS_CXX  := $(wildcard $(TROS_KERN_DIR)/*.cpp)

TROS_KERN_OBJS := \
    $(patsubst $(SRC_DIR)/%.asm, $(OBJ_DIR)/%.asm.o, $(TROS_KERN_SRCS_NASM)) \
    $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o,     $(TROS_KERN_SRCS_CXX))

TRUNK_OBJS += $(TROS_KERN_OBJS)