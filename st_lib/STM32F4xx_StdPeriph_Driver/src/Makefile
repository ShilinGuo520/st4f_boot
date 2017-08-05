
TARGET = lib_periph_driver.a
SRC = stm32f4xx_gpio.o stm32f4xx_rcc.o

############### Compilation configuration ################
CROSS_COMPILE     ?= arm-none-eabi-

CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar

PROCESSOR = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16

INCLUDES = -I ../inc -I ../../CMSIS/inc -I ../../CMSIS/stm32f4xx/inc


CFLAGS += $(PROCESSOR) $(INCLUDES)
CFLAGS += -Wall -fno-strict-aliasing 
CFLAGS += -O0 -g3
CFLAGS += -DSTM32F40_41xxx


ARFLAGS = -rv



$(TARGET):$(SRC)
	$(AR) $(ARFLAGS) $(TARGET) $(SRC)
	mv $(TARGET) ../../../

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

