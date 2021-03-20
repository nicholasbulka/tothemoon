//
//  format.cpp
//  widjeos
//
//  Created by Nicholas Bulka on 9/2/20.
//  Copyright © 2020 Nicholas Bulka. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "format.hpp"

using namespace std;

KeyPointRecorder::KeyPointRecorder(){
    
}
KeyPointRecorder::~KeyPointRecorder(){
    
}

void KeyPointRecorder::keypointsToRecording(int frame, std::vector<cv::Point2f> points)
{

    list_of_frames_to_keypoints.push_back(std::make_tuple(frame, points));
        
    
}

    
void KeyPointRecorder::printValsToFile(std::string fileName, std::vector<std::tuple<int, std::vector<cv::Point2f>>> values){
    
    std::ostringstream os;
    for (std::tuple<int, std::vector<cv::Point2f>> i : values) {
        os << std::get<0>(i);
        os << ":";
        for(cv::Point2f point : std::get<1>(i)){
            os << "{";
            os << point.x;
            os << ",";
            os << point.y;
            os << "}";
        }
        os << "\n";
    }

    std::string str(os.str());
    ofstream myfile;
    myfile.open (fileName);
    myfile << str;
    myfile.close();
    
}
