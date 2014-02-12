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
    void setVisible(bool is);
    void setDown(bool is);
    void setForce(float f);
    void draw();
    
    ofVec3f pos;
    
private:
    
    bool visible;
    float force;
    bool isDown;
};

#endif /* defined(__tactonic_test__Tool__) */
