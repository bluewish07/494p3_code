//
//  Result_State.h
//  game
//
//  Created by Xinyuan Huang on 10/28/13.
//
//

#ifndef __game__Result_State__
#define __game__Result_State__

#include <iostream>

#include <zenilib.h>
#include "Main_menu_Button.h"

class Result_State : public Zeni::Widget_Gamestate {
    Result_State(const Result_State &);
    Result_State operator=(const Result_State &);
    
public:
    Result_State(bool passed_);
    
private:
    bool passed;
    Main_menu_Button button;
    
    void render();
};


#endif /* defined(__game__Result_State__) */
