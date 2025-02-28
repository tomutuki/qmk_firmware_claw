
#include "claw44.h"
/*#include "jp_us_overrides.h"

void set_key_override(OVERRIDE_MODE mode) {
    switch (mode) {
        case DISABLE_OVERRIDE:
            key_override_off();
            break;
        case US_KEY_ON_JP_OS_OVERRIDE:
            register_us_key_on_jp_os_overrides();
            key_override_on();
            break;
        case JP_KEY_ON_US_OS_OVERRIDE:
            register_jp_key_on_us_os_overrides();
            key_override_on();
            break;
    }
}

keyboard_config_t keyboard_config;

void eeconfig_init_kb(void){
    keyborard_config.raw = 0;
    eeconfig_update_kb(keyboard_config.raw)
    keyboard_config.override_mode = US_KEY_ON_JP_OS_OVERRIDE;
    set_key_override(US_KEY_ON_JP_OS_OVERRIDE);
    eeconfig_update_kb(keyboard_config.raw);
}
*/


void matrix_init_kb(void) {
    //keyboard_config.raw = eeconfig_read_kb();
    //set_key_override(keyboard_config.override_mode);
    //keyboard_config.override_mode = US_KEY_ON_JP_OS_OVERRIDE;
    //set_key_override(US_KEY_ON_JP_OS_OVERRIDE);
    debug_enable=true;
    debug_matrix=true;
    debug_mouse=true;

    uprintf("Init matrix kb\n");
}

