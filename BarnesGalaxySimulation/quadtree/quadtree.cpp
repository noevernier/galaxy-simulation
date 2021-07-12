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
    
    
    if (!this->chunk.contains(planet)) {
        return false;
    }
    
    this->total_mass += planet.mass;
    this->center_of_mass += planet.pos * planet.mass;
    
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
    
    RectangleShape rectangle(Vector2f(chunk.w, chunk.h));
    rectangle.setPosition(chunk.x, chunk.y);
    rectangle.setFillColor(Color(255,255,255,0));
    rectangle.setOutlineThickness(1);
    rectangle.setOutlineColor(Color(255,255,255,100));
    window.draw(rectangle);
    
    if(total_mass != 0 && center_of_mass.x != 0){
        CircleShape circle(total_mass);
        circle.setPosition(center_of_mass.x/total_mass, center_of_mass.y/total_mass);
        circle.setFillColor(Color(255,255,255,0));
        circle.setOutlineThickness(1);
        circle.setOutlineColor(Color(255,255,255,255));
        window.draw(circle);
    }

    if(this->divided){
        this->northwest->draw(window);
        this->northeast->draw(window);
        this->southwest->draw(window);
        this->southeast->draw(window);
    }
    
}

void QuadTree::query(Planet planet, vector<Planet> &found){
    if(this->total_mass != 0 && center_of_mass.x != 0 && center_of_mass.y != 0){
        
        Vector tot = (this->center_of_mass)/(this->total_mass);
                
        float dist = get_distance_2(planet.pos, tot);
        float theta = (this->chunk.w)*(this->chunk.h);
        
        if(theta < precision*precision*dist){
            Planet p(tot.x, tot.y, total_mass);
            found.push_back(p);
        } else if(this->divided){
            this->northwest->query(planet, found);
            this->northeast->query(planet, found);
            this->southeast->query(planet, found);
            this->southwest->query(planet, found);
        }
    }
}

void QuadTree::Free(){

    if(this->divided){
        this->northeast->Free();
        this->northwest->Free();
        this->southeast->Free();
        this->southwest->Free();
    }
    free(this);
    
}
