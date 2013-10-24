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

// right-hand coordinate system
// default camera is facing positive-x direction
// with upside of the camera in pos-z direction
Play_State::Play_State()
:time_passed(0),
m_ball(Point3f(0.0f, 0.0f, 100.0f)),
m_camera(Point3f(0.0f, -300.0f, 200.0f),
         Quaternion(),
         1.0f, 100000.0f),
m_velocity(0, 0, 0), m_collided(false)
{
    set_pausable(true);
    m_camera.adjust_yaw(Global::pi_over_two);
    
}
void Play_State::on_push() {
    get_Window().set_mouse_state(Window::MOUSE_HIDDEN);
    m_chrono.start();
}

void Play_State::on_pop() {
}


void Play_State::on_key(const SDL_KeyboardEvent &event) {
    switch(event.keysym.sym) {
        case SDLK_UP:
            m_controls.forward = event.type == SDL_KEYDOWN;
            break;
            
        case SDLK_LEFT:
            m_controls.left = event.type == SDL_KEYDOWN;
            break;
            
        case SDLK_DOWN:
            m_controls.back = event.type == SDL_KEYDOWN;
            break;
            
        case SDLK_RIGHT:
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
    
    float tilt_forward = (m_controls.forward - m_controls.back) * 0.2f * processing_time;
    float tilt_leftward = (m_controls.left - m_controls.right) * 0.2f * processing_time;
    m_world.tilt(tilt_forward, tilt_leftward);
    
    float time_step = processing_time > 0.005f ? 0.005f : processing_time;
    for (; processing_time > 0.0f; processing_time -= time_step) {
        //  Gravity has its effect
        m_velocity += Vector3f(0.0f, 0.0f, -time_step * 9.8 * 50.0f);
        
        // Try to move
        bool collided = partial_step(time_step);
        
        if (collided && !m_collided) {
            cout << collided << endl;
            m_collided = true;
            bounce();
        }
        else if (!collided) {
            m_collided = false;
        }
        else {
            cout << "stupid" << endl;
            m_ball.move_to(m_world.get_plane_position(m_ball.get_body()));
        }
    }

    
    time_passed = time_total;
    
    
}

bool Play_State::partial_step(const float &time_step) {
    bool result = false;
    const Point3f backup_position = m_ball.get_body().get_center();
    //const Point3f backup_position = m_world.get_plane_position(m_ball.get_body());
    
    m_ball.move_to(m_velocity * time_step + backup_position);
    
    /** If collision with the plane has occurred, roll things back **/
    if(m_ball.get_body().shortest_distance(m_world.get_body()) < 2) {
        cout << m_ball.get_body().get_center().z << "collided" << endl;
        m_ball.move_to(backup_position);
        cout << m_ball.get_body().get_center().z << endl;
        result = true;
        
    }
    return result;
}

void Play_State::bounce()
{
    Vector3f plane_normal = m_world.get_body().get_normal();
    Vector3f projection = plane_normal.normalized() * m_velocity * plane_normal.normalized();
    Vector3f along_plane = m_velocity - projection;
    m_velocity = along_plane - projection;
    
    
}

void Play_State::render() {
    Video &vr = get_Video();
    vr.set_3d(m_camera);
    
    m_world.render();
    m_ball.render();
}
