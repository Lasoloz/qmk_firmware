#include "quantum.h"
#include "transactions.h"
#include "features/keycodes.h"
#include "features/layer_lock.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifndef TAP_LOCKING_LAYERS_ENABLE
    return true;
    #else
    if (!is_keyboard_master()) {
        return true;
    }

    static bool tapped = false;

    if (keycode == KC_SUPER_RAISE) {
        tapped = attempt_locking_tapped_layer(tapped, 2, record);
        return false;
    }

    tapped = false;

    if (keycode == TG(2)) {
        update_raise_locked_state(false);
    }

    return true;
    #endif
}
