//
//  baddies_factory.cpp
//  ToTheMoon
//
//  Created by Nicholas Bulka on 3/8/21.
//  Copyright © 2021 Nicholas Bulka. All rights reserved.
//

#include "baddies_factory.hpp"


BaddieFactory::BaddieFactory(int baddieNumber){
    for(int i = 0; i < baddieNumber; i++){
        Baddie* baddie = new Baddie(cv::Point2f(i*75.0, i*100.0));
        _baddieSwarm.push_back(*baddie);
    }
}
BaddieFactory::~BaddieFactory(){
    
}

void BaddieFactory::updateBaddies(){
    
}

void BaddieFactory::update(){
    
}

