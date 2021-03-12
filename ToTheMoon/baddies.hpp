//
//  baddies.hpp
//  ToTheMoon
//
//  Created by Nicholas Bulka on 3/8/21.
//  Copyright © 2021 Nicholas Bulka. All rights reserved.
//

#ifndef baddies_hpp
#define baddies_hpp

#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


const std::string _bitcoin_fp = "/Users/nicholasbulka/programming/creativ/ToTheMoon/ToTheMoon/bitcoin.png";

class Baddie
{
public:
    Baddie();
    Baddie(cv::Point2f);
    ~Baddie();
    //topL, topR, bottomL, bottomR
    std::vector<cv::Point2f> corners;
    cv::Mat getBaddie();
    void explode();

    
    
private:
    cv::Mat _baddie;
    void update();
    void fallDown();
};
#endif /* baddies_hpp */
