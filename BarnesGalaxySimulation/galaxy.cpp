//
//  galaxy.cpp
//  GalaxySimulation
//
//  Created by Noé on 28/06/2021.
//  Copyright © 2021 Noé. All rights reserved.
//

#include "galaxy.hpp"


Galaxy::Galaxy(int planet_number, float size, float min_mass, float max_mass, bool draw_qt) {
    this->n = planet_number;
    this->s = size;
    this->min_mass = min_mass;
    this->max_mass = max_mass;
    this->draw_qt = draw_qt;
    this->chunk = new Rectangle(0, 0, width, height);
}

void Galaxy::init() {
    for (int i = 0; i < n; i++) {
        
        float theta = RandomFloat(0,2*M_PI);
        float radius = RandomFloat(0,this->s);
        
        float m = map_value(radius, 0, this->s, this->min_mass, this->max_mass);
        
        float x = radius * cos(theta)+width/2;
        float y = radius * sin(theta)+height/2;
        float speed = map_value(radius, 0,this->s, 0,5);
        
        
        Planet planet(x, y, m, theta, radius, speed);
        planets.push_back(planet);
    }
    
    texture.create(width, height);
    pixels  = new Uint8[width * height * 4];
    
}

void Galaxy::update() {
    
    qt = new QuadTree(*chunk, 1);
    
    for (int i = 0; i < this->n; i++) {
        qt->insert(planets[i]);
    }
    
    Vector2f force;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(i!=j){
                float dist = pow( pow(planets[i].pos.x - planets[j].pos.x, 2) +  pow(planets[i].pos.y-planets[j].pos.y, 2), 3/2);
                if(dist < 2){
                    dist = 2;
                }
                force = planets[j].pos - planets[i].pos;
                force.x *= G*(planets[j].mass) / dist;
                force.y *= G*(planets[j].mass) / dist;
                planets[i].applyForce(force);
            }
        }
    }
}

void Galaxy::draw(RenderWindow &window) {
    for (int i = 0; i < width * height * 4; i++) {
        pixels[i] = 0;
        
    }
    
    vector<Planet> founds;
    qt->query(planets[0], founds);
    
    /*for(auto &p : founds){
        p.draw(window, pixels, 255);
    }*/
    
    for (int i = 0; i < n_planet; i++) {
        planets[i].update();
        Uint8 c = (Uint8)map_value(planets[i].mass, this->min_mass, this->max_mass, 0, 255);
        planets[i].draw(window, pixels, c);
    }
    
    texture.update(pixels);
    sprite.setTexture(texture);
    window.draw(sprite);
    if(draw_qt){qt->draw(window);}
}



