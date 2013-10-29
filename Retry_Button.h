//
//  Retry_Button.h
//  game
//
//  Created by Xinyuan Huang on 10/28/13.
//
//

#ifndef __game__Retry_Button__
#define __game__Retry_Button__

#include <zenilib.h>
#include <string>

class Retry_Button : public Zeni::Text_Button {
public:
    Retry_Button(int lives_left)
    : Zeni::Text_Button(Zeni::Point2f(50.0f, 50.0f),
                        Zeni::Point2f(250.0f, 100.0f),
                        "system_36_800x600",
                        Zeni::String("X " + std::to_string(lives_left)))
    {}
    
    void on_accept() override;
    
};

#endif /* defined(__game__Retry_Button__) */
