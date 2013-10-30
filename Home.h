//
//  Home.h
//  game
//
//  Created by Xinyuan Huang on 10/29/13.
//
//

#ifndef __game__Home__
#define __game__Home__

#include <zenilib.h>
#include <Zeni/Model.h>
#include <Zeni/Quaternion.h>
#include <Zeni/Vector3f.h>


class Home {
public:
    Home(const Zeni::Point3f &end_point_a, const Zeni::Point3f &end_point_b,
         const float &radius_ = 120.0f,
         const Zeni::Vector3f &scale_ = Zeni::Vector3f(1.0f, 1.0f, 1.0f),
         const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Home(const Home &rhs) = delete;
    Home & operator=(const Home &rhs) = delete;
    
    void render();
    
    Zeni::Point3f get_position() {return m_body.get_end_point_a();}

private:
    Zeni::Point3f m_end_point_a;
    Zeni::Point3f m_end_point_b;
    float m_radius;
    Zeni::Vector3f m_scale;
    Zeni::Quaternion m_rotation;
    
    Zeni::Collision::Capsule m_body;
    
    Zeni::Model * m_model;
    
    
    void create_body();
};


#endif /* defined(__game__Home__) */
