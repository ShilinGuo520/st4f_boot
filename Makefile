
TARGET = bootloader

CROSS_COMPILE     ?= arm-none-eabi-

############### Compilation configuration ################
AS = $(CROSS_COMPILE)as
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
SIZE = $(CROSS_COMPILE)size
OBJCOPY = $(CROSS_COMPILE)objcopy

PROCESSOR = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16

INCLUDES = -Iinclude -I./


CFLAGS += $(PROCESSOR) $(INCLUDES)
CFLAGS += -Wall -fno-strict-aliasing 
CFLAGS += -O0 -g3


ASFLAGS = $(PROCESSOR) $(INCLUDES)

LDFLAGS = -Mmap > $(TARGET).map
LDFLAGS += -T ./cm4/bootloader.ld

ALL = start_up.o main.o

$(TARGET).bin:$(TARGET).elf
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin

start_up.o:./cm4/start_up.S
	$(AS) $(ASFLAGS) $< -o $@

main.o:main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf:$(ALL)
	$(LD) $(LDFLAGS) $(ALL) --output $(TARGET).elf

clean:
	rm -f *.o *.map *.elf *.bin *.obj
