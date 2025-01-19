#include "quantum.h"
#include "transactions.h"
#include "features/layer_lock.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifndef TAP_LOCKING_LAYERS_ENABLE
    return true;
    #else
    static const uint16_t QK_TAP_LOCKING_END = QK_KB_0 + TAP_LOCKING_LAYER_COUNT;
    static bool tapped = false;

    if (!is_keyboard_master()) {
        return true;
    }

    if (keycode >= QK_KB_0 && keycode < QK_TAP_LOCKING_END) {
        uint8_t layer_offset = keycode - QK_KB_0;
        tapped = attempt_locking_tapped_layer(tapped, TAP_LOCKING_STARTING_LAYER + layer_offset, record);
        return false;
    }

    tapped = false;

    if (keycode >= TG(0) && keycode < TG(16) && !record->event.pressed) {
        layer_lock_state_t *prev_lock_state = update_locked_state(false, 0);

        if (prev_lock_state->is_locked) {
            layer_off(prev_lock_state->layer);
            return false;
        }
    }

    return true;
    #endif
}
