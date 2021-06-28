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
    this->boundary = new Rectangle(width/2, height/2, width/2, height/2);
}

void Galaxy::init() {
    for (int i = 0; i < n; i++) {
        float theta = RandomFloat(0,2*M_PI);
        float rayon = RandomFloat(0,this->s);
        
        float m = map_value(rayon, 0, this->s, this->min_mass, this->max_mass);
        
        float x = rayon * cos(theta)+width/2;
        float y = rayon * sin(theta)+height/2;
        float speed = map_value(rayon, 0,this->s, 1,6);
        
        
        Planet planet(x, y, m, theta, rayon, speed);
        planets.push_back(planet);
    }
    
    texture.create(width, height);
    pixels  = new Uint8[width * height * 4];
    
}

void Galaxy::update() {
    
    qt = new QuadTree(*boundary, 1);
    
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
                force.x *= G*(planets[i].mass * planets[j].mass) / dist;
                force.y *= G*(planets[i].mass * planets[j].mass) / dist;
                planets[i].applyForce(force);
            }
        }
    }
}

void Galaxy::draw(RenderWindow &window) {
    for (int i = 0; i < width * height * 4; i++) {
        pixels[i] = 0;
        
    }
    
    for (int i = 0; i < n_planet; i++) {
        planets[i].update();
        //planets[i].draw(window);
        if(planets[i].pos.y >= 0 &&planets[i].pos.y < height && planets[i].pos.x >= 0 && planets[i].pos.x < width){
            int ind = floor(planets[i].pos.y) * width + floor(planets[i].pos.x);
            float c = map_value(planets[i].mass, this->min_mass, this->max_mass, 0, 255);
            pixels[ind*4]= 255;
            pixels[ind*4 + 1] = c;
            pixels[ind*4+ 2] = c;
            pixels[ind*4+ 3] = 255;
        }
    }
    
    texture.update(pixels);
    sprite.setTexture(texture);
    window.draw(sprite);
    if(draw_qt){qt->draw(window);}
}



