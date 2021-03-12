//
//  ship_factory.cpp
//  ToTheMoon
//
//  Created by Nicholas Bulka on 2/28/21.
//  Copyright © 2021 Nicholas Bulka. All rights reserved.
//

#include "ship_factory.hpp"

/**
 * Concrete Products provide various implementations of the Product interface.
 */
class ConcreteProduct1 : public Product {
 public:
  std::string Operation() const override {
    return "{Result of the ConcreteProduct1}";
  }
};
class ConcreteProduct2 : public Product {
 public:
  std::string Operation() const override {
    return "{Result of the ConcreteProduct2}";
  }
};
