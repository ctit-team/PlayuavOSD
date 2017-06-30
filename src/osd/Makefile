include Makefile.defs

# product's details
PRODUCT := firmware

# tool's options
CINCS += -I "../../lib/mavlink/v1.0" \
		 -I "freertos/FreeRTOS/Source/portable/GCC/ARM_CM4F" \
		 -I "freertos/FreeRTOS/Source/include" \
		 -I "stm32f4/inc" \
		 -I "stm32f4/Libraries/STM32_USB_OTG_Driver/inc" \
		 -I "stm32f4/Libraries/STM32_USB_HOST_Library/Core/inc" \
		 -I "stm32f4/Libraries/STM32_USB_Device_Library/Class/cdc/inc" \
		 -I "stm32f4/Libraries/STM32_USB_Device_Library/Core/inc" \
		 -I "stm32f4/Libraries/STM32F4xx_StdPeriph_Driver/inc" \
		 -I "stm32f4/Libraries/CMSIS/ST/STM32F4xx/Include" \
		 -I "stm32f4/Libraries/CMSIS/Include"

CFLAGS += -std=gnu99
LDFLAGS += -Wl,-T,script.ld
LDLIBS += -lm -lc -lfreertos -lstm32f4
LDPATH += -L "freertos/FreeRTOS/Library" -L "stm32f4/lib"

# inputs
CFILES := main.c \
		 system_stm32f4xx.c \
		 stm32f4xx_it.c \
		 board.c \
		 led.c \
		 spi.c \
		 usart2.c \
		 osdvar.c \
		 font_outlined8x8.c \
		 font_outlined8x14.c \
		 fonts.c \
		 graphengine.c \
		 m2dlib.c \
		 m3dlib.c \
		 math3d.c \
		 max7456.c \
		 osdconfig.c \
		 osdcore.c \
		 osdmavlink.c \
		 osdproc.c \
		 UAVObj.c \
		 uavtalk.c \
		 usb_bsp.c \
		 usbd_cdc_vcp.c \
		 usbd_usr.c \
		 printf2.c

ASFILES := startup.s

# outputs
EXE := $(PRODUCT)
BIN := $(PRODUCT).bin
HEX := $(PRODUCT).hex
OFILES := $(CFILES:.c=.o) $(ASFILES:.s=.o)

# phony rules
.PHONY: all clean stm32f4 freertos

all: $(HEX)

clean:
	-@rm -f *.o $(HEX) $(BIN) $(EXE)
	-@$(MAKE) -C freertos clean
	-@$(MAKE) -C stm32f4 clean

stm32f4:
	$(MAKE) -C stm32f4

freertos:
	$(MAKE) -C freertos

# file rules
$(HEX): $(BIN)
	../../tools/px_mkfw.py --board_id 90 --description "Firmware for the PLAYUAVOSD board" --image $^ > $@

$(BIN): $(EXE)
	$(CP) -O binary -S $^ $@

$(EXE): stm32f4 freertos $(OFILES)
	$(LD) $(LDFLAGS) -o $@ $(OFILES) $(LDLIBS)
