//
//  planet.hpp
//  GalaxySimulation
//
//  Created by Noé on 25/06/2021.
//  Copyright © 2021 Noé. All rights reserved.
//

#ifndef planet_hpp
#define planet_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Planet{
public:
    float mass;
    float size;
    float max_acc;
    Vector2f pos;
    Vector2f vel;
    Vector2f acc;
    Planet(float x, float y, float m);
    Planet(float x, float y, float m, float a, float r, float speed);
    void applyForce(Vector2f force);
    void draw(RenderWindow &window);
    void update();
};

#endif /* planet_hpp */
