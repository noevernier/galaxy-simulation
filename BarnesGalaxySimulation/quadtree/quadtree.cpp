//
//  quadtree.cpp
//  GalaxySimulation
//
//  Created by Noé on 27/06/2021.
//  Copyright © 2021 Noé. All rights reserved.
//

#include "quadtree.hpp"

QuadTree::QuadTree(){}

QuadTree::QuadTree(Rectangle chunk, int n){
    this->chunk = chunk;
    this->n = n;
    this->divided = false;
    this->total_mass = 0;
    
}

void QuadTree::subdivide(){
    float x = chunk.x;
    float y = chunk.y;
    float h = chunk.h;
    float w = chunk.w;
    
    Rectangle nw(x, y, w/2, h/2);
    this->northwest = new QuadTree(nw, n);
    
    Rectangle ne(x+w/2, y, w/2, h/2);
    this->northeast = new QuadTree(ne, n);
    
    Rectangle sw(x, y+h/2, w/2, h/2);
    this->southwest= new QuadTree(sw, n);
    
    Rectangle se(x+w/2, y+h/2, w/2, h/2);
    this->southeast = new QuadTree(se, n);
    
    this->divided = true;
}

bool QuadTree::insert(Planet planet){
    this->total_mass += planet.mass;
    if (!this->chunk.contains(planet)) {
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

Vector QuadTree::getCenterOfMass(){

    
    Vector com(0,0);
    
    if(planets.size()==1){
        for (int i = 0; i < this->n; i++) {
            cout << planets[i].pos << endl;
            com = com + planets[i].pos * planets[i].mass;
        }
    }
    
    
    if(!this->divided && planets.size()==1){
        return com / (float)this->total_mass;
    } else {
        com  = com + this->northeast->getCenterOfMass() * (float)this->northeast->total_mass +
        this->northwest->getCenterOfMass() * (float)this->northwest->total_mass +
        this->southeast->getCenterOfMass() * (float)this->southeast->total_mass +
        this->southwest->getCenterOfMass() * (float)this->southwest->total_mass;
        
        return com / ((float)this->northeast->total_mass+(float)this->northwest->total_mass+(float)this->southeast->total_mass+(float)this->southwest->total_mass);
    }
}

void QuadTree::draw(RenderWindow &window){
    
    RectangleShape rectangle(Vector2f(chunk.w, chunk.h));
    rectangle.setPosition(chunk.x, chunk.y);
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

void QuadTree::query(Planet planet, vector<Planet> &found){
    
    Vector center_of_mass = getCenterOfMass();
    
    float dist = get_distance(planet.pos, center_of_mass);

    float theta = (this->chunk.w * this->chunk.w) / dist;
    
    if(theta < 0.5 && dist>2){
        Planet p(center_of_mass.x, center_of_mass.y, total_mass);
        found.push_back(p);
    } else {
        this->northwest->query(planet, found);
        this->northeast->query(planet, found);
        this->southeast->query(planet, found);
        this->southwest->query(planet, found);
    }
    
}
