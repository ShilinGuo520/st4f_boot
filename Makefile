

CROSS_COMPILE     ?= arm-none-eabi-

############### Compilation configuration ################
AS = $(CROSS_COMPILE)as
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)gcc
SIZE = $(CROSS_COMPILE)size
OBJCOPY = $(CROSS_COMPILE)objcopy

PROCESSOR = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16

INCLUDES = -Iinclude -I./

CFLAGS += -O0 -g3

ASFLAGS = $(PROCESSOR) $(INCLUDES)

startup_stm32f40xx.o:startup_stm32f40xx.s
	$(AS) $(ASFLAGS) $< -o $@



clean:
	rm -f *.o
