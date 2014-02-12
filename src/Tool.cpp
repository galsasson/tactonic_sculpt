//
//  Tool.cpp
//  tactonic_test
//
//  Created by Gal Sasson on 1/31/14.
//
//

#include "Tool.h"

Tool::Tool()
{
    pos = ofVec3f(0, 0, -1);
    visible = true;
    isDown = false;
    force = 0;
}

void Tool::setPos(float x, float y, float z, float hysteresis)
{
    pos.x += (x - pos.x) * (1-hysteresis);
    pos.y += (y - pos.y) * (1-hysteresis);
    z = ofMap(z, 0, 1, 0.45, 0.7);
    pos.z += (z - pos.z) * (1-hysteresis);
}

void Tool::setPos(ofVec3f pos, float hysteresis)
{
    setPos(pos.x, pos.y, pos.z, hysteresis);
}

void Tool::setVisible(bool is)
{
    visible = is;
}

void Tool::setDown(bool is)
{
    isDown = false;
}

void Tool::setForce(float f)
{
    force = f;
}

void Tool::draw()
{
    if (!visible) {
        return;
    }
    
    ofPushMatrix();
    ofTranslate(pos);
    
    ofFill();
    if (pos.z > 0.5) {
        ofSetColor(ofMap(pos.z, 0.5, 1, 180, 255), 50, 50);
    }
    else {
        ofSetColor(0, 0, 255);
    }
    
    ofSphere(0, 0, 0, 0.06);
        
    ofPopMatrix();
}