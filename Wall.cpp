#include "Wall.h"
#include <iostream>

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;

Wall::Wall(const Point3f &corner_,
             const Vector3f &scale_,
             const Quaternion &rotation_)
: m_corner(corner_), m_scale(scale_), m_rotation(rotation_)
{
    //m_source(new Sound_Source(get_Sounds()["collide"]))
    if(!m_instance_count)
        m_model = new Model("models/p3wall.3ds");
    ++m_instance_count;
    
    create_body();
}

Wall::Wall(const Wall &rhs)
: m_corner(rhs.m_corner), m_scale(rhs.m_scale), m_rotation(rhs.m_rotation)
{
    ++m_instance_count;
    
    create_body();
}

Wall & Wall::operator=(const Wall &rhs) {
    m_corner = rhs.m_corner;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    create_body();
    
    return *this;
}

Wall::~Wall() {
    
    //delete m_source;
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
}

void Wall::render() {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    
    m_model->set_translate(m_corner);
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    
    m_model->render();
}

void Wall::collide() {
    /*if(!m_source->is_playing())
        m_source->play();*/
}

void Wall::create_body() {
    m_body = Parallelepiped(m_corner,
                            m_rotation * (100 * m_scale.get_i()),
                            m_rotation * (10 * m_scale.get_j()),
                            m_rotation * (200 * m_scale.get_k()));
    
    //m_source->set_position(m_corner + m_rotation * m_scale / 2.0f);
}

Point3f Wall::get_plane_position(const Ball &ball)
{
    float displacement = -5.f;
    if (ball.get_velocity().y < 0) {
        displacement = 5.f;
    }
    
    Point3f result(ball.get_body().get_center().x, m_body.get_point().y - ball.get_body().get_radius() + displacement, ball.get_body().get_center().z);
    /*if (result.y > ball.get_center().y + 20) {
        result.y = ball.get_center().y + 20;
    }*/
    //cout << "wall: displace from " << ball.get_center().y << "to " << result.y << endl;

    
    return result;
}

Model * Wall::m_model = 0;
unsigned long Wall::m_instance_count = 0lu;
