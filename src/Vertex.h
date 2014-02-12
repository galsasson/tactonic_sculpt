//
//  Vertex.h
//  tactonic_test
//
//  Created by Gal Sasson on 1/31/14.
//
//

#ifndef __tactonic_test__Vertex__
#define __tactonic_test__Vertex__

#include <iostream>
#include "ofMain.h"

class Vertex : public ofVec3f
{
public:
    Vertex();
    void setup(ofVec3f p);
    void update();
    
    void applyForce(ofVec3f force);
    void applyGravity(ofVec3f force);
    
    ofVec3f restPos;
    ofVec3f vel, acc;
    float mass;
    float friction;
    
};

#endif /* defined(__tactonic_test__Vertex__) */
