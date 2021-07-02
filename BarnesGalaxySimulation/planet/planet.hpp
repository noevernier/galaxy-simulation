//
//  planet.hpp
//  GalaxySimulation
//
//  Created by Noé on 25/06/2021.
//  Copyright © 2021 Noé. All rights reserved.
//

#ifndef planet_hpp
#define planet_hpp

#include "utils.hpp"

using namespace sf;

class Planet{
public:
    float mass;
    float size;
    float max_acc;
    Vector pos;
    Vector vel;
    Vector acc;
    Planet(float x, float y, float m);
    Planet(float x, float y, float m, float a, float r, float speed);
    void applyForce(Vector force);
    void draw(RenderWindow &window,  Uint8 * pixels, Uint8 c);
    void update();
};

#endif /* planet_hpp */
