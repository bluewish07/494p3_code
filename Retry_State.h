//
//  Retry_State.h
//  game
//
//  Created by Xinyuan Huang on 10/28/13.
//
//

#ifndef __game__Retry_State__
#define __game__Retry_State__

#include <zenilib.h>
#include "Retry_Button.h"

class Retry_State : public Zeni::Widget_Gamestate {
    Retry_State(const Retry_State &);
    Retry_State operator=(const Retry_State &);
    
public:
    Retry_State(Zeni::Point3f restart_pos, int lives_left_);
    
private:
    int lives_left;
    Retry_Button button;
    
    void render();
};


#endif /* defined(__game__Retry_State__) */
