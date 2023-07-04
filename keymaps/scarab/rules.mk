#rules.mk
DYNAMIC_MACRO_ENABLE = yes
LEADER_ENABLE = yes
CONSOLE_ENABLE = yes
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
SWAP_HANDS_ENABLE = yes

COMBO_ENABLE = yes
ifeq ($(strip $(COMBO_ENABLE)), yes)
  VPATH += keyboards/gboards
endif

RAW_ENABLE = no
ifeq ($(strip $(RAW_ENABLE)), yes)
  SRC += feature/app_keys/app_keys.c
endif

OS_DETECTION_ENABLE = no
ifeq ($(strip $(OS_DETECTION_ENABLE)), yes)
  SRC += feature/os_keys/os_keys.c
endif


SRC += feature/mod_keys/mod_keys.c

SRC += feature/feature_manager.c
SRC += feature/keymap_ascii/keymap_ascii.c
SRC += feature/counter_keys/counter_keys.c
#SRC += feature/timer_keys/timer_keys.c
#SRC += feature/morse_keys/morse_keys.c
#SRC += feature/arch_tap_keys/arch_tap_keys.c

#SRC += feature/textflow/textflow_keys.c
#SRC += feature/textflow/parser.c
#SRC += feature/textflow/interpreter.c
#SRC += feature/textflow/textflow_variables.c
