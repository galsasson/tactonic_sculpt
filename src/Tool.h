//
//  Tool.h
//  tactonic_test
//
//  Created by Gal Sasson on 1/31/14.
//
//

#ifndef __tactonic_test__Tool__
#define __tactonic_test__Tool__

#include <iostream>
#include "ofMain.h"

class Tool
{
public:
    Tool();
    void setPos(float x, float y, float z, float hysteresis);
    void setPos(ofVec3f pos, float hysteresis);
    void setArea(ofVec3f min, ofVec3f max);
    void setVisible(bool is);
    void setDown(bool is);
    void setForce(float f);
    void draw();
    
    ofVec3f getWorldPos();
    
    // always from -1 - 1
    ofVec3f pos;
    
    // the real world size of the surface
    ofVec3f areaCenter;
    ofVec3f scale;
    
    bool inMaterial;
private:
    
    bool visible;
    float force;
    bool isDown;
};

#endif /* defined(__tactonic_test__Tool__) */
