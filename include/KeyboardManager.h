#ifndef KEYBOARDMANAGER
#define KEYBOARDMANAGER

#include <SDL.h>

class KeyboardManager {
public:
    KeyboardManager();

    void UpdateKeyStates(SDL_Event* e);

    bool isKeyUpPressed();
    bool isKeyLeftPressed();
    bool isKeyRightPressed();
    bool isKeyDownPressed();
    bool isKeyZoomInPressed();
    bool isKeyZoomOutPressed();

private:
    bool is_key_up_pressed_;
    bool is_key_left_pressed_;
    bool is_key_right_pressed_;
    bool is_key_down_pressed_;
    bool is_zoom_in_pressed_;
    bool is_zoom_out_pressed_;
};

#endif