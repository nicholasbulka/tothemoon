//
//  background.cpp
//  ToTheMoon
//
//  Created by Nicholas Bulka on 3/21/21.
//  Copyright © 2021 Nicholas Bulka. All rights reserved.
//

#include <stdio.h>
#include "background.hpp"


void Moon::resize_moon(){
    cv::resize(_moon_loaded, _moon_background, cv::Size(240,200));
}

cv::Mat Moon::get_moon(){
    resize_moon();
    
    return _moon_background;
}
