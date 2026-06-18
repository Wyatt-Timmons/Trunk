TROS_MEM_VIRT_DIR := $(SRC_DIR)/cbk/mem/virt

TROS_MEM_VIRT_SRCS_NASM := $(wildcard $(TROS_MEM_VIRT_DIR)/*.asm)
TROS_MEM_VIRT_SRCS_CXX  := $(wildcard $(TROS_MEM_VIRT_DIR)/*.cpp)

TROS_MEM_VIRT_OBJS := \
    $(patsubst $(SRC_DIR)/%.asm, $(OBJ_DIR)/%.asm.o, $(TROS_MEM_VIRT_SRCS_NASM)) \
    $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o,     $(TROS_MEM_VIRT_SRCS_CXX))

CBK_OBJS += $(TROS_MEM_VIRT_OBJS)