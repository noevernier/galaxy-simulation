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
#include "../vector/vector.hpp"

#define DT 0.9


using namespace sf;
using namespace std;

const double G = 6.674e-11;
const int n_planet = 100000;
const int width = 800;
const int height = 800;

float RandomFloat(float min, float max);
float map_value(double inValue, double minInRange, double maxInRange, double minOutRange,double maxOutRange);

#endif /* utils_hpp */
