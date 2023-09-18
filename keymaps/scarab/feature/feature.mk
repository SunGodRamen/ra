# feature.mk

FEATURE_DIR = feature
LOG_DIR = $(FEATURE_DIR)/log
LEADER_DIR = $(FEATURE_DIR)/leader_key
LEADER_SUB_DIR = $(FEATURE_DIR)/leader_key/subfeature
RAW_HID_DIR = $(FEATURE_DIR)/raw_hid
OS_DETECT_DIR = $(FEATURE_DIR)/os_detect
MOD_KEYS_DIR = $(FEATURE_DIR)/mod_keys
KEYMAP_ASCII_DIR = $(FEATURE_DIR)/keymap_ascii
COUNTER_KEYS_DIR = $(FEATURE_DIR)/counter_keys

ifeq ($(LOGGING_ENABLE),yes)
SRC += $(LOG_DIR)/log.c
endif

ifeq ($(HID_CONTROLLER_ENABLE),yes)
SRC += $(RAW_HID_DIR)/rawhid_controller.c $(RAW_HID_DIR)/message_protocol.c
endif

# Check if LEADER_MULTIKEY is set to "yes" and LEADER_HASH is not set to "yes"
ifeq ($(LEADER_MULTIKEY_ENABLE),yes)
ifneq ($(LEADER_HASH_ENABLE),yes)
SRC += $(LEADER_DIR)/leader_multikey.c $(LEADER_SUB_DIR)/alt_tab.c
endif
endif

# Check if LEADER_SCANMOD is set to "yes" and LEADER_HASH is not set to "yes"
ifeq ($(LEADER_SCANMOD_ENABLE),yes)
ifneq ($(LEADER_HASH_ENABLE),yes)
SRC += $(LEADER_DIR)/leader_scanmod.c
endif
endif

# Check if LEADER_HASH is set to "yes" and both LEADER_MULTIKEY and LEADER_SCANMOD are not set to "yes"
ifneq ($(LEADER_MULTIKEY_ENABLE),yes)
ifneq ($(LEADER_SCANMOD_ENABLE),yes)
ifeq ($(LEADER_HASH),yes)
SRC += $(LEADER_DIR)/leader_hash.c
endif
endif
endif

ifeq ($(OS_DETECTION_ENABLE),yes)
SRC += $(OS_DETECT_DIR)/os_detect.c
endif

ifeq ($(MOD_KEYS_ENABLE),yes)
SRC += $(MOD_KEYS_DIR)/mod_keys.c
endif

ifeq ($(FEATURE_KEYS_ENABLE),yes)
SRC += $(FEATURE_DIR)/feature_manager.c

	ifeq ($(COUNTER_KEYS_ENABLE),yes)
	SRC += $(KEYMAP_ASCII_DIR)/keymap_ascii.c
	SRC += $(COUNTER_KEYS_DIR)/counter_keys.c
	endif

endif
