#include "quantum.h"
#include "transactions.h"
#include "features/layer_lock.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifndef TAP_LOCKING_LAYERS_ENABLE
    return true;
    #else
    static const uint16_t QK_TAP_LOCKING_END = QK_KB_0 + TAP_LOCKING_LAYER_COUNT;
    static const uint16_t TG_EXIT_END = TG(TAP_LOCKING_STARTING_LAYER) + TAP_LOCKING_LAYER_COUNT;
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

    if (keycode >= TG(TAP_LOCKING_STARTING_LAYER) && keycode < TG_EXIT_END) {
        update_locked_state(false, 0);
    }

    return true;
    #endif
}
