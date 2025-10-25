TARGET    = main
MCPU      = cortex-m4
STARTUP   = startup_stm32f401rctx
LOADER    = STM32F401RCTX_FLASH.ld
OBJCOPY   = arm-none-eabi-objcopy
CC        = arm-none-eabi-gcc

INCLUDE1  = Drivers/CMSIS/Device/ST/STM32F4xx/Include
INCLUDE2  = Drivers/CMSIS/Include
ST_INCL   = Core/Startup
INC_H     = inc

SRC       := $(wildcard *.c)
OBJ       := $(patsubst %.c,build/%.o,$(SRC))

CFLAGS = -mcpu=$(MCPU) -g3 --specs=nano.specs -mthumb -mfloat-abi=soft -Wall -I$(INC_H) -DSTM32F401xC

all: build/$(TARGET).hex

build:
	mkdir -p build

build/%.o: %.c | build
	$(CC) $(CFLAGS) -I$(INCLUDE1) -I$(INCLUDE2) -I$(INC_H) -std=gnu11 \
	-c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -o $@ $<

$(STARTUP).o: $(ST_INCL)/$(STARTUP).s | build
	$(CC) $(CFLAGS) -DDEBUG -c -x assembler-with-cpp -o $@ $<

build/$(TARGET).elf: $(OBJ) $(STARTUP).o $(LOADER) Makefile
	$(CC) -o $@ $(OBJ) $(STARTUP).o -mcpu=$(MCPU) --specs=nosys.specs -T"$(LOADER)" \
	-Wl,-Map=build/$(TARGET).map -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb \
	-Wl,--start-group -lc -lm -Wl,--end-group
	arm-none-eabi-size $@

build/$(TARGET).hex: build/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $@