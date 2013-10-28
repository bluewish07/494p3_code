#ifndef WALL_H
#define WALL_H

#include <zenilib.h>
#include <Zeni/Collision.h>
#include <Zeni/Model.h>
#include <Zeni/Quaternion.h>
#include <Zeni/Sound.h>
#include <Zeni/Vector3f.h>

class Wall {
public:
    Wall(const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
          const Zeni::Vector3f &scale_ = Zeni::Vector3f(1.0f, 1.0f, 1.0f),
          const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Wall(const Wall &rhs);
    Wall & operator=(const Wall &rhs);
    ~Wall();
    
    void render();
    
    void collide();
    
    const Zeni::Collision::Parallelepiped & get_body() const {return m_body;}
    
    Zeni::Point3f get_plane_position(const Zeni::Collision::Sphere &ball);
    
private:
    void create_body();
    
    // Level 1
    static Zeni::Model * m_model;
    static unsigned long m_instance_count;
    
    //Zeni::Sound_Source * m_source;
    
    // Level 2
    Zeni::Point3f m_corner;
    Zeni::Vector3f m_scale;
    Zeni::Quaternion m_rotation;
    
    // Level 3
    Zeni::Collision::Parallelepiped m_body; // not motion so much as collision
    
    // Level 4
    // A stationary Crate has no controls
};

#endif
