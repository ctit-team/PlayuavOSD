EXE=firmware.elf
BIN=firmware.bin
HEX=firmware.hex

CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy

DEFS = -DUSE_STDPERIPH_DRIVER -DSTM32F4XX -DHSE_VALUE=8000000

MCU = cortex-m4
MCFLAGS = -mcpu=$(MCU) -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -std=gnu99
STMLIBSDIR    = ../../lib/STM32F4-Discovery_FW_V1.1.0/Libraries
STMSPDDIR    = $(STMLIBSDIR)/STM32F4xx_StdPeriph_Driver
STMSPSRCDDIR = $(STMSPDDIR)/src
STMSPINCDDIR = $(STMSPDDIR)/inc
FREERTOSDIR = ../../lib/FreeRTOSV8.2.0/FreeRTOS/Source
USBOTGLIB = $(STMLIBSDIR)/STM32_USB_OTG_Driver
USBDEVICELIB = $(STMLIBSDIR)/STM32_USB_Device_Library
USBHOSTLIB = $(STMLIBSDIR)/STM32_USB_HOST_Library
MAVLINKDIR = ../../lib/mavlink/v1.0

STM32_INCLUDES = -I$(STMLIBSDIR)/CMSIS/Include/ \
				 -I$(STMLIBSDIR)/CMSIS/ST/STM32F4xx/Include/ \
				 -I$(STMSPINCDDIR)/ \
				 -I$(FREERTOSDIR)/include    \
          		 -I$(FREERTOSDIR)/portable/GCC/ARM_CM4F    \
          		 -I$(MAVLINKDIR)    \
          		 -I$(USBDEVICELIB)/Class/cdc/inc    \
          		 -I$(USBDEVICELIB)/Core/inc    \
          		 -I$(USBHOSTLIB)/Core/inc    \
          		 -I$(USBOTGLIB)/inc    \
				 -I../../inc 
OPTIMIZE       = -Os

CFLAGS	= $(MCFLAGS)  $(OPTIMIZE)  $(DEFS) -I../../ $(STM32_INCLUDES)  -Wl,-T,../../linker/stm32_flash.ld
AFLAGS	= $(MCFLAGS) 
#-mapcs-float use float regs. small increase in code size

STM32_USB_OTG_SRC = $(USBOTGLIB)/src/usb_dcd_int.c \
					$(USBOTGLIB)/src/usb_core.c \
					$(USBOTGLIB)/src/usb_dcd.c \

STM32_USB_DEVICE_SRC =	$(USBDEVICELIB)/Class/cdc/src/usbd_cdc_core.c \
						$(USBDEVICELIB)/Core/src/usbd_req.c \
						$(USBDEVICELIB)/Core/src/usbd_core.c \
						$(USBDEVICELIB)/Core/src/usbd_ioreq.c

## list of APP files
SRC  = main.c
SRC += system_stm32f4xx.c
SRC += stm32f4xx_it.c
SRC += board.c
SRC += led.c
SRC += spi.c
SRC += usart2.c
SRC += osdvar.c
SRC += font_outlined8x8.c
SRC += font_outlined8x14.c
SRC += fonts.c
SRC += graphengine.c
SRC += m2dlib.c
SRC += m3dlib.c
SRC += math3d.c
SRC += max7456.c
SRC += osdconfig.c
SRC += osdcore.c
SRC += osdmavlink.c
SRC += osdproc.c
SRC += UAVObj.c
SRC += uavtalk.c
SRC += usb_bsp.c
SRC += usbd_cdc_vcp.c
SRC += usbd_desc.c
SRC += usbd_usr.c
SRC += printf2.c
## used parts of the STM-Library
SRC += $(STMSPSRCDDIR)/stm32f4xx_dma.c
SRC += $(STMSPSRCDDIR)/stm32f4xx_exti.c
SRC += $(STMSPSRCDDIR)/stm32f4xx_flash.c
SRC += $(STMSPSRCDDIR)/stm32f4xx_gpio.c
SRC += $(STMSPSRCDDIR)/stm32f4xx_syscfg.c
SRC += $(STMSPSRCDDIR)/stm32f4xx_pwr.c
SRC += $(STMSPSRCDDIR)/stm32f4xx_rcc.c
SRC += $(STMSPSRCDDIR)/stm32f4xx_rtc.c
SRC += $(STMSPSRCDDIR)/stm32f4xx_spi.c
SRC += $(STMSPSRCDDIR)/stm32f4xx_tim.c
SRC += $(STMSPSRCDDIR)/stm32f4xx_usart.c
SRC += $(STMSPSRCDDIR)/stm32f4xx_can.c
SRC += $(STMSPSRCDDIR)/misc.c
## list of FreeRTOS files
SRC += $(FREERTOSDIR)/portable/GCC/ARM_CM4F/port.c
SRC += $(FREERTOSDIR)/portable/MemMang/heap_2.c
SRC += $(FREERTOSDIR)/croutine.c
SRC += $(FREERTOSDIR)/event_groups.c
SRC += $(FREERTOSDIR)/list.c
SRC += $(FREERTOSDIR)/queue.c
SRC += $(FREERTOSDIR)/tasks.c
SRC += $(FREERTOSDIR)/timers.c
## list of USB_CDC files
SRC += $(STM32_USB_OTG_SRC)
SRC += $(STM32_USB_DEVICE_SRC)
# List ASM source files here
STARTUP = $(STMLIBSDIR)/CMSIS/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f40xx.s

all: $(HEX)

clean:
	rm -f $(HEX) $(BIN) $(EXE) $(SRC:.c=.lst)

$(HEX): $(BIN)
	../../tools/px_mkfw.py --board_id 90 --description "Firmware for the PLAYUAVOSD board" --image $^ > $@

$(BIN): $(EXE)
	$(CP) -O binary -S $^ $@
	
$(EXE): $(SRC) $(STARTUP)
	$(CC) $(CFLAGS) $^ -lm -lc -lnosys -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -o $@
