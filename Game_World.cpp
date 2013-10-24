//
//  Game_World.cpp
//  game
//
//  Created by Xinyuan Huang on 10/20/13.
//
//

#include "Game_World.h"

#include <zenilib.h>
#include <cmath>

using namespace std;
using namespace Zeni;
using namespace Zeni::Collision;

Game_World::Game_World()
: m_point(Point3f(0, 0, 0)), m_normal(Vector3f(0, 0, 1)),
m_scale(Vector3f(10.0f, 1.0f, 1.0f)),
m_rotation(Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f)),
tilt_forward(0), tilt_leftward(0),
m_wall(Point3f(20.0f, 50.0f, 0.0f), Vector3f(1.0f, 2.0f, 2.5f),
       Quaternion::Axis_Angle(Vector3f(0.0f, 0.0f, 1.0f), Global::pi_over_two))
{
    if(!m_instance_count)
        m_model = new Model("models/p3road.3DS");
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

bool Game_World::collide(const Sphere &ball) {
    Vector3f radius_vector = ball.get_radius() * m_normal.normalized();
    float vertical_projection = radius_vector * Vector3f(0, 0, 1);
    float cos_theta = vertical_projection / ball.get_radius();
    float center_to_plane_vertical = ball.get_radius() / cos_theta;
    
    float x_dist = ball.get_center().x - m_body.get_point().x;
    float theta = acos(cos_theta);
    float plane_to_ground = x_dist * tan(theta);
    
    cout << ball.get_center().z - m_body.get_point().z << " " << center_to_plane_vertical + plane_to_ground << endl;
    
    return (ball.get_center().z - m_body.get_point().z) < (center_to_plane_vertical + plane_to_ground);
    
}

Point3f Game_World::get_plane_position(const Sphere &ball)
{
    Vector3f radius_vector = ball.get_radius() * m_normal.normalized();
    float vertical_projection = radius_vector * Vector3f(0, 0, 1);
    float cos_theta = vertical_projection / ball.get_radius();
    float center_to_plane_vertical = ball.get_radius() / cos_theta;
    
    float x_dist = abs(ball.get_center().x - m_body.get_point().x);
    float theta = acos(cos_theta);
    float plane_to_ground = x_dist * tan(theta);
    
    Point3f result(ball.get_center().x, ball.get_center().y, center_to_plane_vertical + plane_to_ground + 5);
    if (result.z > ball.get_center().z + 20) {
        result.z = ball.get_center().z + 20;
    }
    //cout << "displace from " << ball.get_center().z << "to " << result.z << endl;
    
    return result;
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
