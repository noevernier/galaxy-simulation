//
//  galaxy.hpp
//  GalaxySimulation
//
//  Created by Noé on 28/06/2021.
//  Copyright © 2021 Noé. All rights reserved.
//

#ifndef galaxy_hpp
#define galaxy_hpp

#include "utils.hpp"
#include "planet.hpp"
#include "rectangle.hpp"
#include "quadtree.hpp"


using namespace std;

class Galaxy{
public:
    int n;
    float s;
    float min_mass;
    float max_mass;
    bool draw_qt;
    
    Texture texture;
    Sprite sprite;
    Uint8 *pixels;
    vector<Planet> planets;
    Rectangle* chunk;
    QuadTree* qt;
    
    Galaxy(int planet_number, float size, float min_mass, float max_mass, bool draw_qt);
    
    void init();
    void update();
    void draw(RenderWindow &window);
    
};

#endif
