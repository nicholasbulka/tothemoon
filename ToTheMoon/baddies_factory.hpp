//
//  baddies_factory.hpp
//  ToTheMoon
//
//  Created by Nicholas Bulka on 3/10/21.
//  Copyright © 2021 Nicholas Bulka. All rights reserved.
//

#ifndef baddies_factory_hpp
#define baddies_factory_hpp


#include "baddies.hpp"

#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


class BaddieFactory
{
public:
    BaddieFactory(int baddieNumber);
    ~BaddieFactory();
    //topL, topR, bottomL, bottomR
    std::vector<Baddie> _baddieSwarm;
    void update();

    
private:
    void updateBaddies();
};
#endif /* baddies_hpp */
