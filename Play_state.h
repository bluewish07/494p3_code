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

class Play_State : public Zeni::Gamestate_Base {
    Play_State(const Play_State &);
    Play_State operator=(const Play_State &);
    
public:
    Play_State() {
        set_pausable(true);
    }
    
private:
    void on_push();
    
    void on_pop();
    
    void on_cover();
    
    void on_controller_button(const SDL_ControllerButtonEvent &event);
};

#endif /* defined(__game__Play_state__) */
