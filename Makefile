CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -g3
LDFLAGS = -T linker.ld -nostdlib

firmware.elf: main.o startup.o
	$(CC) $(LDFLAGS) $^ -o $@

firmware.bin: firmware.elf
	$(OBJCOPY) -O binary $< $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

startup.o: startup.c
	$(CC) $(CFLAGS) -c $< -o $@

flash: firmware.elf
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg \
		-c "program firmware.elf verify reset exit"

clean:
	rm -f *.o firmware.elf firmware.bin

.PHONY: flash clean
