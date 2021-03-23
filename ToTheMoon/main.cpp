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
#include "format.hpp"
#include "opencv2/objdetect.hpp"

cv::CascadeClassifier eyes_cascade;
cv::Mat tv_load = cv::imread("/Users/nicholasbulka/programming/creativ/ToTheMoon/ToTheMoon/Tv_hd.png");
cv::Mat tv;
std::string eyes_cascade_name = "/usr/local/Cellar/opencv/4.5.0_5/share/opencv4/haarcascades/haarcascade_eye_tree_eyeglasses.xml";

int tv_edge_left = 115;
int tv_edge_right = 430;
int tv_edge_top = 110;
int tv_edge_bottom = 222;
int pause = 14;
int intro_length = 500;
int three_d_sep_x = 5;
int three_d_sep_y = 5;


std::vector<cv::Rect> detectEyes( cv::Mat frame_gray )
{
    //cv::Mat frame_gray;
    //cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    std::vector<cv::Rect> eyes;
    eyes_cascade.detectMultiScale( frame_gray, eyes );
    
    //-- Show what you got
    return eyes;
}


int main(int argc, const char * argv[]) {
    cv::VideoCapture video =
    cv::VideoCapture("/Users/nicholasbulka/programming/creativ/ToTheMoon/ToTheMoon/tothemoon.mp4");

    if( !eyes_cascade.load( eyes_cascade_name ) )
    {
        std::cout << "--(!)Error loading eyes cascade\n";
        return -1;
    };
    
    //cv::VideoCapture stream1(0);
    
    if (!video.isOpened()) return -1;
    
    cv::Mat frame, previous_frame_resized;
    cv::Mat live_frame;
    cv::Mat resized_live_frame;
    cv::Mat gray_resized;

    
    //int frame_width = video.get(cv::CAP_PROP_FRAME_WIDTH);
    //int frame_height = video.get(cv::CAP_PROP_FRAME_HEIGHT);
    
    int folder_image_width = 1120;
    int folder_image_height = 700;
    
    int rectangle_width_max = 35;
    int rectangle_height_max = 35;
    
    int rectangle_width_min = 20;
    int rectangle_height_min = 20;

    int frame_count = video.get(cv::CAP_PROP_FRAME_COUNT);
    
    double fps = video.get(cv::CAP_PROP_FPS);
    std::cout << "Frames per second : " << fps << std::endl;
    
    FeatureExtractor* fe = new FeatureExtractor();
    std::vector<cv::Point2f> _points[2];
    std::vector<cv::KeyPoint> _keypoints[2];
    
    int count_frames = 0;
    int count_images = 1;
    cv::Mat gray_mat, prev_gray_mat, gray_mat_des, prev_gray_mat_des;

   /*Creator* creator = new ConcreteCreator1();
    Spaceship* level1ss = creator->FactoryMethod();
    Creator* creator2 = new ConcreteCreator2();
    Spaceship* level2ss = creator->FactoryMethod();

    BaddieFactory* badguy_factory = new BaddieFactory(5); */
    KeyPointRecorder* kprecorder = new KeyPointRecorder();
    
    cv::Mat canvas = cv::Mat::zeros(cv::Size(folder_image_width + tv_edge_left + tv_edge_right, folder_image_height + tv_edge_top + tv_edge_bottom), CV_8UC3);
    
    //Create and initialize the VideoWriter object
       cv::VideoWriter oVideoWriter("/Users/nicholasbulka/programming/creativ/ToTheMoon/ToTheMoon/bounce.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
                                    fps, cv::Size(canvas.cols, canvas.rows), true);
       
       //If the VideoWriter object is not initialized successfully, exit the program
       if (oVideoWriter.isOpened() == false)
       {
           std::cout << "Cannot save the video to a file" << std::endl;
           std::cin.get(); //wait for any key press
           return -1;
       }


    cv::resize(tv_load, tv, cv::Size(folder_image_width + tv_edge_left + tv_edge_right, folder_image_height + tv_edge_top + tv_edge_bottom));


    while(video.read(frame)){
        
        
        //Loop body.
        cv::Mat resized;
        cv::resize(frame, resized, cv::Size(folder_image_width, folder_image_height));
        
        //Loop initialize.
        if(count_frames == 0){
            previous_frame_resized = resized;
            count_frames++;
            kprecorder->keypointsToRecording(0, std::vector<cv::Point2f>{cv::Point2f(5,5)});
            continue;
        }
        
        //live video read.
        //stream1.read(live_frame);
        //cv::resize(live_frame, resized_live_frame, cv::Size((int) (live_frame.size().width / 5), (int) (live_frame.size().height / 5)));
        //cv::cvtColor(resized_live_frame, gray_resized, cv::COLOR_BGR2GRAY);

        
        
        cvtColor(resized, gray_mat, cv::COLOR_BGR2GRAY);
        cvtColor(previous_frame_resized, prev_gray_mat, cv::COLOR_BGR2GRAY);

        _points[0] = fe->extractPoints(prev_gray_mat, _points[0]);
        _points[1] = fe->extractPoints(gray_mat, _points[1]);
        
        _keypoints[0] = fe->extractKeyPoints(_points[0], previous_frame_resized);
        _keypoints[1] = fe->extractKeyPoints(_points[1], resized);
        
        if(cv::waitKey(25) >= 0){
            break;
        }
         
        if(count_frames % pause == 0){ count_images++;}
        
        //std::string frame_file_path = "/Users/nicholasbulka/programming/creativ/ToTheMoon/doge/select/output/output/" + std::to_string(count_images) + ".jpg";
        
        std::string frame_file_path = "/Users/nicholasbulka/programming/creativ/ToTheMoon/ToTheMoon/images/output/" + std::to_string(count_images) + ".jpg";
        
        cv::Mat woman_load = cv::imread(frame_file_path, cv::IMREAD_GRAYSCALE);
        cv::Mat woman_tmp;
        //cv::Canny(woman_load, woman_load, 100, 200);
        cv::resize(woman_load, woman_tmp, cv::Size(folder_image_width, folder_image_height));
        
        cv::Mat woman;
        cv::Mat transfer = cv::Mat::zeros(woman_tmp.rows,
                                          woman_tmp.cols,
                                          woman_tmp.type());
        /*cv::Mat mask = cv::Mat::ones(woman_tmp.rows,
                                     woman_tmp.cols,
                                     woman_tmp.type());
          cv::Mat transfer_flip;
          cv::copyTo(transfer, transfer_flip, mask); */

        
        std::vector<cv::KeyPoint>::const_iterator it0 = _keypoints[0].begin(), end0 = _keypoints[0].end();
        //std::vector<cv::KeyPoint>::const_iterator it1 = _keypoints[1].begin(), end1 = _keypoints[1].end();
        std::vector<cv::Point2f> points_vec;
        for( ; it0 != end0; ++it0 ) {
            
            
            int x1 = it0->pt.x;
            int x2 = it0->pt.x;
            int y1 = it0->pt.y;
            int y2 = it0->pt.y;
                        
            //cv::Point xy = cv::Point(x, y);
            
         /*   cv::rectangle( music_points,
                          xy,
                          cv::Point(it0->pt.x+cos(0.5 * it0->pt.x), it0->pt.y+cos(0.5 * it0->pt.y)),
                          //flame
                          cv::Scalar( 34, 88, 226 ),
                          cv::FILLED,
                          cv::LINE_8 );
            
            */

            //woman_tmp(roi_flip).copyTo(transfer_flip(roi_flip));
            
            //cv::Rect roi_mid = cv::Rect(frame_width, frame_height/2 - y/2, 7,7);
            
            int rand_width = rand()%(rectangle_width_max - rectangle_width_min + 1) + rectangle_width_min;
            int rand_height = rand()%(rectangle_height_max - rectangle_height_min + 1) + rectangle_height_min;
            
            
            if(count_frames < intro_length ){
                
                rand_width = count_frames/50 + 2;
                rand_height = count_frames/50 + 2;
            }
            
            if(x1 > rectangle_width_max && y1 > rectangle_height_max){
                cv::Rect roi_second_mid = cv::Rect(x1-rand_width, y1-rand_height, rand_width, rand_height);
                woman_tmp(roi_second_mid).copyTo(transfer(roi_second_mid));

            };
                
            
            //woman_tmp(roi_mid).copyTo(transfer(roi_mid));

            
           /* cv::rectangle( music_points_mirror,
                          xy,
                          cv::Point(it0->pt.x+cos(0.5 * it0->pt.x), it0->pt.y+cos(0.5 * it0->pt.y)),
                          //flame
                          cv::Scalar( 34, 88, 226 ),
                          cv::FILLED,
                          cv::LINE_8 );*/
            
            //points_vec.push_back(xy);
        
            
        }
        
        cv::Mat mix;


        
        //if(count_frames > intro_length ){

            std::vector<cv::Rect> eyes_in_pic = detectEyes(woman_tmp);

            for(size_t eye = 0; eye < eyes_in_pic.size(); eye++){
                
                cv::Mat woman_canny;
                
                cv::Canny(woman_tmp(eyes_in_pic[eye]), woman_canny, 100, 200);
                                
                cv::Mat woman_r;
                cv::Mat bgr_chan2[3];
                cv::cvtColor(woman_canny, woman_r, cv::COLOR_GRAY2BGR);
                cv::split(woman_r, bgr_chan2); // split the BGR channesl
                bgr_chan2[1] = cv::Mat::zeros(woman_r.rows, woman_r.cols, CV_8UC1);
                bgr_chan2[0] = cv::Mat::zeros(woman_r.rows, woman_r.cols, CV_8UC1);
                cv::merge(bgr_chan2, 3, woman_r); // pack the image
                        
                cv::Mat woman_bg;
                cv::Mat bgr_chan01[3];
                cv::cvtColor(woman_canny, woman_bg, cv::COLOR_GRAY2BGR);
                cv::split(woman_bg, bgr_chan01); // split the BGR channesl
                bgr_chan01[2] = cv::Mat::zeros(woman_bg.rows, woman_bg.cols,CV_8UC1);
                cv::merge(bgr_chan01, 3, woman_bg); // pack the image
                        
                double alpha = 0.4; double beta;
                beta = 1 - alpha;
                                
                cv::Mat transfer_red, transfer_blue_green;
                cv::cvtColor(transfer, mix, cv::COLOR_GRAY2BGR);
                cv::cvtColor(transfer, transfer_red, cv::COLOR_GRAY2BGR);
                cv::cvtColor(transfer, transfer_blue_green, cv::COLOR_GRAY2BGR);
                
                //remove channel data from
                cv::cvtColor(woman_tmp, woman_bg, cv::COLOR_GRAY2BGR);

                
                int x = eyes_in_pic[eye].x;
                int y = eyes_in_pic[eye].y;
                int width = eyes_in_pic[eye].width;
                int height = eyes_in_pic[eye].height;
                bool greaterThanZero = x - three_d_sep_x > 0 && y - three_d_sep_y > 0;
                bool lessThanEdge = x + width + 2 * three_d_sep_x < transfer.cols && y + height + three_d_sep_y * 2 < transfer.rows;
                
                if(greaterThanZero && lessThanEdge){
                                    
                    cv::Rect bg_rect = cv::Rect(x, y, width, height);
                    cv::Rect r_rect = cv::Rect(x - three_d_sep_x, y - three_d_sep_y, width + 2 * three_d_sep_x, height + three_d_sep_y * 2);
                    
                    //woman(eyes_in_pic[eye]).copyTo(transfer(eyes_in_pic[eye]));
                    woman_r.copyTo(transfer_red(r_rect)); //gray
                    woman_bg(bg_rect).copyTo(transfer_blue_green(bg_rect)); //gray
                    
                    addWeighted( transfer_red, alpha, transfer_blue_green, beta, 0.0, mix);
                }

            }
        //}
        
        cv::cvtColor(transfer, woman, cv::COLOR_GRAY2BGR );

        kprecorder->keypointsToRecording(count_frames, points_vec);
                                             
        
        //


        std::vector<Baddie>::iterator it;
    /*    for (it = badguy_factory->_baddieSwarm.begin();
        it != badguy_factory->_baddieSwarm.end(); ++it) {
            cv::Mat matrix_image = it->getBaddie();
            matrix_image.copyTo(blank(cv::Rect(it->corners[0], it->corners[1])));
        }*/
    
                
        //Loop cleanup.
        previous_frame_resized = resized;
        count_frames++;
        //cv::flip(music_points_mirror, music_points_mirror, 0);

       /* music_points_mirror.copyTo(canvas(cv::Rect(100,
                                                   50 + music_points.rows,
                                                   music_points_mirror.cols,
                                                   music_points_mirror.rows)));
        music_points.copyTo(canvas(cv::Rect(100,
                                            50,
                                            music_points.cols,
                                            music_points.rows))); */

        Moon* moon = new Moon();
        cv::Mat moonbg = moon->get_moon();
        int moon_width = moonbg.cols;
        int moon_height = moonbg.rows;
        int moon_right_push = 50;
        int moon_top_spacing = tv_edge_top + 50;
        
        /*resized_live_frame.copyTo(canvas(cv::Rect(1000,
                                                  1000,
                                                  resized_live_frame.cols,
                                                  resized_live_frame.rows)));*/
        

        //woman_flip.copyTo(canvas(cv::Rect(0, woman.rows, woman_flip.cols, woman_flip.rows)));
        
        cv::Mat tv_gray;
        cvtColor(tv, tv_gray, cv::COLOR_BGR2GRAY);
        cvtColor(tv_gray, tv, cv::COLOR_GRAY2BGR);
        tv.copyTo(canvas(cv::Rect(0,0, tv.cols, tv.rows)));


        //blue_eye.copyTo(canvas(cv::Rect(blue_eye.x, blue_eye.y, blue_eye.width, blue_eye.height)));
        //red_eye.copyTo(canvas(cv::Rect(red_eye.x, red_eye.y, red_eye.width, red_eye.height)));
        woman.copyTo(canvas(cv::Rect(tv_edge_left, tv_edge_top, woman.cols, woman.rows)));
        
        std::cout << "canvas: " << canvas.channels() << std::endl;
        //std::cout << "mix: " << mix.channels() << std::endl;
        std::cout << "frame# : " << count_frames << std::endl;

        mix.copyTo(canvas(cv::Rect(tv_edge_left, tv_edge_top, mix.cols, mix.rows)));
        moonbg.copyTo(canvas(cv::Rect(folder_image_width - moon_width + moon_right_push, moon_top_spacing, moonbg.cols, moonbg.rows)));
                
        cv::imshow("canvas", canvas);
        
        //oVideoWriter.write(canvas);
        
        //clear.copyTo(music_points);
        //clear.copyTo(music_points_mirror);


        
  //      if(count_frames == 50){
    //    }
    
        //std::cout << count_frames << std::endl;
        float seconds = float(count_frames / fps);
        //std::cout << seconds << std::endl;
    }
    
   // delete creator;
    //delete creator2;
    kprecorder->printValsToFile("outs.txt", kprecorder->getListOfFramesToKp());
    video.release();
    oVideoWriter.release();
    
    return 0;
}
    
