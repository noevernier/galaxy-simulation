#include "planet.hpp"

Planet::Planet(float x, float y, float m){
    pos.x = x;
    pos.y = y;
    mass = m;
}

Planet::Planet(float x, float y, float m, float a, float r, float speed){
    pos.x = x;
    pos.y = y;
    
    vel.x = speed*sin(a);
    vel.y = -speed*cos(a);
    
    acc.x = 0;
    acc.y = 0;
    mass = m;
    
    max_acc = 0.1;
}

void Planet::update(){
    if(this->acc.get_norm_2() > this->max_acc){
        this->acc.set_norm(max_acc);
    }
    this->vel+=this->acc;
    this->pos+=this->vel;
    
    this->acc*=0;
}

void Planet::applyForce(Vector force){
    this->acc+=force;
}


void Planet::draw(RenderWindow &window, Uint8 *pixels, Uint8 c){
    if(this->pos.y >= 0 && this->pos.y < height && this->pos.x >= 0 && this->pos.x < width){
        int ind = floor(this->pos.y) * width + floor(this->pos.x);
        pixels[ind*4]= 255;
        pixels[ind*4 + 1] = c;
        pixels[ind*4+ 2] = c;
        pixels[ind*4+ 3] = 255;
    }
}
