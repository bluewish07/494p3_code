//
//  Instruction_State.h
//  game
//
//  Created by Xinyuan Huang on 10/19/13.
//
//

#ifndef __game__Instruction_State__
#define __game__Instruction_State__

#include <zenilib.h>

class Instructions_State : public Zeni::Widget_Gamestate {
    Instructions_State(const Instructions_State &);
    Instructions_State operator=(const Instructions_State &);
    
public:
    Instructions_State();
    
private:
    void on_key(const SDL_KeyboardEvent &event);
    
    void render();
};

#endif /* defined(__game__Instruction_State__) */
