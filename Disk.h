#ifndef DISK_H
#define DISK_H

#include <zenilib.h>
#include <Zeni/Collision.h>
#include <Zeni/Model.h>
#include <Zeni/Quaternion.h>
#include <Zeni/Sound.h>
#include <Zeni/Vector3f.h>

#include <queue>

class Disk {
public:
    Disk(const Zeni::Point3f &end_point_a, const Zeni::Point3f &end_point_b,
         const float &radius_ = 120.0f,
         const Zeni::Vector3f &scale_ = Zeni::Vector3f(1.0f, 1.0f, 1.0f),
         const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Disk(const Disk &rhs);
    Disk & operator=(const Disk &rhs);
    ~Disk();
    
    void render();
    
    void collide();
    
    const Zeni::Collision::Capsule & get_body() const {return m_body;}
    
    Zeni::Point3f get_plane_position(const Zeni::Collision::Sphere &ball);
    
    const Zeni::Vector3f get_normal() const {return m_end_point_a - m_end_point_b;}
    
    float get_tilt_forward() const {return tilt_forward;}
    float get_tilt_leftward() const {return tilt_leftward;}

    void tilt(const float &forward, const float &leftward);
    
private:
    void create_body();
    
    Zeni::Model * m_model;
    static unsigned long m_instance_count;
    
    static std::queue<Zeni::Model *> reusable_models;
    
    static bool model_num;
    
    //Zeni::Sound_Source * m_source;
    
    Zeni::Point3f m_end_point_a;
    Zeni::Point3f m_end_point_b;
    float m_radius;
    Zeni::Vector3f m_scale;
    Zeni::Quaternion m_rotation;
    
    float tilt_forward;
    float tilt_leftward;
    
    
    Zeni::Collision::Capsule m_body; 
    
};

#endif
