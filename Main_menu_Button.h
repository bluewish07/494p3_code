//
//  Main_menu_Button.h
//  game
//
//  Created by Xinyuan Huang on 10/28/13.
//
//

#ifndef __game__Main_menu_Button__
#define __game__Main_menu_Button__

#include <zenilib.h>
#include <string>

class Main_menu_Button : public Zeni::Text_Button {
public:
    Main_menu_Button()
    : Zeni::Text_Button(Zeni::Point2f(50.0f, 50.0f),
                        Zeni::Point2f(250.0f, 100.0f),
                        "system_36_800x600",
                        Zeni::String("Main Menu"))
    {}
    
    void on_accept() override;
    
};


#endif /* defined(__game__Main_menu_Button__) */
