//
//  Ball.h
//  game
//
//  Created by Xinyuan Huang on 10/19/13.
//
//

#ifndef __game__Ball__
#define __game__Ball__

#include <zenilib.h>
#include <Zeni/Collision.h>
#include <Zeni/Model.h>
#include <Zeni/Quaternion.h>
#include <Zeni/Sound.h>
#include <Zeni/Vector3f.h>

class Ball {
public:
    Ball(const Zeni::Point3f &center_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
         const float &radius_ = 15.0,
         const Zeni::Vector3f &scale_ = Zeni::Vector3f(1.0f, 1.0f, 1.0f),
         const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Ball(const Ball &rhs) = delete;
    Ball & operator=(const Ball &rhs) = delete;
    ~Ball();
    
    void render();
    
    void collide();
    
    const Zeni::Collision::Sphere & get_body() const {return m_body;}
    
private:
    void create_body();
    
    // Level 1
    static Zeni::Model * m_model;
    static unsigned long m_instance_count;
    
    // Level 2
    Zeni::Point3f m_center;
    float m_radius;
    Zeni::Vector3f m_scale;
    Zeni::Quaternion m_rotation;
    
    // Level 3
    Zeni::Collision::Sphere m_body; // not motion so much as collision
    
    // Level 4
    // A stationary Crate has no controls
};

#endif /* defined(__game__Ball__) */
