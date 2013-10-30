//
//  Home.cpp
//  game
//
//  Created by Xinyuan Huang on 10/29/13.
//
//

#include "Home.h"

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;


Home::Home(const Zeni::Point3f &end_point_a, const Zeni::Point3f &end_point_b,
           const float &radius_,
           const Zeni::Vector3f &scale_,
           const Zeni::Quaternion &rotation_)
: m_end_point_a(end_point_a), m_end_point_b(end_point_b), m_radius(radius_),
m_scale(scale_), m_rotation(rotation_)
{
    m_model = new Model("models/p3disk.3ds");
    create_body();
}

void Home::render() {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    
    // for now
    m_model->set_translate(m_end_point_a);
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    
    m_model->render();
}

void Home::create_body() {
    m_body = Capsule(m_end_point_a, m_end_point_b, m_radius);
    
}
