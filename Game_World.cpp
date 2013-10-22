//
//  Game_World.cpp
//  game
//
//  Created by Xinyuan Huang on 10/20/13.
//
//

#include "Game_World.h"

#include <zenilib.h>

using namespace std;
using namespace Zeni;
using namespace Zeni::Collision;

Game_World::Game_World()
: m_point(Point3f(0, 0, 0)), m_normal(Vector3f(0, 0, 1)),
m_scale(Vector3f(1.0f, 1.0f, 1.0f)),
m_rotation(Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f)),
m_wall(Point3f(20.0f, 50.0f, 0.0f), Vector3f(1.0f, 2.0f, 2.5f),
       Quaternion::Axis_Angle(Vector3f(0.0f, 0.0f, 1.0f), Global::pi_over_two))
{
    if(!m_instance_count)
        m_model = new Model("models/p3wall.3DS");
    ++m_instance_count;
    
    create_body();
}


Game_World::~Game_World() {
    
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
}

void Game_World::render() {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    
    m_model->set_translate(m_point);
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    //m_model->set_rotate(m_rotation);
    
    m_model->render();
    
    m_wall.render();
}

void Game_World::collide() {
    
}

void Game_World::tilt(const float &forward, const float &leftward)
{
    tilt_forward += forward;
    tilt_leftward += leftward;
    m_rotation = Quaternion(0, -tilt_leftward, -tilt_forward);

    Quaternion normal_rotation(0, -leftward, -forward);
    
    m_normal = normal_rotation * m_normal;
    //cout << "m_normal " << m_normal.x << "," << m_normal.y << "," << m_normal.z << endl;
    create_body();
}

void Game_World::create_body() {
    m_body = Plane(m_point, m_normal);
    //m_source->set_position(m_corner + m_rotation * m_scale / 2.0f);
}

Model * Game_World::m_model = 0;
unsigned long Game_World::m_instance_count = 0lu;
