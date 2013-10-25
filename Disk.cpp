#include "Disk.h"

using namespace Zeni;
using namespace Zeni::Collision;

Disk::Disk(const Point3f &summit_point_, const float &radius_,
           const Vector3f &scale_, const Quaternion &rotation_)
: m_summit_point(summit_point_), m_radius(radius_), m_scale(scale_), m_rotation(rotation_)
{
    //m_source(new Sound_Source(get_Sounds()["collide"]))
    if(!m_instance_count)
        m_model = new Model("models/p3disk.3ds");
    ++m_instance_count;
    
    create_body();
}

Disk::Disk(const Disk &rhs)
: m_summit_point(rhs.m_summit_point), m_radius(rhs.m_radius),
m_scale(rhs.m_scale), m_rotation(rhs.m_rotation)
{
    ++m_instance_count;
    
    create_body();
}

Disk & Disk::operator=(const Disk &rhs) {
    m_summit_point = rhs.m_summit_point;
    m_radius = rhs.m_radius;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    create_body();
    
    return *this;
}

Disk::~Disk() {
    
    //delete m_source;
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
}

void Disk::render() {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    
    // for now 
    m_model->set_translate(m_summit_point);
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    
    m_model->render();
}

void Disk::collide() {
    /*if(!m_source->is_playing())
     m_source->play();*/
}

void Disk::create_body() {
    Point3f m_end_point_b = m_summit_point;
    m_end_point_b.z -= 0.5f;
    m_body = Capsule(m_summit_point, m_end_point_b, m_radius);
    
    //m_source->set_position(m_corner + m_rotation * m_scale / 2.0f);
}

Model * Disk::m_model = 0;
unsigned long Disk::m_instance_count = 0lu;
