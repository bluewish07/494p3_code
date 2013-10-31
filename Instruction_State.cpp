//
//  Instruction_State.cpp
//  game
//
//  Created by Xinyuan Huang on 10/19/13.
//
//

#include "Instruction_State.h"
#include <cstdlib>

using namespace std;
using namespace Zeni;

#if defined(_DEBUG) && defined(_WINDOWS)
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

Instructions_State::Instructions_State()
: Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)))
{
}

void Instructions_State::on_key(const SDL_KeyboardEvent &event) {
    if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED)
        get_Game().pop_state();
}


void Instructions_State::render() {
    Widget_Gamestate::render();
    
    Zeni::Font &narrative = get_Fonts()["system_36_800x600"];
    narrative.render_text("Your task is to help the ball bounce its way home.\nYou will tilt the boucy disks, and physics will do it.\n",
                          Point2f(400, 50),
                          get_Colors()["title_text"],
                          ZENI_CENTER);
    
    Zeni::Font &fr = get_Fonts()["title"];
    
    fr.render_text("Use ARROW KEYS!",
                   Point2f(400.0f, 200.0f - 0.5f * fr.get_text_height()),
                   get_Colors()["title_text"],
                   ZENI_CENTER);
    
    narrative.render_text("<-- -->              tilt to the left/right\nup/down arrows     tilt forward/backward",
                          Point2f(100.0f, 300.0f),
                          get_Colors()["title_text"]);
    
    Zeni::Font &sm_title = get_Fonts()["small_title"];
    sm_title.render_text("TIP: \nYou do not want the ball to sprint.\n",
                         Point2f(10, 380),
                         get_Colors()["title_text"]);
    
    fr.render_text("SLOW DOWN!",
                   Point2f(400, 500),
                   get_Colors()["title_text"],
                   ZENI_CENTER);
}