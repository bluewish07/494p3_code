//
//  Game_World.h
//  game
//
//  Created by Xinyuan Huang on 10/20/13.
//
//

#ifndef __game__Game_World__
#define __game__Game_World__

#include <zenilib.h>
#include <Zeni/Collision.h>
#include <Zeni/Model.h>
#include <Zeni/Quaternion.h>
#include <Zeni/Sound.h>
#include <Zeni/Vector3f.h>

class Game_World {
public:
    Game_World();
    Game_World(const Game_World &rhs) = delete;
    Game_World & operator=(const Game_World &rhs) = delete;
    ~Game_World();
    
    void render();
    
    void collide();
    
    void tilt(const float &forward, const float &leftward);
    
    const Zeni::Collision::Plane & get_body() const {return m_body;}
    
private:
    void create_body();
    
    // Level 1
    static Zeni::Model * m_model;
    static unsigned long m_instance_count;
    
    // Level 2
    Zeni::Point3f m_point;
    Zeni::Vector3f m_normal;
    Zeni::Vector3f m_scale;
    Zeni::Quaternion m_rotation;
    float tilt_forward;
    float tilt_leftward;
    
    // Level 3
    Zeni::Collision::Plane m_body; // not motion so much as collision
    
    // Level 4
    // A stationary Crate has no controls
};


#endif /* defined(__game__Game_World__) */
