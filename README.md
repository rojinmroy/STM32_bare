# STM32 Bare-Metal Firmware

Minimal bare-metal firmware for an **STM32F103C8T6 (Cortex-M3)**, developed using the ARM GCC toolchain without an IDE, HAL, RTOS, or vendor-generated project.

The project is primarily a hands-on exercise in understanding the basic firmware build and startup flow.

## What I'm Learning

* Cortex-M reset and startup
* Vector table and stack initialization
* Linker scripts and MCU memory layout
* `.text`, `.rodata`, `.data`, and `.bss`
* Basic C runtime initialization
* Memory-mapped peripheral registers
* Direct GPIO configuration
* ARM GCC and GNU Make
* ELF vs. binary firmware images
* SWD programming with ST-Link and OpenOCD
* GDB-based firmware debugging
* Basic GitHub Actions CI

Some of these topics are implemented in the current firmware, while others are still being explored.

## Hardware

* **MCU:** STM32F103C8T6
* **CPU:** ARM Cortex-M3
* **Flash:** 64 KiB
* **RAM:** 20 KiB
* **Board:** STM32F1 Blue Pill
* **Debugger:** ST-Link V2
* **LED:** PC13

## Current Firmware

The firmware currently:

1. Enables the GPIOC clock.
2. Configures PC13 as a push-pull output.
3. Toggles PC13 continuously.

The GPIO is accessed directly through memory-mapped registers rather than a HAL.

## Build

Required tools:

```text
arm-none-eabi-gcc
arm-none-eabi-objcopy
make
openocd
gdb-multiarch
```

Build:

```bash
make
```

This produces:

```text
firmware.elf
firmware.bin
```

The ELF is used for debugging; the binary is the raw firmware image.

## Flash

Using ST-Link and OpenOCD:

```bash
make flash
```

The Makefile programs, verifies, and resets the target.

## Debug

The project uses **GDB + OpenOCD + ST-Link**.

Start OpenOCD:

```bash
openocd -f interface/stlink.cfg -f target/stm32f1x.cfg
```

In another terminal:

```bash
arm-none-eabi-gdb firmware.elf
```

Then:

```gdb
target extended-remote localhost:3333
monitor reset halt
break main
continue
```

See [`docs/debugging.md`](docs/debugging.md) for the complete debugging workflow.

## Project Structure

```text
stm32-baremetal/
├── README.md
├── Makefile
├── linker.ld
├── startup.c
├── main.c
├── docs/
│   └── debugging.md
└── .github/
    └── workflows/
        └── build.yml
```

* `main.c` — application and GPIO code
* `startup.c` — vector table and reset handler
* `linker.ld` — Flash/RAM layout and section placement
* `Makefile` — build and flash commands
* `docs/debugging.md` — GDB/OpenOCD debugging procedure
* `.github/workflows/build.yml` — automated build

## Current Limitations

This is intentionally a minimal project.

It does not yet include:

* Interrupt-driven peripherals
* UART
* Timers
* DMA
* Drivers
* RTOS
* Hardware-in-the-loop testing

The current LED delay is a simple busy loop and is not intended to provide accurate timing.

## Next Steps

Possible extensions:

* Interrupt handling
* SysTick-based timing
* UART driver
* Timer driver
* Watchdog
* Unit testing
* Hardware-in-the-loop testing
* More structured driver development
