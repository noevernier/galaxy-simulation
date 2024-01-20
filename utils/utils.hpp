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
#include <thread>

#define DT 1


using namespace sf;
using namespace std;

const double G = 6.674e-11;
const int n_planet = 7000;
const int width = 800;
const int height = 800;
const float precision = 1;

float RandomFloat(float min, float max);
float map_value(double inValue, double minInRange, double maxInRange, double minOutRange,double maxOutRange);
sf::Color HSVtoRGB(float H, float S, float V);
#endif /* utils_hpp */
