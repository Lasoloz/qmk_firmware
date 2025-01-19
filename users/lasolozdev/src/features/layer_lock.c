#include "layer_lock.h"

#ifdef TAP_LOCKING_LAYERS_ENABLE
static layer_lock_state_t global_layer_state = { false, 0 };
static layer_lock_state_t prev_layer_state = { false, 0 };

layer_lock_state_t *get_global_layer_lock_state(void) {
    return &global_layer_state;
}

void user_sync_layer_lock_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const layer_lock_state_t *m2s = (const layer_lock_state_t*)in_data;
    global_layer_state.is_locked = m2s->is_locked;
    global_layer_state.layer = m2s->layer;
}

layer_lock_state_t *update_locked_state(bool is_locked, uint8_t layer) {
    prev_layer_state.is_locked = global_layer_state.is_locked;
    prev_layer_state.layer = global_layer_state.layer;
    global_layer_state.is_locked = is_locked;
    global_layer_state.layer = layer;
    if (prev_layer_state.is_locked != is_locked || prev_layer_state.layer != layer) {
        transaction_rpc_send(USER_SYNC_LAYER_LOCK, sizeof(global_layer_state), &global_layer_state);
    }
    return &prev_layer_state;
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
        update_locked_state(false, layer);

        return current_tapped_state;
    }

    update_locked_state(true, layer);

    return current_tapped_state;
}
#endif
