#include "quantum.h"
#include "features/layer_lock.h"

#ifdef RGB_MATRIX_ENABLE
#ifdef TAP_LOCKING_LAYERS_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    layer_lock_state_t *layer_lock_state = get_global_layer_lock_state();
    if (!layer_lock_state->is_locked) {
        return false;
    }

    uint8_t hue = rgb_matrix_get_hue();
    uint8_t value = rgb_matrix_get_val();
    uint8_t saturation = rgb_matrix_get_sat();
    if (saturation < 128) {
        // Increase saturation in so there is a difference between normal white keys and important keys
        // (in case saturation is down)
        saturation = 128;
    }

    hsv_t alt_1_hsv = { (hue + 85) % 256, saturation, value };
    hsv_t alt_2_hsv = { (alt_1_hsv.h + 85) % 256, saturation, value };
    hsv_t irrelevant_hsv = { hue, 16, value <= 48 ? 0 : 16 };
    rgb_t alt_1_rgb = hsv_to_rgb(alt_1_hsv);
    rgb_t alt_2_rgb = hsv_to_rgb(alt_2_hsv);
    rgb_t irrelevant_rgb = hsv_to_rgb(irrelevant_hsv);

    if (layer_lock_state->layer == 2) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED) {
                    uint16_t keycode = keymap_key_to_keycode(2, (keypos_t){col,row});
                    switch (keycode) {
                        case KC_P0:
                        case KC_P1:
                        case KC_P2:
                        case KC_P3:
                        case KC_P4:
                        case KC_P5:
                        case KC_P6:
                        case KC_P7:
                        case KC_P8:
                        case KC_P9:
                            if (host_keyboard_led_state().num_lock) {
                                rgb_matrix_set_color(index, alt_1_rgb.r, alt_1_rgb.g, alt_1_rgb.b);
                            }
                            break;
                        case KC_NUM:
                            if (!host_keyboard_led_state().num_lock) {
                                rgb_matrix_set_color(index, alt_1_rgb.r, alt_1_rgb.g, alt_1_rgb.b);
                                break;
                            }
                        case KC_PENT:
                        case KC_PSLS:
                        case KC_PAST:
                        case KC_PMNS:
                        case KC_PDOT:
                        case KC_PPLS:
                            rgb_matrix_set_color(index, alt_2_rgb.r, alt_2_rgb.g, alt_2_rgb.b);
                                break;
                        case KC_NO:
                            rgb_matrix_set_color(index, irrelevant_rgb.r, irrelevant_rgb.g, irrelevant_rgb.b);
                            break;
                    }
                }
            }
        }
    }

    return false;
}
#endif
#endif
