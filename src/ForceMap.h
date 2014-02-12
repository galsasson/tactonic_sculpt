//
//  ForceMap.h
//  example_Basic
//
//  Created by Gal Sasson on 1/7/14.
//
//

#ifndef __example_Basic__ForceMap__
#define __example_Basic__ForceMap__

#include <iostream>
#include "ofMain.h"
#include "ofxTactonic.h"

class ForceMap
{
public:
    ForceMap();
    void init(int width, int height, float size);
    void updateForce(TactonicFrame *frame);
    void render();
    ofFbo& getImage();
    
private:
    ofVbo model;
    ofFbo image;
    int width, height;
    float squareSize;
};

#endif /* defined(__example_Basic__ForceMap__) */
