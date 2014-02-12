//
//  ForceMap.cpp
//  example_Basic
//
//  Created by Gal Sasson on 1/7/14.
//
//

#include "ForceMap.h"
#define MAX_FORCE 3872

ForceMap::ForceMap()
{
    width = 0;
    height = 0;
}

void ForceMap::init(int w, int h, float size)
{
    width = w;
    height = h;
    squareSize = size;
    
    vector<ofVec3f> verts;
    vector<ofIndexType> indices;
    vector<ofFloatColor> colors;
    
    for (int y=0; y<h+2; y++)
    {
        for (int x=0; x<w+2; x++)
        {
            verts.push_back(ofVec3f(x*squareSize, y*squareSize, 0));
            colors.push_back(ofFloatColor(0, 0, 1));
        }
    }
    
    // fill indices
    for (int y=0; y<h+1; y++)
    {
        for (int x=0; x<w+1; x++)
        {
#ifdef USE_TRIANGLES
            // first triangle
            indices.push_back(y*(w+2) + x);
            indices.push_back(y*(w+2) + x+1);
            indices.push_back((y+1)*(w+2) + x);
            
            // second triangle
            indices.push_back((y+1)*(w+2) + x);
            indices.push_back(y*(w+2) + x+1);
            indices.push_back((y+1)*(w+2) + x+1);
#else
            indices.push_back(y*(w+2) + x);
            indices.push_back(y*(w+2) + x+1);
            indices.push_back((y+1)*(w+2) + x+1);
            indices.push_back((y+1)*(w+2) + x);
#endif
        }
    }
    
    model.setVertexData(&verts[0], verts.size(), GL_STATIC_DRAW);
    model.setIndexData(&indices[0], indices.size(), GL_STATIC_DRAW);
    model.setColorData(&colors[0], colors.size(), GL_STATIC_DRAW);
    
    // allocate FBO
    image.allocate((width+1)*squareSize, (height+1)*squareSize);
    image.begin();
    ofClear(0);
    image.end();
}

void ForceMap::updateForce(TactonicFrame *frame)
{
    vector<ofFloatColor> colors;

    for (int y=0; y<height+2; y++)
    {
        for (int x=0; x<width+2; x++)
        {
            if (y==0 || y==height+1 || x==0 || x==width+1) {
                colors.push_back(ofFloatColor(0, 0, 0.2));
                continue;
            }
            
            float force = (float)frame->forces[(frame->rows-(y))*frame->cols + (x-1)];
            colors.push_back(ofFloatColor(force/MAX_FORCE, 0, 0.2f-(force/MAX_FORCE)*0.2));
        }
    }
    
    model.setColorData(&colors[0], colors.size(), GL_STATIC_DRAW);
}

void ForceMap::render()
{
    image.begin();
#ifdef USE_TRIANGLES
    model.drawElements(GL_TRIANGLES, (width+1)*(height+1)*6);
#else
    model.drawElements(GL_QUADS, (width+1)*(height+1)*4);
#endif
    image.end();
}

ofFbo& ForceMap::getImage()
{
    return image;
}


