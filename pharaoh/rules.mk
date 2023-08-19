# MCU name
MCU = STM32F072

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
NKRO_ENABLE = yes           # Enable N-Key Rollover

CUSTOM_MATRIX = lite
NO_USB_STARTUP_CHECK = yes
LTO_ENABLE = no

SRC += matrix.c
QUANTUM_LIB_SRC += i2c_master.c

LAYOUTS = split_3x5_2

DEFAULT_FOLDER = ra/pharaoh/base

