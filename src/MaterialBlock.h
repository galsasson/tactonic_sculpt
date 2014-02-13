//
//  MaterialBlock.h
//  tactonic_test
//
//  Created by Gal Sasson on 1/31/14.
//
//

#ifndef __tactonic_test__MaterialBlock__
#define __tactonic_test__MaterialBlock__

#include <iostream>
#include "ofMain.h"

#include "Vertex.h"

class MaterialBlock
{
public:
    
    MaterialBlock();
    void setup(int w, int h, int d);
    void update();
    void draw();
    
    bool setToolPosition(ofVec3f p, float rad);
    void repulse(ofVec3f p, float rad);
    void attract(ofVec3f p, float rad);
    
    void reset();
    
    int width, height, depth;
    vector<Vertex*> particles;
    ofMesh mesh;
    ofVbo vbo;
    
private:
    void initGeometry();
};

#endif /* defined(__tactonic_test__MaterialBlock__) */
