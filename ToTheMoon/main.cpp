//
//  main.cpp
//  ToTheMoon
//
//  Created by Nicholas Bulka on 2/27/21.
//  Copyright © 2021 Nicholas Bulka. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include "feature_extractor.hpp"
#include "ship_factory.hpp"
#include "baddies.hpp"
#include "baddies_factory.hpp"
#include "background.hpp"


int main(int argc, const char * argv[]) {
    cv::VideoCapture video =
    cv::VideoCapture("/Users/nicholasbulka/programming/creativ/ToTheMoon/ToTheMoon/song.mp4");
    
    if (!video.isOpened()) return -1;
    
    cv::Mat frame, previous_frame;
    
    int frame_width = video.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = video.get(cv::CAP_PROP_FRAME_HEIGHT);
    int frame_count = video.get(cv::CAP_PROP_FRAME_COUNT);
    
    double fps = video.get(cv::CAP_PROP_FPS);
    std::cout << fps << std::endl;
    
    FeatureExtractor* fe = new FeatureExtractor();
    std::vector<cv::Point2f> _points[2];
    std::vector<cv::KeyPoint> _keypoints[2];
    
    int count_frames = 0;
    cv::Mat gray_mat, prev_gray_mat, gray_mat_des, prev_gray_mat_des;
    cv::Mat blank = cv::Mat::zeros(cv::Size(frame_width, frame_height), CV_8UC3);
    cv::Mat blank_copy = cv::Mat::zeros(cv::Size(frame_width, frame_height), CV_8UC3);
    
    Creator* creator = new ConcreteCreator1();
    Spaceship* level1ss = creator->FactoryMethod();
    Creator* creator2 = new ConcreteCreator2();
    Spaceship* level2ss = creator->FactoryMethod();

    BaddieFactory* badguy_factory = new BaddieFactory(5);

    while(video.read(frame)){
        
        //Loop initialize.
        if(count_frames == 0){
            previous_frame = frame;
            count_frames++;
            continue;
        }
        
        //Loop body.
        cvtColor(frame, gray_mat, cv::COLOR_BGR2GRAY);
        cvtColor(previous_frame, prev_gray_mat, cv::COLOR_BGR2GRAY);

        _points[0] = fe->extractPoints(prev_gray_mat, _points[0]);
        _points[1] = fe->extractPoints(gray_mat, _points[1]);
        
        _keypoints[0] = fe->extractKeyPoints(_points[0], previous_frame);
        _keypoints[1] = fe->extractKeyPoints(_points[1], frame);
        
        if(cv::waitKey(25) >= 0){
            break;
        }
    
        
        std::vector<cv::Point> placeholder1 {cv::Point(5,7) , cv::Point(8,10) };
        std::vector<cv::Point> placeholder2 {cv::Point(18,18) , cv::Point(20,20) };

        //cv::drawKeypoints (frame, _keypoints[0], blank, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
        
        std::vector<cv::KeyPoint>::const_iterator it0 = _keypoints[0].begin(), end0 = _keypoints[0].end();
        std::vector<cv::KeyPoint>::const_iterator it1 = _keypoints[1].begin(), end1 = _keypoints[1].end();
        
        for( ; it0 != end0; ++it0 ) {
            cv::rectangle( blank,
                          cv::Point(it0->pt.x, it0->pt.y),
                          cv::Point(it0->pt.x+cos(0.5 * it0->pt.x), it0->pt.y+cos(0.5 * it0->pt.y)),
                          //flame
                          cv::Scalar( 34, 88, 226 ),
                          cv::FILLED,
                          cv::LINE_8 );
            
        }
  /*
  for( ; it0 != end0; ++it0 ) {
      cv::rectangle( blank,
                    cv::Point(it0->pt.x, it0->pt.y),
                    cv::Point(it0->pt.x+cos(0.5 * it0->pt.x), it0->pt.y+cos(0.5 * it0->pt.y)),
                    //flame
                    cv::Scalar( 34, 88, 226 ),
                    cv::FILLED,
                    cv::LINE_8 );
        */
        std::vector<Baddie>::iterator it;
    /*    for (it = badguy_factory->_baddieSwarm.begin();
        it != badguy_factory->_baddieSwarm.end(); ++it) {
            cv::Mat matrix_image = it->getBaddie();
            matrix_image.copyTo(blank(cv::Rect(it->corners[0], it->corners[1])));
        }*/
             
        level1ss->draw(blank, placeholder1);
        level1ss->draw(blank, placeholder2);
        
        
        cv::imshow("blank", blank);
        
        //Loop cleanup.
        previous_frame = frame;
        count_frames++;
        blank_copy.copyTo(blank);
        _moon_background.copyTo(blank(cv::Rect(600, 50, _moon_background.cols, _moon_background.rows)));
        
  //      if(count_frames == 50){
    //    }
    
        std::cout << count_frames << std::endl;

    }
    
    delete creator;
    delete creator2;
    video.release();
    
    return 0;
}
    
