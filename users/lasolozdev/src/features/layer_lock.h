#pragma once

#include "quantum.h"
#include "transactions.h"

#ifdef TAP_LOCKING_LAYERS_ENABLE

#ifndef TAP_LOCKING_TIMEOUT
#   define TAP_LOCKING_TIMEOUT 200
#endif

#ifndef TAP_LOCKING_LAYER_COUNT
#   define TAP_LOCKING_LAYER_COUNT 2
#endif

#ifndef TAP_LOCKING_STARTING_LAYER
#   define TAP_LOCKING_STARTING_LAYER 1
#endif

typedef struct _layer_lock_state_t {
    bool is_locked;
    uint8_t layer;
} layer_lock_state_t;

layer_lock_state_t *get_global_layer_lock_state(void);

void user_sync_layer_lock_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data);

void update_locked_state(bool is_locked, uint8_t layer);

bool attempt_locking_tapped_layer(bool current_tapped_state, uint8_t layer, keyrecord_t *record);
#endif
