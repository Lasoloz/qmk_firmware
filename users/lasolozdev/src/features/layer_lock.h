#pragma once

#ifdef TAP_LOCKING_LAYERS_ENABLE

typedef struct _layer_lock_state_t {
    bool raise_locked;
} layer_lock_state_t;

void user_sync_layer_lock_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data);

#endif
