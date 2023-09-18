//feature_manager.h
#ifndef FEATURE_MANAGER_H
#define FEATURE_MANAGER_H
#pragma once

#include "quantum.h"
#include "stdbool.h"
#include "stdint.h"

#include "feature/feature_key.h"
#include "feature/log/log.h"

#ifdef COUNTER_KEYS_ENABLE
#include "feature/counter_keys/counter_keys.h"
#endif

bool process_record_feature(uint16_t keycode, keyrecord_t *record);

#endif // FEATURE_MANAGER_H
