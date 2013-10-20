//
//  Play_state.h
//  game
//
//  Created by Xinyuan Huang on 10/19/13.
//
//

#ifndef __game__Play_state__
#define __game__Play_state__

#include <zenilib.h>
#include "Ball.h"

class Play_State : public Zeni::Gamestate_Base {
    Play_State(const Play_State &);
    Play_State operator=(const Play_State &);
    
public:
    Play_State();
    
    void on_push();
    
    void on_pop();
    
    void on_key(const SDL_KeyboardEvent &event);
    
    void render();
    
private:
    Zeni::Time_HQ time_passed;
    
    Ball m_ball;
    
    Zeni::Camera m_camera;
    
    struct Controls {
        Controls() : forward(false), left(false), back(false), right(false) {}
        
        bool forward;
        bool left;
        bool back;
        bool right;
    } m_controls;
    
    
};

#endif /* defined(__game__Play_state__) */
