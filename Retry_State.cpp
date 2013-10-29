//
//  Retry_State.cpp
//  game
//
//  Created by Xinyuan Huang on 10/28/13.
//
//

#include "Retry_State.h"
#include <string>

using namespace std;
using namespace Zeni;

const int last_level_c = 3;

Retry_State::Retry_State(int lives_left_)
: Widget_Gamestate(std::make_pair(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(800.0f, 600.0f))),
lives_left(lives_left_), button(lives_left)
{

    button.set_upper_left(Point2f(500, 400));
    button.set_lower_right(Point2f(700, 450));
    m_widgets.lend_Widget(button);

}

void Retry_State::render()
{
    Widget_Gamestate::render();
    
    Zeni::Font &fr = get_Fonts()["small_title"];
    
    string result = "OOPS! You fell off the disk!";
    
    fr.render_text(String(result),
                   Point2f(400.0f, 100.0f - 0.5f * fr.get_text_height()),
                   get_Colors()["title_text"],
                   ZENI_CENTER);
    
    /*
    Font &level_font = get_Fonts()["system_36_800x600"];
    level_font.render_text(String("Level "+ to_string(current_level)),
                           Point2f(100.0f, 20.0f - 0.5f *level_font.get_text_height()), get_Colors()["title_text"],
                           ZENI_CENTER);
     */
}