#ifndef OS_DETECT_H
#define OS_DETECT_H
#pragma once

#include "quantum.h"
#include "os_detection.h"
#include "feature/log/log.h"

bool process_record_os(uint16_t keycode, keyrecord_t *record);

// todo: modify keys based on OS

#endif // OS_DETECT_H
