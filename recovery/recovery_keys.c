#include <linux/input.h>

#include "recovery_ui.h"
#include "common.h"
#include "extendedcommands.h"

int int_ext_switch = 0;

int device_toggle_display(volatile char* key_pressed, int key_code) {
    int alt = key_pressed[KEY_LEFTALT] || key_pressed[KEY_RIGHTALT];
    if (alt && key_code == KEY_L)
        return 1;
    // allow toggling of the display if the correct key is pressed, and the display toggle is allowed or the display is currently off
    if (ui_get_showing_back_button()) {
        return 0;
        //return get_allow_toggle_display() && (key_code == KEY_HOME || key_code == KEY_MENU || key_code == KEY_END);
    }
    return get_allow_toggle_display() && (key_code == KEY_HOME || key_code == KEY_MENU || key_code == KEY_END);
}

int device_handle_key(int key_code, int visible) {
    if (visible) {
        switch (key_code) {
            case 172:
		if ( int_ext_switch == 1 )
		{
		    if (ensure_path_unmounted("/sdcard") != 0)
		    {
			ui_print("Can't unmount External SD!\n");
			return NO_ACTION;
		    }
		    setup_data_media();
		    __system("cp -f /etc/recovery_int.fstab /etc/recovery.fstab");
		    load_volume_table();
		    int_ext_switch = 0;
//		    ui_print("External SD -> Internal SD\n");
		    ui_end_menu();
		    ui_clear_key_queue();
		    prompt_and_wait();
		    return GO_BACK;
		}
		else
		{
		    if (ensure_path_mounted("/external_sd") != 0)
		    {
			ui_print("Can't mount External SD!\n");
			return NO_ACTION;
		    }
		    if (ensure_path_unmounted("/external_sd") != 0)
		    {
			ui_print("Can't unmount External SD!\n");
			return NO_ACTION;
		    }
		    __system("rm -f /sdcard");
		    __system("cp -f /etc/recovery_ext.fstab /etc/recovery.fstab");
		    load_volume_table();
		    int_ext_switch = 1;
//		    ui_print("Internal SD -> External SD\n");
		    ui_end_menu();
		    ui_clear_key_queue();
		    prompt_and_wait();
		    return GO_BACK;
		}
            case KEY_CAPSLOCK:
            case KEY_DOWN:
            case KEY_VOLUMEDOWN:
                return HIGHLIGHT_DOWN;

            case KEY_LEFTSHIFT:
            case KEY_UP:
            case KEY_VOLUMEUP:
                return HIGHLIGHT_UP;

            case KEY_POWER:
            case KEY_LEFTBRACE:
            case KEY_ENTER:
            case BTN_MOUSE:
            case KEY_CAMERA:
            case KEY_F21:
            case KEY_SEND:
            case KEY_MENU:
                return SELECT_ITEM;
            
            case KEY_END:
            case KEY_BACKSPACE:
            case KEY_SEARCH:
                if (ui_get_showing_back_button()) {
                    return SELECT_ITEM;
                }
                if (!get_allow_toggle_display() && ui_menu_level > 0) {
                    return GO_BACK;
                }
            case KEY_BACK:
                if (ui_menu_level > 0) {
                    return GO_BACK;
                }

        }
    }

    return NO_ACTION;
}
