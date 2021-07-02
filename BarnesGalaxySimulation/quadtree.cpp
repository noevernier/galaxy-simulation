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

float QuadTree::getMass(){
    float ttm = 0;
    for (int i = 0; i < planets.size(); i++) {
        ttm += planets[i].mass;
    }
    if(!this->divided){
        return ttm;
    } else {
        return ttm+ this->northeast->getMass() + this->northwest->getMass()+this->southeast->getMass()+this->southwest->getMass();
    }
}

Vector2f QuadTree::getCenterOfMass(){

    
    Vector2f com(0,0);
    
        
    for (int i = 0; i < planets.size(); i++) {
        
        com.x += planets[i].pos.x * planets[i].mass/getMass();
        com.y += planets[i].pos.y * planets[i].mass/getMass();
    }
    
    
    if(!this->divided){
        return com;
    } else {
        com.x += (this->northeast->getCenterOfMass().x * this->northeast->getMass() +
                  this->northwest->getCenterOfMass().x * this->northwest->getMass() +
                  this->southeast->getCenterOfMass().x * this->southeast->getMass() +
                  this->southwest->getCenterOfMass().x * this->southwest->getMass()) / (
                  this->northeast->getMass() +  this->northwest->getMass() + this->southeast->getMass() +this->southwest->getMass()) ;
        
        com.y += (this->northeast->getCenterOfMass().y * this->northeast->getMass() +
                  this->northwest->getCenterOfMass().y * this->northwest->getMass() +
                  this->southeast->getCenterOfMass().y * this->southeast->getMass() +
                  this->southwest->getCenterOfMass().y * this->southwest->getMass())/ (
                                                                                       this->northeast->getMass() +  this->northwest->getMass() + this->southeast->getMass() +this->southwest->getMass()) ;
        return com;
    }
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

void QuadTree::query(Planet planet, vector<Planet> &found){
    
    float total_mass = getMass();
    Vector2f center_of_mass = getCenterOfMass();
    
    float dist = sqrt(pow(planet.pos.x - center_of_mass.x, 2) + pow(planet.pos.y - center_of_mass.y, 2));
    float theta = this->boundary.w / dist;
    if(theta < 0.5 && dist>1){
        Planet p(center_of_mass.x, center_of_mass.y, total_mass);
        found.push_back(p);
    } else {
        this->northwest->query(planet, found);
        this->northeast->query(planet, found);
        this->southeast->query(planet, found);
        this->southwest->query(planet, found);
    }
    
    
}
