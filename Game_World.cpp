//
//  Game_World.cpp
//  game
//
//  Created by Xinyuan Huang on 10/20/13.
//
//

#include "Game_World.h"
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
{}


Game_World::~Game_World() {
    delete m_home;
    
}

void Game_World::render() {
    
    for (auto itr = disks_in_view.begin(); itr != disks_in_view.end(); ++itr) {
        itr->render();
    }
    for (auto itr : walls_in_view) {
        itr.render();
    }
}

bool Game_World::collide(Ball &ball, const Point3f backup_position, bool should_bounce) {
    // collision detection for disks
    for (auto itr = disks_in_view.begin(); itr != disks_in_view.end(); ++itr) {
        Point3f  disk_pos = itr->get_body().get_end_point_a();
        Point3f ball_pos = ball.get_body().get_center();
        float distance = (Point3f(disk_pos.x, disk_pos.y, 0) - Point3f(ball_pos.x, ball_pos.y, 0)).magnitude();
        if (distance - itr->get_body().get_radius() > 50)
            continue;
        
        if(ball.get_body().shortest_distance(Plane(itr->get_body().get_end_point_a(), itr->get_normal())) < 2
           //&& ball.get_body().shortest_distance(itr->get_body()) < 2) {
           && (ball.get_body().get_center() - itr->get_body().get_end_point_a()).get_ij().magnitude() < itr->get_body().get_radius() + ball.get_body().get_radius() + 2) {
            //cout << ball.get_body().shortest_distance(Plane(itr->get_body().get_end_point_a(), itr->get_normal())) << endl;
            ball.move_to(backup_position);
            //cout << ball.get_body().get_center().z << endl;
            if (should_bounce) {
                ball.bounce(itr->get_body().get_end_point_a() - itr->get_body().get_end_point_b());
            }
            else {
                cout << "stupid" << endl;
                ball.move_to(itr->get_plane_position(ball.get_body()));
            }
            return true;
        }
    }
    // collision detection for walls
    for (auto itr : walls_in_view) {
        if(ball.get_body().shortest_distance(Plane(itr.get_body().get_point(), itr.get_body().get_normal_b())) < 2
           && (ball.get_body().get_center().x > itr.get_body().get_point().x - ball.get_body().get_radius() &&
               ball.get_body().get_center().x < itr.get_body().get_point().x + 2*(itr.get_body().get_center().x - itr.get_body().get_point().x) + ball.get_body().get_radius())
           && (ball.get_body().get_center().z > itr.get_body().get_point().z - ball.get_body().get_radius() &&
               ball.get_body().get_center().z < itr.get_body().get_point().z + 2*(itr.get_body().get_center().z - itr.get_body().get_point().z) + ball.get_body().get_radius())) {
               //cout << ball.get_body().get_center().y << "collide with wall" << endl;
               ball.move_to(backup_position);
               //cout << ball.get_body().get_center().y << endl;
               if (should_bounce) {
                   ball.bounce(itr.get_body().get_edge_b());
               } else {
                   cout << "stupid" << endl;
                   ball.move_to(itr.get_plane_position(ball.get_body()));
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
    Zeni::Point3f home_position = disk_positions[disk_positions.size()-1];
    m_home = new Home(home_position, home_position-Point3f(0, 0, 10));
    disk_positions.erase(disk_positions.end()-1);
    
}

void Game_World::read_wall_positions(string filename)
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
        wall_positions.push_back(Point3f(x, y, z));
    }
    
}

static bool y_comparator(const Point3f &p1, const Point3f &p2)
{
    return p1.y < p2.y;
}

void Game_World::update_view(const Point3f &camera_position)
{
    // remove any disks that is far back behind
    if (!disks_in_view.empty()) {
        Point3f disk_position = disks_in_view[0].get_body().get_end_point_a();
        float distance = disk_position.y - camera_position.y;
        while (distance < -200) {
            disks_in_view.erase(disks_in_view.begin());
            if (!disks_in_view.empty()) {
                disk_position = disks_in_view[0].get_body().get_end_point_a();
                distance = disk_position.y - camera_position.y;
            } else
                break;
        }
    }
    
    // remove any walls that is far back behind
    if (!walls_in_view.empty()) {
        Point3f wall_position = walls_in_view[0].get_body().get_point();
        float distance = wall_position.y - camera_position.y;
        while (distance < -200) {
            walls_in_view.erase(walls_in_view.begin());
            if (!walls_in_view.empty()) {
                wall_position = walls_in_view[0].get_body().get_point();
                distance = wall_position.y - camera_position.y;
            } else
                break;
        }
    }
    
    // insert disks in the front if the camera moves backward
    auto itr1 = upper_bound(disk_positions.begin(), disk_positions.end(),
                            camera_position - Point3f(0, 200, 0), y_comparator);
    float insert_front_upper_bound = disks_in_view.empty() ? camera_position.y + 900 : disks_in_view[0].get_body().get_end_point_a().y;
    float tilt_forward = disks_in_view.empty() ? 0 : disks_in_view[0].get_tilt_forward();
    float tilt_leftward = disks_in_view.empty() ? 0 : disks_in_view[0].get_tilt_leftward();
    int index = 0;
    while (itr1 != disk_positions.end() && itr1->y < insert_front_upper_bound) {
        Disk new_disk(*itr1, *itr1 - Point3f(0, 0, 10));
        new_disk.tilt(tilt_forward, tilt_leftward);
        disks_in_view.insert(disks_in_view.begin() + index, new_disk);
        index ++;
        itr1 ++;
    }
    
    // insert walls in the front if the camera moves backward
    auto itr_wall = upper_bound(wall_positions.begin(), wall_positions.end(),
                                camera_position - Point3f(0, 200, 0), y_comparator);
    float insert_front_upper_bound_for_wall = walls_in_view.empty() ? camera_position.y + 900 : walls_in_view[0].get_body().get_point().y;
    index = 0;
    while (itr_wall != wall_positions.end() && itr_wall->y < insert_front_upper_bound_for_wall) {
        cout << "1 " << itr_wall->x << ' ' << itr_wall->y << ' ' << itr_wall->z << endl;
        Wall new_wall(*itr_wall);
        walls_in_view.insert(walls_in_view.begin() + index, new_wall);
        index++;
        itr_wall++;
    }
    
    
    // remove any disks that is too far away
    if (!disks_in_view.empty()) {
        Point3f disk_position = disks_in_view[disks_in_view.size()-1].get_body().get_end_point_a();
        float distance = disk_position.y - camera_position.y;
        while (distance > 900) {
            disks_in_view.erase(disks_in_view.end()-1);
            if (!disks_in_view.empty()) {
                disk_position = disks_in_view[disks_in_view.size()-1].get_body().get_end_point_a();
                distance = disk_position.y - camera_position.y;
            } else
                break;
        }
    }
    
    // remove any disks that is too far away
    if (!walls_in_view.empty()) {
        Point3f wall_position = walls_in_view[walls_in_view.size()-1].get_body().get_point();
        float distance = wall_position.y - camera_position.y;
        while (distance > 900) {
            walls_in_view.erase(walls_in_view.end()-1);
            if (!walls_in_view.empty()) {
                wall_position = walls_in_view[walls_in_view.size()-1].get_body().get_point();
                distance = wall_position.y - camera_position.y;
            } else
                break;
        }
    }
    
    // append disks at the end as the camera moves forward
    float append_lower_bound = disks_in_view.empty() ?
    camera_position.y - 200 : disks_in_view[disks_in_view.size()-1].get_body().get_end_point_a().y;
    auto itr2 = upper_bound(disk_positions.begin(), disk_positions.end(),
                            Point3f(0, append_lower_bound, 0), y_comparator);
    while (itr2 != disk_positions.end() && itr2->y < camera_position.y + 900) {
        Disk new_disk(*itr2, *itr2- Point3f(0, 0, 10));
        new_disk.tilt(tilt_forward, tilt_leftward);
        disks_in_view.push_back(new_disk);
        itr2 ++;
    }
    
    // append walls at the end as the camera moves forward
    float append_lower_bound_for_wall = walls_in_view.empty() ?
    camera_position.y - 200 : walls_in_view[walls_in_view.size()-1].get_body().get_point().y;
    auto itr_wall2 = upper_bound(wall_positions.begin(), wall_positions.end(),
                                 Point3f(0, append_lower_bound_for_wall, 0), y_comparator);
    while (itr_wall2 != wall_positions.end() && itr_wall2->y < camera_position.y + 900) {
        cout << itr_wall2->x << ' ' << itr_wall2->y << ' ' << itr_wall2->z << endl;
        Wall new_wall(*itr_wall2);
        walls_in_view.push_back(new_wall);
        itr_wall2++;
    }
}
    

Point3f Game_World::reset()
{
    // reset disks
    for (auto itr = disks_in_view.begin(); itr != disks_in_view.end(); ++itr) {
        itr->tilt(-itr->get_tilt_forward(), -itr->get_tilt_leftward());
        assert(!itr->get_tilt_forward() && !itr->get_tilt_leftward());
    }
            
    return disks_in_view[0].get_body().get_end_point_a() + Point3f(0, 0, 100);
}

float Game_World::get_ideal_camera_height()
{
    if (disks_in_view.empty()) {
        return -1;
    }
    else
        return disks_in_view[0].get_body().get_end_point_a().z + 200;
}

bool Game_World::is_home(Zeni::Point3f ball_pos)
{
    return (ball_pos - m_home->get_position()).magnitude() < 120;
}
/*void Game_World::create_body() {
 // m_body = Plane(m_point, m_normal);
 //m_source->set_position(m_corner + m_rotation * m_scale / 2.0f);
 }
 
 Model * Game_World::m_model = 0;
 unsigned long Game_World::m_instance_count = 0lu;*/
