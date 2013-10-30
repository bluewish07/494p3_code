//
//  Play_state.cpp
//  game
//
//  Created by Xinyuan Huang on 10/19/13.
//
//

#include "Play_state.h"
#include "Retry_State.h"
#include "Result_State.h"
#include <cmath>
#include <iostream>
#include <Zeni/Collision.h>

using namespace Zeni;
using namespace std;
using namespace Zeni::Collision;

// right-hand coordinate system
// default camera is facing positive-x direction
// with upside of the camera in pos-z direction
Play_State::Play_State(Zeni::Point3f ball_position, int lives)
:time_passed(0),
m_ball(ball_position),
m_camera(Point3f(0.0f, -200.0f, 300.0f), Quaternion(), 1.0f, 100000.0f),
m_collided(false), m_collision_time(0.0f), m_lives(lives)
{
    set_pausable(true);
    m_camera.adjust_yaw(Global::pi_over_two);
    
}
void Play_State::on_push() {
    get_Window().set_mouse_state(Window::MOUSE_HIDDEN);
    m_world.read_disk_positions("maps/disks_locs.txt");
    m_world.read_wall_positions("maps/walls_locs.txt");
    m_world.update_view(m_camera.position);
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
    
    // winning condition detection
    if (m_world.is_home(m_ball.get_body().get_center())) {
        get_Game().pop_state();
        get_Game().push_state(new Result_State(true));
    }
    
    // losing condition detection
    if (time_total - m_collision_time > 2.0f) {
        cout << "end";
        m_lives--;
        if (m_lives) {
            Point3f ball_position = m_world.reset();
            m_ball.reset(ball_position);
            get_Game().pop_state();
            get_Game().push_state(new Retry_State(ball_position, m_lives));
        }
        else {
            get_Game().pop_state();
            get_Game().push_state(new Result_State(false));
        }
        
    }
    
    float processing_time = time_total - time_passed;
    
    float tilt_forward = (m_controls.forward - m_controls.back) * 0.2f * processing_time;
    float tilt_leftward = (m_controls.left - m_controls.right) * 0.2f * processing_time;
    m_world.tilt(tilt_forward, tilt_leftward);
    
    float time_step = processing_time > 0.005f ? 0.005f : processing_time;
    for (; processing_time > 0.0f; processing_time -= time_step) {
        // Gravity has its effect
        m_ball.set_velocity(m_ball.get_velocity() + Vector3f(0.0f, 0.0f, -time_step * 9.8 * 50.0f));
        
        // move
        partial_step(time_step);
    }
    
    time_passed = time_total;
    
}

void Play_State::partial_step(const float &time_step) {
    const Point3f backup_position = m_ball.get_body().get_center();
    
    m_ball.move_to(m_ball.get_velocity() * time_step + backup_position);
    m_collided = m_world.collide(m_ball, backup_position, !m_collided);
    if (m_collided)
        m_collision_time = m_chrono.seconds();

}


void Play_State::render() {
    m_camera.position.y = m_ball.get_body().get_center().y - 300;
    float ideal_height = m_world.get_ideal_camera_height();
    if (!(ideal_height < -.9 && ideal_height > -1.1)) {
        m_camera.position.z = ideal_height < m_camera.position.z - 1 ? m_camera.position.z - 1 : ideal_height;
    }
    cout << ideal_height << " " << m_camera.position.z << endl;
    m_world.update_view(m_camera.position);

    Video &vr = get_Video();
    vr.set_3d(m_camera);
    
    m_world.render();
    m_ball.render();
}

void Play_State::reset()
{
    m_chrono.reset();
    m_collided = false;
    m_collision_time = 0;
}
