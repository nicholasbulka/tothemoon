//
//  format.h
//  widjeos
//
//  Created by Nicholas Bulka on 9/2/20.
//  Copyright © 2021 Nicholas Bulka. All rights reserved.
//

#ifndef format_h
#define format_h

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

class KeyPointRecorder
{
public:
    KeyPointRecorder();
    ~KeyPointRecorder();
    void printValsToFile(std::string fileName, std::vector<std::tuple<int, std::vector<cv::Point2f>>> values );
    void keypointsToRecording(int frame, std::vector<cv::Point2f>);
    std::vector<std::tuple<int, std::vector<cv::Point2f>>> getListOfFramesToKp(){
        return list_of_frames_to_keypoints;
    }

    
private:
    
    std::vector<std::tuple<int, std::vector<cv::Point2f>>> list_of_frames_to_keypoints;

};
#endif /* format_h */
