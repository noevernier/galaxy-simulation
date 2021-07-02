//
//  utils.hpp
//  GalaxySimulation
//
//  Created by Noé on 28/06/2021.
//  Copyright © 2021 Noé. All rights reserved.
//

#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>


using namespace sf;
using namespace std;

const float G = 0.03;
const int n_planet = 100;
const int width = 800;
const int height = 800;

float RandomFloat(float min, float max);
float map_value(float inValue, float minInRange, float maxInRange, float minOutRange,float maxOutRange);

#endif /* utils_hpp */
