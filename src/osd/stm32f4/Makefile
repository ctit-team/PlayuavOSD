include ../Makefile.defs

# product's details
PRODUCT = libstm32f4
OUTDIR = lib
LIB = $(OUTDIR)/$(PRODUCT).a

# tool's options
CINCS += -I "inc" \
		 -I "Libraries/STM32_USB_OTG_Driver/inc" \
		 -I "Libraries/STM32_USB_Device_Library/Class/cdc/inc" \
		 -I "Libraries/STM32_USB_Device_Library/Core/inc" \
		 -I "Libraries/STM32F4xx_StdPeriph_Driver/inc" \
		 -I "Libraries/CMSIS/ST/STM32F4xx/Include" \
		 -I "Libraries/CMSIS/Include"

# inputs
CFILES = Libraries/STM32_USB_Device_Library/Class/cdc/src/usbd_cdc_core.c \
		 Libraries/STM32_USB_Device_Library/Core/src/usbd_core.c \
		 Libraries/STM32_USB_Device_Library/Core/src/usbd_desc.c \
		 Libraries/STM32_USB_Device_Library/Core/src/usbd_ioreq.c \
		 Libraries/STM32_USB_Device_Library/Core/src/usbd_req.c \
		 Libraries/STM32_USB_OTG_Driver/src/usb_dcd_int.c \
		 Libraries/STM32_USB_OTG_Driver/src/usb_core.c \
		 Libraries/STM32_USB_OTG_Driver/src/usb_dcd.c \
		 Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c \
		 Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c \
		 Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c \
		 Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c \
		 Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c \
		 Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c \
		 Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c \
		 Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c \
		 Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c \
		 Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c \
		 Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c \
		 Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c \
		 Libraries/STM32F4xx_StdPeriph_Driver/src/misc.c

# phony rules
.PHONY: all clean

all: $(LIB)

clean:
	-@rm -f $(LIB)
	-@find . -name *.o -delete

# file rules
$(LIB): $(CFILES:.c=.o)
	mkdir -p $(OUTDIR)
	$(AR) rcs $@ $^
