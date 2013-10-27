//
//  Game_World.cpp
//  game
//
//  Created by Xinyuan Huang on 10/20/13.
//
//

#include "Game_World.h"
#include "Ball.h"
#include <zenilib.h>
#include <cmath>
#include <algorithm>

using namespace std;
using namespace Zeni;
using namespace Zeni::Collision;

Game_World::Game_World()
{
    /*if(!m_instance_count)
        m_model = new Model("models/p3road.3DS");
    ++m_instance_count;*/
    
    Wall* m_wall = new Wall(Point3f(20.0f, 50.0f, 0.0f), Vector3f(1.0f, 2.0f, 2.5f),
                            Quaternion::Axis_Angle(Vector3f(0.0f, 0.0f, 1.0f), Global::pi_over_two));
    m_walls.push_back(m_wall);
    
    m_wall = new Wall(Point3f(20.0f, 500.0f, 0.0f), Vector3f(1.0f, 2.0f, 2.5f),
                      Quaternion::Axis_Angle(Vector3f(0.0f, 0.0f, 1.0f), Global::pi_over_two));
    
    m_walls.push_back(m_wall);
    
    Disk* m_disk = new Disk (Point3f(0.0f, 0.0f, 0.0f), Point3f(0.0f, 0.0f, -10.f));
    m_disks.push_back(m_disk);
    m_disk = new Disk (Point3f(0.0f, 250.0f, -50.0f), Point3f(0.0f, 250.0f, -60.f));
    m_disks.push_back(m_disk);
    m_disk = new Disk (Point3f(0.0f, 500.0f, -100.0f), Point3f(0.0f, 500.0f, -110.f));
    m_disks.push_back(m_disk);
    
    //create_body();
}


Game_World::~Game_World() {
    
    /*if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }*/
    
    for (auto ptr : m_walls) {
        delete ptr;
    }
}

void Game_World::render() {
    for (auto disk_ptr : m_disks) {
        disk_ptr->render();
    }
    
    for (auto wall_ptr : m_walls) {
        wall_ptr->render();
    }
}

bool Game_World::collide(Ball &ball, const Point3f backup_position, bool should_bounce) {
    for (auto disk_ptr : m_disks) {
        if(ball.get_body().shortest_distance(Plane(disk_ptr->get_body().get_end_point_a(), disk_ptr->get_normal())) < 2
           && ball.get_body().shortest_distance(disk_ptr->get_body()) < 2) {
            cout << ball.get_body().get_center().z << "collided" << endl;
            ball.move_to(backup_position);
            cout << ball.get_body().get_center().z << endl;
            if (should_bounce) {
                ball.bounce(disk_ptr->get_body().get_end_point_a() - disk_ptr->get_body().get_end_point_b());
            }
            else {
                cout << "stupid" << endl;
                ball.move_to(disk_ptr->get_plane_position(ball.get_body()));
            }
            return true;
        }
    }
    return false;
}

void Game_World::tilt(const float &forward, const float &leftward)
{
    for (auto disk_ptr : m_disks) {
        disk_ptr->tilt(forward, leftward);
    }
}

/*void Game_World::create_body() {
    // m_body = Plane(m_point, m_normal);
    //m_source->set_position(m_corner + m_rotation * m_scale / 2.0f);
}

Model * Game_World::m_model = 0;
unsigned long Game_World::m_instance_count = 0lu;*/
