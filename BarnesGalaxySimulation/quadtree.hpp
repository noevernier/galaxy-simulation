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


using namespace std;

class QuadTree {
public:
    int n;
    QuadTree *northwest;
    QuadTree *northeast;
    QuadTree *southwest;
    QuadTree *southeast;
    
    
    Rectangle chunk;
    vector<Planet> planets;
    
    bool divided;
    int total_mass;
    
    QuadTree();
    QuadTree(Rectangle chunk, int n);
    void subdivide();
    bool insert(Planet planet);
    void draw(RenderWindow &window);
    void query(Planet planet, vector<Planet> &found);
    float getMass();
    Vector getCenterOfMass();
};


#endif /* quadtree_hpp */
