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
#include <string>
#include <fstream>
#include <cassert>

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
    //m_disk.render();
    
    //m_wall.render();
    
    for (auto itr = disks_in_view.begin(); itr != disks_in_view.end(); ++itr) {
        itr->render();
    }
}

void Game_World::read_disk_positions(string filename)
{
    ifstream ifs(filename);
    assert(ifs.is_open());
    string line;
    while (getline(ifs, line)) {
        int first_space = line.find(' ');
        int second_space = line.rfind(' ');
        int x = stoi(line.substr(0, first_space));
        int y = stoi(line.substr(first_space+1, second_space - first_space-1));
        int z = stoi(line.substr(second_space+1));
        disk_positions.push_back(Point3f(x, y, z));
    }
}

bool Game_World::collide(Ball &ball, const Point3f backup_position, bool should_bounce) {
    for (int i = 0; i < disks_in_view.size(); i++) {
        m_disk = disks_in_view[i];
        Point3f  disk_pos = m_disk.get_body().get_end_point_a();
        Point3f ball_pos = ball.get_body().get_center();
        float distance = (Point3f(disk_pos.x, disk_pos.y, 0) - Point3f(ball_pos.x, ball_pos.y, 0)).magnitude();
        if (distance - m_disk.get_body().get_radius() > 50)
            continue;
        
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
    }
    return false;
    
}

void Game_World::tilt(const float &forward, const float &leftward)
{
    for (auto itr = disks_in_view.begin(); itr != disks_in_view.end(); ++itr) {
        itr->tilt(forward, leftward);
    }
    
}

static bool y_comparator(const Point3f &p1, const Point3f &p2)
{
    return p1.y < p2.y;
}

void Game_World::update_disks_in_view(const Point3f &camera_position)
{
    // remove any disks that is far back behind
    if (!disks_in_view.empty()) {
        Point3f disk_position = disks_in_view[0].get_body().get_end_point_a();
        float distance = disk_position.y - camera_position.y;
        while (distance < -200) {
            disks_in_view.erase(disks_in_view.begin());
            disk_position = disks_in_view[0].get_body().get_end_point_a();
            distance = disk_position.y - camera_position.y;
        }
    }

    // insert disks in the front if the camera moves backward
    auto itr1 = upper_bound(disk_positions.begin(), disk_positions.end(),
                            camera_position - Point3f(0, 200, 0), y_comparator);
    float insert_front_upper_bound = disks_in_view.empty()? camera_position.y + 500 : disks_in_view[0].get_body().get_end_point_a().y;
    float tilt_forward = disks_in_view.empty()? 0 : disks_in_view[0].get_tilt_forward();
    float tilt_leftward = disks_in_view.empty()? 0 : disks_in_view[0].get_tilt_leftward();
    int index = 0;
    while (itr1 != disk_positions.end() && itr1->y < insert_front_upper_bound) {
        Disk new_disk(*itr1, *itr1 - Point3f(0, 0, 10));
        new_disk.tilt(tilt_forward, tilt_leftward);
        disks_in_view.insert(disks_in_view.begin() + index, new_disk);
        index ++;
        itr1 ++;
    }

    
    // remove any disks that is too far away
    if (!disks_in_view.empty()) {
        Point3f disk_position = disks_in_view[disks_in_view.size()-1].get_body().get_end_point_a();
        float distance = disk_position.y - camera_position.y;
        while (distance > 500) {
            disks_in_view.erase(disks_in_view.end()-1);
            disk_position = disks_in_view[disks_in_view.size()-1].get_body().get_end_point_a();
            distance = disk_position.y - camera_position.y;
            
        }

    }
    
    // append disks at the end as the camera moves forward
    float append_lower_bound = disks_in_view.empty()?
                                camera_position.y - 200 : disks_in_view[disks_in_view.size()-1].get_body().get_end_point_a().y;
    auto itr2 = upper_bound(disk_positions.begin(), disk_positions.end(),
                            Point3f(0, append_lower_bound, 0), y_comparator);
    while (itr2 != disk_positions.end() && itr2->y < camera_position.y + 500) {
        Disk new_disk(*itr2, *itr2- Point3f(0, 0, 10));
        new_disk.tilt(tilt_forward, tilt_leftward);
        disks_in_view.push_back(new_disk);
        itr2 ++;
    }
    
}

void Game_World::create_body() {
    // m_body = Plane(m_point, m_normal);
    //m_source->set_position(m_corner + m_rotation * m_scale / 2.0f);
}

Model * Game_World::m_model = 0;
unsigned long Game_World::m_instance_count = 0lu;
