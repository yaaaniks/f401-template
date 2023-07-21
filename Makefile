# ______________________________________________________________________________________________
# all the files will be generated with this name (main.elf, main.bin, main.hex, etc)
PROJECT=main

MCU=STM32F401xx

INCLUDE_DIR=./inc
SOURCE_DIR=./src
CORE_DIR=./core
CMSIS_DIR=./cmsis
CPU_DIR=./cpu
BUILD_DIR=build

# DEF=-DSTM32F401xC
OPT=-O3 -g0 -flto
SRC=$(SOURCE_DIR)/main.c 
SRC+=$(SOURCE_DIR)/system_stm32f4xx.c
SRC+=$(CORE_DIR)/timer.c $(CORE_DIR)/rcc.c
###################################################

CSTANDARD = -std=c11

# External libraries
# LIBRARIES = lib

CMSIS = $(CMSIS_DIR)/device
CORE = $(CMSIS_DIR)/core
###################################################

# Location of linker script and startup file
LINKER_SCRIPT = $(CPU_DIR)/STM32F401CC_FLASH.ld
STARTUP_SCRIPT = $(CPU_DIR)/startup_stm32f401xc.s
###################################################

# vpath %.a ./cpu
VPATH +=$(SOURCE_DIR) $(CPU_DIR) $(CORE_DIR)

CC=arm-none-eabi-gcc
GDB=arm-none-eabi-gdb
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
SIZE=arm-none-eabi-size


CFLAGS  = -Wall -g $(CSTANDARD) -Os $(OPT)
CFLAGS += -mlittle-endian -mcpu=cortex-m4 -march=armv7e-m -mthumb
CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -D $(MCU)
CFLAGS += -I$(INCLUDE_DIR)
CFLAGS += -I$(CORE_DIR)
CFLAGS += -I$(SOURCE_DIR)
CFLAGS += -I$(CMSIS)
CFLAGS += -I$(CORE)

LDFLAGS += -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/$(PROJECT).map -ffreestanding -Xlinker
LDFLAGS+=-L$(LIBS_STM_PATH)/build -T$(LINKER_SCRIPT)

###################################################

ROOT=$(shell pwd)

OBJS = $(addprefix $(BUILD_DIR)/objs/,$(SRC:.c=.o))
DEPS = $(addprefix $(BUILD_DIR)/deps/,$(SRC:.c=.d))
DEPS += rcc.h
OBJS += rcc.o


###################################################

all: proj

-include $(DEPS)

proj: $(BUILD_DIR) $(BUILD_DIR)/$(PROJECT).elf

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/deps $(BUILD_DIR)/objs

$(BUILD_DIR)/objs/%.o : src/%.c $(BUILD_DIR) $(DEPS)
	$(CC) $(OBJS) $(CFLAGS) -c -o $@ $< -MMD -MF $(BUILD_DIR)/deps/$(*F).d

$(BUILD_DIR)/$(PROJECT).elf: $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(STARTUP_SCRIPT) 
	$(OBJCOPY) -O ihex $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).hex
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).bin
	$(OBJDUMP) -St $(BUILD_DIR)/$(PROJECT).elf >$(BUILD_DIR)/$(PROJECT).lst
	$(SIZE) $(BUILD_DIR)/$(PROJECT).elf

program: all
	@sleep 1
	st-flash write `pwd`/$(BUILD_DIR)/$(PROJECT).bin 0x08000000

debug: program
	$(GDB) -x extra/gdb_cmds $(PROJECT).elf

clean:
	find ./ -name '*~' | xargs rm -f	
	rm -rf $(BUILD_DIR)

reallyclean: clean
	$(MAKE) -C clean

.PHONY: all proj program debug clean reallyclean