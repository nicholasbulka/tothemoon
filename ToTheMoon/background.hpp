//
//  background.hpp
//  ToTheMoon
//
//  Created by Nicholas Bulka on 3/11/21.
//  Copyright © 2021 Nicholas Bulka. All rights reserved.
//

#ifndef background_hpp
#define background_hpp

#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <stdio.h>

const std::string _moon_fp = "/Users/nicholasbulka/programming/creativ/ToTheMoon/ToTheMoon/moon.png";

cv::Mat _moon_background = cv::imread(_moon_fp, cv::IMREAD_COLOR);


#endif /* background_hpp */
