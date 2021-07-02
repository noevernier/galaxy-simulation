//
//  quadtree.hpp
//  GalaxySimulation
//
//  Created by Noé on 27/06/2021.
//  Copyright © 2021 Noé. All rights reserved.
//

#ifndef quadtree_hpp
#define quadtree_hpp

#include "rectangle.hpp"
#include "planet.hpp"
#include "utils.hpp"
#include <vector>

using namespace std;

class QuadTree {
public:
    int n;
    QuadTree *northwest;
    QuadTree *northeast;
    QuadTree *southwest;
    QuadTree *southeast;
    
    
    Rectangle boundary;
    vector<Planet> planets;
    
    bool divided;
    
    QuadTree();
    QuadTree(Rectangle boundary, int n);
    void subdivide();
    bool insert(Planet planet);
    void draw(RenderWindow &window);
    void query(Planet planet, vector<Planet> &found);
    float getMass();
    Vector2f getCenterOfMass();
};


#endif /* quadtree_hpp */
