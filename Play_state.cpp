//
//  Play_state.cpp
//  game
//
//  Created by Xinyuan Huang on 10/19/13.
//
//

#include "Play_state.h"

using namespace Zeni;
using namespace std;

void Play_State::on_push() {
    get_Window().set_mouse_state(Window::MOUSE_HIDDEN);
}

void Play_State::on_pop() {
    get_Controllers().reset_vibration_all();
}

void Play_State::on_cover() {
    get_Controllers().reset_vibration_all();
}

void Play_State::on_controller_button(const SDL_ControllerButtonEvent &event) {
    if(event.button == SDL_CONTROLLER_BUTTON_BACK && event.state == SDL_PRESSED)
        get_Game().push_Popup_Menu_State();
}