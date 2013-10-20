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

// left-hand coordinate system
// default camera is facing positive-x direction
// with upside of the camera in neg-z direction
Play_State::Play_State()
:m_ball(Point3f(0.0f, 0.0f, 0.0f)),
m_camera(Point3f(0.0f, -100.0f, -250.0f),
         Quaternion(),
         1.0f, 100000.0f)
{
    set_pausable(true);
    m_camera.adjust_pitch(-Global::pi_over_two); // camera facing pos-z direction
    m_camera.adjust_roll(Global::pi_over_two); // upside of the camera points pos-y
}
void Play_State::on_push() {
    get_Window().set_mouse_state(Window::MOUSE_HIDDEN);
}

void Play_State::on_pop() {
}


void Play_State::on_key(const SDL_KeyboardEvent &event) {
    switch(event.keysym.sym) {
        case SDLK_w:
            m_controls.forward = event.type == SDL_KEYDOWN;
            break;
            
        case SDLK_a:
            m_controls.left = event.type == SDL_KEYDOWN;
            break;
            
        case SDLK_s:
            m_controls.back = event.type == SDL_KEYDOWN;
            break;
            
        case SDLK_d:
            m_controls.right = event.type == SDL_KEYDOWN;
            break;
            
        default:
            Gamestate_Base::on_key(event);
            break;
    }
}

void Play_State::render() {
    Video &vr = get_Video();
    vr.set_3d(m_camera);
    
    m_ball.render();
}
