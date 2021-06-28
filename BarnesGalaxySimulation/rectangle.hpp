//
//  rectangle.hpp
//  GalaxySimulation
//
//  Created by Noé on 27/06/2021.
//  Copyright © 2021 Noé. All rights reserved.
//

#ifndef rectangle_hpp
#define rectangle_hpp

#include <stdio.h>
#include "planet.hpp"

class Rectangle{
public:
    float x, y, w, h;
    Rectangle();
    Rectangle(float x, float y, float w, float h);
    
    bool contains(Planet planet);
    bool intersects(Rectangle range);
};

#endif /* rectangle_hpp */
