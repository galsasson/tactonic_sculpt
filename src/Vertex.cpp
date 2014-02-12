//
//  Vertex.cpp
//  tactonic_test
//
//  Created by Gal Sasson on 1/31/14.
//
//

#include "Vertex.h"

Vertex::Vertex()
{
    friction = 0.2;
    mass = 50;
}

void Vertex::setup(ofVec3f p)
{
    set(p);
    restPos = p;
}

void Vertex::update()
{
    vel += acc;
//    x += vel.x;
//    y += vel.y;
    z += abs(vel.z);
    
    // cheap friction here
    vel *= 1-friction;
    
    acc.set(0);
}

void Vertex::applyForce(ofVec3f force)
{
    acc += force/mass;
}

void Vertex::applyGravity(ofVec3f force)
{
    acc += force;
}

