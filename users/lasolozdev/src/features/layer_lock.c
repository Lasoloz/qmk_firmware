#include "layer_lock.h"

#ifdef TAP_LOCKING_LAYERS_ENABLE
static layer_lock_state_t global_layer_state = { false };

void user_sync_layer_lock_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const layer_lock_state_t *m2s = (const layer_lock_state_t*)in_data;
    global_layer_state.raise_locked = m2s->raise_locked;
}

void update_raise_locked_state(bool new_state) {
    bool prev = global_layer_state.raise_locked;
    global_layer_state.raise_locked = new_state;
    if (prev != global_layer_state.raise_locked) {
        transaction_rpc_send(USER_SYNC_LAYER_LOCK, sizeof(global_layer_state), &global_layer_state);
    }
}

bool attempt_locking_tapped_layer(bool current_tapped_state, uint8_t layer, keyrecord_t *record) {
    static uint16_t timer = 0;

    if (record->event.pressed) {
        layer_on(layer);
        timer = record->event.time + TAP_LOCKING_TIMEOUT;
        return true;
    }

    if (!current_tapped_state || timer_expired(record->event.time, timer)) {
        layer_off(layer);
        update_raise_locked_state(false);

        return current_tapped_state;
    }

    update_raise_locked_state(true);

    return current_tapped_state;
}
#endif
