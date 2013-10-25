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
: m_disk(Point3f(0.0f, 0.0f, 0.0f), Point3f(0.0f, 0.0f, -10.f)),
m_wall(Point3f(20.0f, 50.0f, 0.0f), Vector3f(1.0f, 2.0f, 2.5f),
       Quaternion::Axis_Angle(Vector3f(0.0f, 0.0f, 1.0f), Global::pi_over_two))
{
    if(!m_instance_count)
        m_model = new Model("models/p3road.3DS");
    ++m_instance_count;
    
    create_body();
}


Game_World::~Game_World() {
    
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
}

void Game_World::render() {
    m_disk.render();
    
    //m_wall.render();
}

bool Game_World::collide(Ball &ball, const Point3f backup_position, bool should_bounce) {
    if(ball.get_body().shortest_distance(Plane(m_disk.get_body().get_end_point_a(), m_disk.get_normal())) < 2
       && ball.get_body().shortest_distance(m_disk.get_body()) < 2) {
        cout << ball.get_body().get_center().z << "collided" << endl;
        ball.move_to(backup_position);
        cout << ball.get_body().get_center().z << endl;
        if (should_bounce) {
            ball.bounce(m_disk.get_body().get_end_point_a() - m_disk.get_body().get_end_point_b());
        }
        else {
            cout << "stupid" << endl;
            ball.move_to(m_disk.get_plane_position(ball.get_body()));
        }
        return true;
    }
    else
        return false;
    
}

void Game_World::tilt(const float &forward, const float &leftward)
{
    m_disk.tilt(forward, leftward);
}

void Game_World::create_body() {
    // m_body = Plane(m_point, m_normal);
    //m_source->set_position(m_corner + m_rotation * m_scale / 2.0f);
}

Model * Game_World::m_model = 0;
unsigned long Game_World::m_instance_count = 0lu;
