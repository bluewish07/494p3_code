#ifndef DISK_H
#define DISK_H

#include <zenilib.h>
#include <Zeni/Collision.h>
#include <Zeni/Model.h>
#include <Zeni/Quaternion.h>
#include <Zeni/Sound.h>
#include <Zeni/Vector3f.h>

class Disk {
public:
    Disk(const Zeni::Point3f &end_point_a, const Zeni::Point3f &end_point_b,
         const float &radius_ = 120.0f,
         const Zeni::Vector3f &scale_ = Zeni::Vector3f(3.0f, 3.0f, 1.0f),
         const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Disk(const Disk &rhs);
    Disk & operator=(const Disk &rhs);
    ~Disk();
    
    Zeni::Point3f get_plane_position(const Zeni::Collision::Sphere &ball);
    void tilt(const float &forward, const float &leftward);

    
    void render();
    
    void collide();
    
    const Zeni::Collision::Capsule & get_body() const {return m_body;}
    
    const Zeni::Vector3f get_normal() const {return m_end_point_a - m_end_point_b;}
    
private:
    void create_body();
    
    // Level 1
    static Zeni::Model * m_model;
    static unsigned long m_instance_count;
    
    //Zeni::Sound_Source * m_source;
    
    // Level 2
    Zeni::Point3f m_end_point_a;
    Zeni::Point3f m_end_point_b;
    float m_radius;
    Zeni::Vector3f m_scale;
    Zeni::Quaternion m_rotation;
    
    float tilt_forward;
    float tilt_leftward;
    
    // Level 3
    Zeni::Collision::Capsule m_body; // not motion so much as collision
    
    // Level 4
    // A stationary Crate has no controls
};

#endif