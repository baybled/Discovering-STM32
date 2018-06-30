TEMPLATEROOT = ..

# additional compilation flags

CFLAGS += -O0 -g
ASFLAGS += -g

# project files

OBJS=	$(STARTUP) main.o
OBJS+=  stm32f10x_gpio.o stm32f10x_rcc.o stm32f10x_usart.o uart.o

# include common make file

include $(TEMPLATEROOT)/Makefile.common
