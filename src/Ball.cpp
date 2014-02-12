//
//  Ball.cpp
//  tactonic_test
//
//  Created by Gal Sasson on 1/9/14.
//
//

#include "Ball.h"

Ball::Ball()
{
    pos = ofVec2f(0, 0);
    visible = true;
    isDown = false;
    force = 0;
}

void Ball::setPos(float x, float y, float z, float hysteresis)
{
    pos.x += (x - pos.x) * (1-hysteresis);
    pos.y += (y - pos.y) * (1-hysteresis);
    pos.z += (z - pos.z) * (1-hysteresis);
}

void Ball::setPos(ofVec3f pos, float hysteresis)
{
    setPos(pos.x, pos.y, pos.z, hysteresis);
}

void Ball::setVisible(bool is)
{
    visible = is;
}

void Ball::setDown(bool is)
{
    isDown = false;
}

void Ball::setForce(float f)
{
    force = f;
}

void Ball::draw()
{
    if (!visible) {
        return;
    }
    
    ofPushMatrix();
    ofTranslate(pos);
    
    ofNoFill();
    ofSetLineWidth(2);
    if (force > 20000) {
        ofSetColor(ofMap(force, 20000, 50000, 180, 255), 180, 120);
    }
    else {
        ofSetColor(150);
    }

    float s = ofMap(force, 0, 50000, 40, 5);
    ofBox(0, 0, 0, 10);
//    ofSphere(0, 0, 0, 10);//pos.x, pos.y, pos.y, 10);
//    ofEllipse(0, 0, s, s);
    
    ofPopMatrix();
}