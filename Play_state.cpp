//
//  Play_state.cpp
//  game
//
//  Created by Xinyuan Huang on 10/19/13.
//
//

#include "Play_state.h"
#include <cmath>
#include <iostream>

using namespace Zeni;
using namespace std;

// left-hand coordinate system
// default camera is facing positive-x direction
// with upside of the camera in neg-z direction
Play_State::Play_State()
:time_passed(0), m_world(),
m_ball(Point3f(0.0f, 100.0f, 0.0f)),
m_camera(Point3f(0.0f, -100.0f, -250.0f),
         Quaternion(),
         1.0f, 100000.0f),
z_speed(10)
{
    set_pausable(true);
    m_camera.adjust_pitch(-Global::pi_over_two); // camera facing pos-z direction
    m_camera.adjust_roll(Global::pi_over_two); // upside of the camera points pos-y
    //m_camera.adjust_pitch(Global::pi_over_two/2);
    
    time_cycle = sqrt(2*(m_ball.get_body().get_center().y - m_ball.get_body().get_radius())/(9.8 * 50));
    cout << "time cycle: " << time_cycle << endl;
}
void Play_State::on_push() {
    get_Window().set_mouse_state(Window::MOUSE_HIDDEN);
    m_chrono.start();
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

void Play_State::perform_logic()
{
    float time_total = m_chrono.seconds();
    float processing_time = time_total - time_passed;
    if (processing_time > 0.05) {
        time_passed = time_total;
        
        float z_forward = z_speed * processing_time * 50.f;
        int num_cycles = time_total / time_cycle;
        float effective_time = time_total - time_cycle * num_cycles;
        float height = 0;
        if (!(num_cycles % 2)) {
            height = -(m_ball.get_origin().y - .5 * 9.8 * 50 * pow(effective_time, 2));
        }
        else {
            height = -(m_ball.get_origin().y - .5 * 9.8 * 50 *pow(time_cycle - effective_time, 2));
        }
        //cout << height << endl;
        m_ball.move(0, z_forward, height);
    }
    
    
}

void Play_State::render() {
    Video &vr = get_Video();
    vr.set_3d(m_camera);
    
    m_world.render();
    m_ball.render();
}
