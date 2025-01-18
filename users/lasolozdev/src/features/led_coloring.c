#include "led_coloring.h"

__attribute__ ((weak))
int keycode_to_led_category(uint8_t layer, uint16_t keycode) {
    return LED_NORMAL;
}

#ifdef RGB_MATRIX_ADDITIONAL_LAYERS
__attribute__ ((weak))
bool layer_led_enabled_as_highest(uint8_t layer) {
    return false;
}
#endif
