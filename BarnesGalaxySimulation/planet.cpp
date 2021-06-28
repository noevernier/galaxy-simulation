#include "utils.hpp"
#include "planet.hpp"

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
    float norm = sqrtf(pow(acc.x,2) + pow(acc.y, 2));
    if(norm > max_acc){
        acc = (acc/norm) * max_acc;
    }
    vel+=acc;
    
    /*float norm = sqrtf(pow(vel.x,2) + pow(vel.y, 2));
     if(norm > max_speed){
     vel = (vel/norm) * max_speed;
     }*/
    
    pos+=vel;
    
    acc = Vector2f(0,0);
}

void Planet::applyForce(Vector2f force){
    acc+=force/mass;
}
