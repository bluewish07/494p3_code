//
//  Game_World.h
//  game
//
//  Created by Xinyuan Huang on 10/20/13.
//
//

#ifndef __game__Game_World__
#define __game__Game_World__

#include "Disk.h"
#include "Wall.h"
#include "Ball.h"
#include <zenilib.h>
#include <Zeni/Collision.h>
#include <Zeni/Model.h>
#include <Zeni/Quaternion.h>
#include <Zeni/Sound.h>
#include <Zeni/Vector3f.h>
#include <Zeni/Collision.h>
#include <vector>

#include <vector>
#include <deque>
#include <string>

class Game_World {
public:
    Game_World();
    Game_World(const Game_World &rhs) = delete;
    Game_World & operator=(const Game_World &rhs) = delete;
    ~Game_World();
    
    void render();
    
    bool collide(Ball &ball, const Zeni::Point3f backup_position, bool should_bounce);
    
    Zeni::Point3f get_plane_position(const Zeni::Collision::Sphere &ball);
    
    void tilt(const float &forward, const float &leftward);
    
    void read_disk_positions(std::string filename);
    
    void read_wall_positions(std::string filename);
    
    void update_view(const Zeni::Point3f &camera_position);
    
    Zeni::Point3f reset(); // return the ball's position to reset to
    
    
private:
    //void create_body();
    
    // Level 1
    /*static Zeni::Model * m_model;
    static unsigned long m_instance_count;*/
    
    std::vector<Disk*> m_disks;
    
    std::deque<Disk> disks_in_view;
    
    std::vector<Zeni::Point3f> disk_positions; // sorted by y
    
    std::vector<Wall*> m_walls;
    
    std::deque<Wall> walls_in_view;
    
    std::vector<Zeni::Point3f> wall_positions;

};


#endif /* defined(__game__Game_World__) */
