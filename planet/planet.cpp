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
    
    density = 0;
}

void Planet::update(){
    if(this->acc.get_norm_2() > this->max_acc){
        this->acc.set_norm(max_acc);
    }
    this->vel+=this->acc*DT;
    

    this->pos+=this->vel*DT;
    
    this->acc*=0;
}

void Planet::applyForce(Vector force){
    this->acc+=force;
}


void Planet::draw(RenderWindow &window, Uint8 *pixels, Uint8 c, float angle){
    if(this->pos.y >= 0 && this->pos.y < height && this->pos.x >= 0 && this->pos.x < width){
        
        //float px = ((this->pos.x-width/2) * (this->pos.y / height)) + width/2;
        
        float py = sin(angle)*(this->pos.y-height/2) + height/2;
        
        
        int ind = floor(py) * width + floor(this->pos.x);
        Color c = HSVtoRGB((this->density*100)%255, 255, 255);
        pixels[ind*4]= c.r;
        pixels[ind*4 + 1] = c.g;
        pixels[ind*4+ 2] = 255;
        pixels[ind*4+ 3] += 100;
        //pixels[ind*4+ 3] = map_value(this->pos.y, 100, height, 0, 255);
    }
}

void Planet::setDensity(int d){
    this->density = d;
}
