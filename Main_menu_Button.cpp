//
//  Main_menu_Button.cpp
//  game
//
//  Created by Xinyuan Huang on 10/28/13.
//
//

#include "Main_menu_Button.h"
#include "Play_State.h"

using namespace std;
using namespace Zeni;

void Main_menu_Button::on_accept() {
    
    get_Game().pop_state();
    
}