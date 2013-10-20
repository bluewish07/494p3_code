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
    
    Zeni::Font &fr = get_Fonts()["title"];
    
    fr.render_text(
#if defined(_WINDOWS)
                   "ALT+F4"
#elif defined(_MACOSX)
                   "Apple+Q"
#else
                   "Ctrl+Q"
#endif
                   " to Quit",
                   Point2f(400.0f, 300.0f - 0.5f * fr.get_text_height()),
                   get_Colors()["title_text"],
                   ZENI_CENTER);
}