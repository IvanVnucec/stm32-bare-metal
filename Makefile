.PHONY: all flash clean

TARGET = main
DEBUG = 1
OPT = -Os
BUILD_DIR = build

C_SOURCES =  \
	src/stm32f1xx_it.c \
	src/system_stm32f1xx.c

CPP_SOURCES = \
	src/main.cpp \

ASM_SOURCES =  \
	src/startup_stm32f103xb.s

AS_INCLUDES =
C_INCLUDES =
CXX_INCLUDES =

PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
MD5SUM = md5sum
 
CPU = -mcpu=cortex-m3
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

AS_DEFS = 
C_DEFS = STM32F103xB
CXX_DEFS = STM32F103xB

CFLAGS += -std=c99
CXXFLAGS += -std=c++17

COMMON_FLAGS = $(MCU) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
COMMON_FLAGS += -g -gdwarf-2
endif

COMMON_FLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

ASFLAGS += $(AS_DEFS) $(AS_INCLUDES) 

CFLAGS += $(COMMON_FLAGS)
CFLAGS += $(patsubst %,-D%,$(C_DEFS))
CFLAGS += $(patsubst %,-I%,$(C_INCLUDES))

CXXFLAGS += $(COMMON_FLAGS)
CXXFLAGS += $(patsubst %,-D%,$(CXX_DEFS))
CXXFLAGS += $(patsubst %,-I%,$(CXX_INCLUDES))

LDSCRIPT = src/STM32F103C8Tx_FLASH.ld

LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections -Wl,--print-memory-usage

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

CPPOBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c $(LDSCRIPT) Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cpp $(LDSCRIPT) Makefile | $(BUILD_DIR) 
	$(CXX) -c $(CXXFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s $(LDSCRIPT) Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) $(CPPOBJECTS) Makefile
	$(CC) $(OBJECTS) $(CPPOBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	$(MD5SUM) $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@
	$(MD5SUM) $@

$(BUILD_DIR):
	mkdir $@

flash: $(BUILD_DIR)/$(TARGET).elf
	openocd -f openocd.cfg -c "program {$<} verify reset; shutdown"

clean:
	-rm -fR $(BUILD_DIR)

-include $(wildcard $(BUILD_DIR)/*.d)
