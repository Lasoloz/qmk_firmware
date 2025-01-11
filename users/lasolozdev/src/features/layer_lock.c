#include "layer_lock.h"

#ifdef TAP_LOCKING_LAYERS_ENABLE
static layer_lock_state_t global_layer_state = { false };

void user_sync_layer_lock_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const layer_lock_state_t *m2s = (const layer_lock_state_t*)in_data;
    global_layer_state.raise_locked = m2s->raise_locked;
}
#endif
