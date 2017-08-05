
TARGET = bootloader

LIB = lib_periph_driver.a

SRC = start_up.o main.o
SRC += $(LIB)

############### Compilation configuration ################
CROSS_COMPILE     ?= arm-none-eabi-

AS = $(CROSS_COMPILE)as
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
SIZE = $(CROSS_COMPILE)size
OBJCOPY = $(CROSS_COMPILE)objcopy

PROCESSOR = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16

INCLUDES = -Iinclude -I./
INCLUDES += -I ./st_lib/STM32F4xx_StdPeriph_Driver/inc
INCLUDES += -I ./st_lib/CMSIS/stm32f4xx/inc
INCLUDES += -I ./st_lib/CMSIS/inc

CFLAGS += $(PROCESSOR) $(INCLUDES)
CFLAGS += -Wall -fno-strict-aliasing 
CFLAGS += -O0 -g3
CFLAGS += -DSTM32F40_41xxx

ASFLAGS = $(PROCESSOR) $(INCLUDES)

LDFLAGS = -Mmap > $(TARGET).map
LDFLAGS += -T ./cm4/bootloader.ld


$(TARGET).bin:$(TARGET).elf
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin

start_up.o:./cm4/start_up.S
	$(AS) $(ASFLAGS) $< -o $@

main.o:main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf:$(SRC)
	$(LD) $(LDFLAGS) $(SRC) --output $(TARGET).elf

lib_periph_driver.a:
	$(MAKE) -C st_lib/STM32F4xx_StdPeriph_Driver/src/


clean:
	rm -f *.o *.map *.elf *.bin *.obj *.a
	$(MAKE) clean -C st_lib/STM32F4xx_StdPeriph_Driver/src/

