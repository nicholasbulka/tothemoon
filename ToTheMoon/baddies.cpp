//
//  baddies.cpp
//  ToTheMoon
//
//  Created by Nicholas Bulka on 3/8/21.
//  Copyright © 2021 Nicholas Bulka. All rights reserved.
//

#include "baddies.hpp"


Baddie::Baddie(){
    _baddie = cv::imread(_bitcoin_fp, cv::IMREAD_COLOR );
}
Baddie::~Baddie(){
    
}
Baddie::Baddie(cv::Point2f top_corner){
    _baddie = cv::imread(_bitcoin_fp, cv::IMREAD_COLOR);
    
    corners.push_back(top_corner);
    corners.push_back(cv::Point2f(top_corner.x + _baddie.cols, top_corner.y + _baddie.rows));
    
}

cv::Mat Baddie::getBaddie(){
    return _baddie;
}

void Baddie::update(){
    fallDown();
}
void Baddie::fallDown(){
    
}

void Baddie::explode(){
    for(int row = 0; row < _baddie.rows; ++row) {
        uchar* p = _baddie.ptr(row);
        for(int col = 0; col < _baddie.cols*3; ++col) {
            *p++  = 0;
             
        }
    }
}

