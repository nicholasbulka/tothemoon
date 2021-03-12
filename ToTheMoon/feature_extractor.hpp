//
//  feature_extractor.hpp
//  example-app
//
//  Created by Nicholas Bulka on 10/27/20.
//

#ifndef feature_extractor_hpp
#define feature_extractor_hpp
#include <opencv2/opencv.hpp>


class FeatureExtractor
{
public:
    FeatureExtractor();
    std::vector<cv::Point2f> extractPoints(cv::Mat mat, std::vector<cv::Point2f> points);
    std::vector<cv::KeyPoint> extractKeyPoints(std::vector<cv::Point2f> points, cv::Mat frame);
    
private:
    

};

#endif /* feature_extractor_hpp */
