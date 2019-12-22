#include "KeyboardManager.h"

KeyboardManager::KeyboardManager() {
    is_key_down_pressed_ = false;
    is_key_left_pressed_ = false;
    is_key_right_pressed_ = false;
    is_key_up_pressed_ = false;
    is_zoom_in_pressed_ = false;
    is_zoom_out_pressed_ = false;
}

void KeyboardManager::UpdateKeyStates(SDL_Event* e) {
    is_key_down_pressed_ = false;
    is_key_left_pressed_ = false;
    is_key_right_pressed_ = false;
    is_key_up_pressed_ = false;
    is_zoom_in_pressed_ = false;
    is_zoom_out_pressed_ = false;
    
    if (e->type != SDL_KEYDOWN) return;

    switch( e->key.keysym.sym ) {
        case SDLK_UP:
            is_key_up_pressed_ = true;
            break;
        case SDLK_DOWN:
            is_key_down_pressed_ = true;
            break;          
        case SDLK_LEFT:
            is_key_left_pressed_ = true;
            break;
        case SDLK_RIGHT:
            is_key_right_pressed_ = true;
            break;
        case SDLK_PAGEDOWN:
            is_zoom_in_pressed_ = true;
            break;
        case SDLK_PAGEUP:
            is_zoom_out_pressed_ = true;
            break;
        default:
            break;
    }
}

bool KeyboardManager::isKeyUpPressed() {
    return is_key_up_pressed_;
}

bool KeyboardManager::isKeyLeftPressed() {
    return is_key_left_pressed_;
}

bool KeyboardManager::isKeyRightPressed() {
    return is_key_right_pressed_;
}

bool KeyboardManager::isKeyDownPressed() {
    return is_key_down_pressed_;
}

bool KeyboardManager::isKeyZoomInPressed() {
    return is_zoom_in_pressed_;
}

bool KeyboardManager::isKeyZoomOutPressed() {
    return is_zoom_out_pressed_;
}