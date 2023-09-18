#ifndef ALT_TAB_H
#define ALT_TAB_H

#include "quantum.h"
#include "feature/log/log.h"
#include "../../../aliases.h"
#include <stdbool.h>
#include <stdint.h>

bool leader_sequence_alt_tab(void);
bool leader_record_alt_tab(uint16_t keycode, keyrecord_t *record);
uint32_t alt_tab_timeout_deferred(uint32_t trigger_time, void *cb_arg);

#endif // ALT_TAB_H
