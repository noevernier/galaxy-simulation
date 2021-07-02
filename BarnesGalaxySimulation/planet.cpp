#include "utils.hpp"
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
    
    max_acc = 0.3;
}

void Planet::update(){
    float norm = sqrtf(pow(this->acc.x,2) + pow(this->acc.y, 2));
    if(norm > this->max_acc){
        this->acc = (this->acc/norm) * this->max_acc;
    }
    this->vel+=this->acc;
    this->pos+=this->vel;
    
    this->acc = Vector2f(0,0);
}

void Planet::applyForce(Vector2f force){
    this->acc+=force/this->mass;
}
