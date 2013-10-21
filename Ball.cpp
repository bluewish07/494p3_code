//
//  Ball.cpp
//  game
//
//  Created by Xinyuan Huang on 10/19/13.
//
//


#include "Ball.h"
#include <zenilib.h>

using namespace std;
using namespace Zeni;
using namespace Zeni::Collision;

Ball::Ball(const Point3f &center_, const float &radius_,
             const Vector3f &scale_,
             const Quaternion &rotation_)
:m_center(center_), m_radius(radius_),
m_scale(scale_),
m_rotation(rotation_)
{
    if(!m_instance_count)
        m_model = new Model("models/p3ball.3DS");
    ++m_instance_count;
    
    m_origin = m_center;
    
    create_body();
}


Ball::~Ball() {
    
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
}

void Ball::move(const float &x_movement, const float &z_movement, const float y_pos)
{
    m_center.x += x_movement;
    m_center.y = y_pos;
    m_center.z = z_movement;
}

void Ball::render() {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    
    m_model->set_translate(m_center);
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    
    m_model->render();
}

void Ball::collide() {

}

void Ball::create_body() {
    m_body = Sphere(m_center, m_radius);
    //m_source->set_position(m_corner + m_rotation * m_scale / 2.0f);
}

Model * Ball::m_model = 0;
unsigned long Ball::m_instance_count = 0lu;