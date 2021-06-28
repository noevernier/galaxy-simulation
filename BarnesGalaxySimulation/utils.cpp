//
//  utils.cpp
//  GalaxySimulation
//
//  Created by Noé on 28/06/2021.
//  Copyright © 2021 Noé. All rights reserved.
//

#include "utils.hpp"

float RandomFloat(float min, float max)
{
    assert(max > min);
    float random = ((float) rand()) / (float) RAND_MAX;
    float range = max - min;
    return (random*range) + min;
}

float map_value(float inValue, float minInRange, float maxInRange, float minOutRange,float maxOutRange)
{
    float a = (maxOutRange - minOutRange) / (maxInRange - minInRange);
    return minOutRange + (inValue - minInRange) * a;
}
