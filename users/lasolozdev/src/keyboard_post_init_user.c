#include "quantum.h"
#include "transactions.h"
#include "features/layer_lock.h"

void keyboard_post_init_user(void) {
    #ifdef TAP_LOCKING_LAYERS_ENABLE
    transaction_register_rpc(USER_SYNC_LAYER_LOCK, user_sync_layer_lock_slave_handler);
    #endif
}
