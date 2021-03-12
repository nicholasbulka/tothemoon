//
//  ship_factory.hpp
//  ToTheMoon
//
//  Created by Nicholas Bulka on 2/28/21.
//  Copyright © 2021 Nicholas Bulka. All rights reserved.
//

#ifndef ship_factory_hpp
#define ship_factory_hpp

#include <iostream>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


/**
 * The Spaceship interface declares the operations that all concrete Spaceships must
 * implement.
 */

class Spaceship {
  public:
    virtual ~Spaceship() {}
    virtual void PaintShip(cv::Mat frame, std::vector<cv::Point> location) const = 0;
    bool getShouldDelete(){
        return shouldDelete;
    }
    std::vector<cv::Point> getLocation(){
        return location;
    }
    void draw(cv::Mat frame, std::vector<cv::Point> location) const {
    // Call the factory method to create a Spaceship object.
        cv::rectangle( frame,
                      location[0],
                      location[1],
                      cv::Scalar( 0, 255, 255 ),
                      cv::FILLED,
                      cv::LINE_8 );
    }
        
  private:
    std::vector<cv::Point> location;
    bool shouldDelete = false;

};

/**
 * Concrete Spaceships provide various implementations of the Spaceship interface.
 */
class Level1Spaceship : public Spaceship {
 public:
  void PaintShip(cv::Mat frame, std::vector<cv::Point> location) const override {
      
  }
};
class Level2Spaceship : public Spaceship {
 public:
  void PaintShip(cv::Mat frame, std::vector<cv::Point> location) const override {
      
  }
};


/**
 * The Creator class declares the factory method that is supposed to return an
 * object of a Spaceship class. The Creator's subclasses usually provide the
 * implementation of this method.
 */

class Creator {
  /**
   * Note that the Creator may also provide some default implementation of the
   * factory method.
   */
 public:
  virtual ~Creator(){};
  virtual Spaceship* FactoryMethod() const = 0;
  /**
   * Also note that, despite its name, the Creator's primary responsibility is
   * not creating Spaceships. Usually, it contains some core business logic that
   * relies on Spaceship objects, returned by the factory method. Subclasses can
   * indirectly change that business logic by overriding the factory method and
   * returning a different type of Spaceship from it.
   */
    
};

/**
 * Concrete Creators override the factory method in order to change the
 * resulting Spaceship's type.
 */
class ConcreteCreator1 : public Creator {
  /**
   * Note that the signature of the method still uses the abstract Spaceship type,
   * even though the concrete Spaceship is actually returned from the method. This
   * way the Creator can stay independent of concrete Spaceship classes.
   */
 public:
  Spaceship* FactoryMethod() const override {
    return new Level1Spaceship();
  }
};

class ConcreteCreator2 : public Creator {
 public:
  Spaceship* FactoryMethod() const override {
    return new Level2Spaceship();
  }
};

/**
 * The Application picks a creator's type depending on the configuration or
 * environment.
 */

#endif /* ship_factory_hpp */
