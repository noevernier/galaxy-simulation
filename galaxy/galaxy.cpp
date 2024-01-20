//
//  galaxy.cpp
//  GalaxySimulation
//
//  Created by Noé on 28/06/2021.
//  Copyright © 2021 Noé. All rights reserved.
//

#include "galaxy.hpp"

float Q_sqrt( float number )
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;
    
    x2 = number * 0.5F;
    y = number;
    i = * ( long * ) &y; // evil floating point bit level hacking
    i = 0x5f3759df - ( i >> 1 ); // what the fuck?
    y = * ( float * ) &i;
    y = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration
    //    y = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration, this can be removed
    
    return y;
}

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
        float radius = RandomFloat(0,this->s+(rand()%100)-50);
        
        float m = map_value(radius, 0, this->s, this->min_mass, this->max_mass);
        
        float x = radius * cos(theta)+width/2;
        float y = radius * sin(theta)+height/2;
        float speed = map_value(radius, 0,this->s, 1, 6);
        
        
        Planet planet(x, y, m, theta, radius, speed);
        planets.push_back(planet);
    }
    
    texture.create(width, height);
    pixels  = new Uint8[width * height * 4];
    
}

void Galaxy::update(int n_start, int n_end) {
    
    qt = new QuadTree(*chunk, 1);
    
    for (int i =  n_start; i <  n_end; i++) {
        qt->insert(planets[i]);
    }
    
    Vector force;
    
    for (int i = n_start; i <  n_end; i++) {
        
        vector<Planet> founds;
        qt->query(planets[i], founds);
        planets[i].setDensity(founds.size());
        
        for(int j = 0; j < founds.size(); j++){
            if(planets[i].pos.x != founds[j].pos.x && planets[i].pos.y != founds[j].pos.y){
                
                float dist_2 = get_distance_2(planets[i].pos, founds[j].pos);
                if(dist_2 < 4){
                    dist_2 = 4;
                }
                force = founds[j].pos - planets[i].pos;
                force.normalize();
                force *= G * (founds[j].mass) * Q_sqrt(dist_2);
                planets[i].applyForce(force);
            }
        }
    }
    qt->Free();
}

void Galaxy::draw(RenderWindow &window, float angle) {
    for (int i = 0; i < width * height * 4; i++) {
        pixels[i] = 0;
    }

    for (int i = 0; i < n_planet; i++) {
        planets[i].update();
        Uint8 c = (Uint8)map_value(planets[i].mass, this->min_mass, this->max_mass, 0, 255);
        planets[i].draw(window, pixels, c, angle);
    }
    
    texture.update(pixels);
    sprite.setTexture(texture);
    window.draw(sprite);
    
    if(draw_qt){qt->draw(window);}
}



