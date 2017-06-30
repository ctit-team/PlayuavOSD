include ../Makefile.defs

# product's details
PRODUCT = libfreertos
OUTDIR = FreeRTOS/Library
LIB = $(OUTDIR)/$(PRODUCT).a

# tool's options
CINCS += -I "FreeRTOS/Source/portable/GCC/ARM_CM4F" \
		 -I "FreeRTOS/Source/include"

# inputs
CFILES = FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c \
		 FreeRTOS/Source/portable/MemMang/heap_2.c \
		 FreeRTOS/Source/croutine.c \
		 FreeRTOS/Source/event_groups.c \
		 FreeRTOS/Source/list.c \
		 FreeRTOS/Source/queue.c \
		 FreeRTOS/Source/tasks.c \
		 FreeRTOS/Source/timers.c

# phony rules
.PHONY: all clean

all: $(LIB)

clean:
	-@rm -f $(LIB)
	-@find FreeRTOS/Source -name *.o -delete

# file rules
$(LIB): $(CFILES:.c=.o)
	mkdir -p $(OUTDIR)
	$(AR) rcs $@ $^
