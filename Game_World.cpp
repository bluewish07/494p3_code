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
#include <algorithm>

using namespace std;
using namespace Zeni;
using namespace Zeni::Collision;

Game_World::Game_World()
: m_disk(Point3f(0.0f, 0.0f, 0.0f), Point3f(0.0f, 0.0f, -10.f)),
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
    m_disk.render();
    
    //m_wall.render();
}

/*bool Game_World::collide(const Sphere &ball) {
    Vector3f radius_vector = ball.get_radius() * m_normal.normalized();
    float vertical_projection = radius_vector * Vector3f(0, 0, 1);
    float cos_theta = vertical_projection / ball.get_radius();
    float center_to_plane_vertical = ball.get_radius() / cos_theta;
    
    float x_dist = ball.get_center().x - m_body.get_point().x;
    float theta = acos(cos_theta);
    float plane_to_ground = x_dist * tan(theta);
    
    cout << ball.get_center().z - m_body.get_point().z << " " << center_to_plane_vertical + plane_to_ground << endl;
    
    return (ball.get_center().z - m_body.get_point().z) < (center_to_plane_vertical + plane_to_ground);
    
}*/

Point3f Game_World::get_plane_position(const Sphere &ball)
{
    /*
    Vector3f radius_vector = ball.get_radius() * m_normal.normalized();
    float vertical_projection = radius_vector * Vector3f(0, 0, 1);
    float cos_theta = vertical_projection / ball.get_radius();
    float center_to_plane_vertical = ball.get_radius() / cos_theta;
    float xy_dist = (Point3f(ball.get_center().x, ball.get_center().y, 0) - Point3f(m_body.get_point().x, m_body.get_point().y, 0)).magnitude();
    float theta = acos(cos_theta);
    float plane_to_ground = xy_dist * tan(theta);
    
    cout << center_to_plane_vertical + plane_to_ground << endl;
    
    Point3f result(ball.get_center().x, ball.get_center().y, center_to_plane_vertical + plane_to_ground + 5);
    if (result.z > ball.get_center().z + 20) {
        result.z = ball.get_center().z + 20;
    }
    cout << "displace from " << ball.get_center().z << "to " << result.z << endl;
    
     */
    
    return m_disk.get_plane_position(ball);
}

void Game_World::tilt(const float &forward, const float &leftward)
{
    m_disk.tilt(forward, leftward);
}

void Game_World::create_body() {
    // m_body = Plane(m_point, m_normal);
    //m_source->set_position(m_corner + m_rotation * m_scale / 2.0f);
}

Model * Game_World::m_model = 0;
unsigned long Game_World::m_instance_count = 0lu;
