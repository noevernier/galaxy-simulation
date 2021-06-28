//
//  quadtree.cpp
//  GalaxySimulation
//
//  Created by Noé on 27/06/2021.
//  Copyright © 2021 Noé. All rights reserved.
//

#include "quadtree.hpp"

QuadTree::QuadTree(){}

QuadTree::QuadTree(Rectangle boundary, int n){
    this->boundary = boundary;
    this->n = n;
    this->divided = false;
    
}

void QuadTree::subdivide(){
    float x = boundary.x;
    float y = boundary.y;
    float h = boundary.h;
    float w = boundary.w;
    
    Rectangle nw(x+w/2, y-h/2, w/2, h/2);
    this->northwest = new QuadTree(nw, n);
    
    Rectangle ne(x-w/2, y-w/2, w/2, h/2);
    this->northeast = new QuadTree(ne, n);
    
    Rectangle sw(x+w/2, y+w/2, w/2, h/2);
    this->southwest= new QuadTree(sw, n);
    
    Rectangle se(x-w/2, y+w/2, w/2, h/2);
    this->southeast = new QuadTree(se, n);
    
    this->divided = true;
}

bool QuadTree::insert(Planet planet){
    if (!this->boundary.contains(planet)) {
        return false;
    }
    
    if (this->planets.size() < this->n) {
        this->planets.push_back(planet);
        return true;
    }
    
    if (!this->divided) {
        this->subdivide();
    }
    if (this->northeast->insert(planet)) return true;
    if (this->northwest->insert(planet)) return true;
    if (this->southeast->insert(planet)) return true;
    if (this->southwest->insert(planet)) return true;
    
    return false;
}

void QuadTree::draw(RenderWindow &window){
    
    RectangleShape rectangle(Vector2f(boundary.w*2, boundary.h*2));
    rectangle.setPosition(boundary.x-boundary.w, boundary.y-boundary.h);
    rectangle.setFillColor(Color(255,255,255,0));
    rectangle.setOutlineThickness(1);
    rectangle.setOutlineColor(Color(255,255,255,100));
    window.draw(rectangle);
    if(this->divided){
        this->northwest->draw(window);
        this->northeast->draw(window);
        this->southwest->draw(window);
        this->southeast->draw(window);
    }
    
}

void QuadTree::query(Rectangle range, vector<Planet> &found){
    if(!this->boundary.intersects(range)){
        
    } else {
        for (int i = 0; i < planets.size(); i++) {
            if(range.contains(planets[i])){
                found.push_back(planets[i]);
            }
        }
        if(this->divided){
            this->northwest->query(range, found);
            this->northeast->query(range, found);
            this->southwest->query(range, found);
            this->southeast->query(range, found);
        }
    }
}
