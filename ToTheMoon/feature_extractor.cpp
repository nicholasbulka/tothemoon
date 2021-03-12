//
//  feature_extractor.cpp
//  example-app
//
//  Created by Nicholas Bulka on 10/27/20.
//

#include "feature_extractor.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

const int MAX_COUNT = 2000;

FeatureExtractor::FeatureExtractor(){

}

std::vector<cv::KeyPoint> FeatureExtractor::extractKeyPoints(std::vector<cv::Point2f> points, cv::Mat frame)
{
    std::vector<cv::KeyPoint> frame_key_points;
    
    frame_key_points.resize(points.size());
    
    std::vector<cv::Point2f>::const_iterator corner_it = points.begin();
    std::vector<cv::KeyPoint>::iterator keypoint_it = frame_key_points.begin();
    for( ; corner_it != points.end(); ++corner_it, ++keypoint_it )
        *keypoint_it = cv::KeyPoint( *corner_it, 1.0 );

    return frame_key_points;
    
}

std::vector<cv::Point2f> FeatureExtractor::extractPoints(cv::Mat mat, std::vector<cv::Point2f> points)
{

    cv::goodFeaturesToTrack(mat, points, MAX_COUNT, 0.01, 1, cv::Mat(), 3, 1, 0, 0.04);
    
    
    //visualization.
    int radius = 2;
    
    cv::Mat copy = mat.clone();
    

    for( size_t i = 0; i < points.size(); i++ )
    {
        cv::circle( copy, points[i], radius, cv::Scalar(0, 0, 255), cv::FILLED );
    }
    
    return points;
}
