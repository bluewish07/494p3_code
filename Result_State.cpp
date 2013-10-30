//
//  Result_State.cpp
//  game
//
//  Created by Xinyuan Huang on 10/28/13.
//
//

#include "Result_State.h"
#include <string>

using namespace std;
using namespace Zeni;

const int last_level_c = 3;

Result_State::Result_State(bool passed_)
: Widget_Gamestate(std::make_pair(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(800.0f, 600.0f))),
passed(passed_)
{
    
    button.set_upper_left(Point2f(500, 400));
    button.set_lower_right(Point2f(700, 450));
    m_widgets.lend_Widget(button);
}

void Result_State::render()
{
    Widget_Gamestate::render();
    
    Zeni::Font &fr = get_Fonts()["small_title"];
    
    string result;
    if (passed) {
        result = "Congratulations!\nYou helped the ball \nto bounce back home!";
    }
    else {
        result = "Sorry!\nThe ball didn't make it home! \nPlease try again.";
    }
    
    fr.render_text(String(result),
                   Point2f(400.0f, 100.0f - 0.5f * fr.get_text_height()),
                   get_Colors()["title_text"],
                   ZENI_CENTER);
    
}