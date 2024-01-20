//
//  rectangle.cpp
//  GalaxySimulation
//
//  Created by Noé on 27/06/2021.
//  Copyright © 2021 Noé. All rights reserved.
//

#include "rectangle.hpp"
Rectangle::Rectangle(){}
Rectangle::Rectangle(float x, float y, float w, float h){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

bool Rectangle::contains(Planet planet){
    return (planet.pos.x > x && planet.pos.x < x+w && planet.pos.y > y && planet.pos.y < y+h);
}

