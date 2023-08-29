#rules.mk
DEFERRED_EXEC_ENABLE = yes
DYNAMIC_TAPPING_TERM_ENABLE = yes
NKRO_ENABLE = yes

MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes

DYNAMIC_MACRO_ENABLE = yes
COMBO_ENABLE = yes
LEADER_ENABLE = yes
SWAP_HANDS_ENABLE = yes
TAP_DANCE_ENABLE = no

OS_DETECTION_ENABLE = yes
CONSOLE_ENABLE = yes
RAW_ENABLE = yes

SRC += feature/log/log.c

SRC += feature/leader_key/leader_key.c
SRC += feature/raw_hid/controller.c
SRC += feature/os_detect/os_detect.c

SRC += feature/mod_keys/mod_keys.c
SRC += feature/feature_manager.c

SRC += feature/keymap_ascii/keymap_ascii.c
SRC += feature/counter_keys/counter_keys.c
