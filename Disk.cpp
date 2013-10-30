#include "Disk.h"
#include <iostream>

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;

queue<Zeni::Model *> Disk::reusable_models;

Disk::Disk(const Point3f &end_point_a, const Point3f &end_point_b, const bool alt,
           const float &radius_, const Vector3f &scale_, const Quaternion &rotation_)
: m_end_point_a(end_point_a), m_end_point_b(end_point_b),
m_radius(radius_), m_scale(scale_), m_rotation(rotation_),
tilt_forward(0), tilt_leftward(0)
{
    //m_source(new Sound_Source(get_Sounds()["collide"]))
    /*
    if(!m_instance_count)
        m_model = new Model("models/p3disk.3ds");
    ++m_instance_count;
     */
    
    if (reusable_models.empty()) {
        if (alt)
            m_model = new Model("models/p3disk.3ds");
        else
            m_model = new Model("models/p3disk.3ds");
    }
    else {
        m_model = reusable_models.front();
        reusable_models.pop();
    }
    
    create_body();
}

Disk::Disk(const Disk &rhs)
: m_end_point_a(rhs.m_end_point_a), m_end_point_b(rhs.m_end_point_b),
m_radius(rhs.m_radius),
m_scale(rhs.m_scale), m_rotation(rhs.m_rotation),
tilt_forward(rhs.tilt_forward), tilt_leftward(rhs.tilt_leftward)
{
    if (reusable_models.empty()) {
        m_model = new Model("models/p3disk.3ds");
    }
    else {
        m_model = reusable_models.front();
        reusable_models.pop();
    }

    
    create_body();
}

Disk & Disk::operator=(const Disk &rhs) {
    m_end_point_a = rhs.m_end_point_a;
    m_end_point_b = rhs.m_end_point_b;
    m_radius = rhs.m_radius;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    tilt_forward = rhs.tilt_forward;
    tilt_leftward = rhs.tilt_leftward;
    
    if (reusable_models.empty()) {
        m_model = new Model("models/p3disk.3ds");
    }
    else {
        m_model = reusable_models.front();
        reusable_models.pop();
    }
    
    create_body();
    
    return *this;
}

Disk::~Disk() {
    /*
    //delete m_source;
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
     */
    reusable_models.push(m_model);
}

void Disk::render() {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    
    // for now 
    m_model->set_translate(m_end_point_a);
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    
    m_model->render();
}

void Disk::collide() {
    /*if(!m_source->is_playing())
     m_source->play();*/
}


Point3f Disk::get_plane_position(const Sphere &ball)
{
    Vector3f normal = m_body.get_end_point_a() - m_body.get_end_point_b();
    Vector3f radius_vector = ball.get_radius() * normal.normalized();
    float vertical_projection = radius_vector * Vector3f(0, 0, 1);
    float cos_theta = vertical_projection / ball.get_radius();
    float center_to_plane_vertical = ball.get_radius() / cos_theta;
    float xy_dist = (Point3f(ball.get_center().x, ball.get_center().y, 0) - Point3f(m_body.get_end_point_a().x, m_body.get_end_point_a().y, 0)).magnitude();
    float theta = acos(cos_theta);
    float plane_to_ground = xy_dist * tan(theta);
    
    //cout << center_to_plane_vertical + plane_to_ground << endl;
    
    Point3f result(ball.get_center().x, ball.get_center().y, center_to_plane_vertical + plane_to_ground + 5);
    if (result.z > ball.get_center().z + 20) {
        result.z = ball.get_center().z + 20;
    }
    //cout << "displace from " << ball.get_center().z << "to " << result.z << endl;
    
    return result;
}

void Disk::tilt(const float &forward, const float &leftward)
{
    float tilt_forward_result = tilt_forward + forward;
    float tilt_leftward_result = tilt_leftward + leftward;
    bool body_change = false;
    if (tilt_forward_result > -0.45 && tilt_forward_result < 0.45) {
        tilt_forward = tilt_forward_result;
        body_change = true;
    }
    if (tilt_leftward_result > -0.45 && tilt_leftward_result < 0.456) {
        tilt_leftward = tilt_leftward_result;
        body_change = true;
    }
    if (body_change) {
        m_rotation = Quaternion(0, -tilt_leftward, -tilt_forward);
        
        Quaternion normal_rotation(0, -leftward, -forward);
        
        Vector3f normal = m_body.get_end_point_a() - m_body.get_end_point_b();
        normal = normal_rotation * normal;
        Point3f mid_point = (m_body.get_end_point_a() + m_body.get_end_point_b());
        mid_point.x /= 2;
        mid_point.y /= 2;
        mid_point.z /= 2;
        
        m_end_point_a = mid_point + normal/2;
        m_end_point_b = mid_point - normal/2;
        //cout << "m_normal " << m_normal.x << "," << m_normal.y << "," << m_normal.z << endl;
        create_body();
    }
}


void Disk::create_body() {
    m_body = Capsule(m_end_point_a, m_end_point_b, m_radius);
    
    //m_source->set_position(m_corner + m_rotation * m_scale / 2.0f);
}

//Model * Disk::m_model = 0;
unsigned long Disk::m_instance_count = 0lu;

