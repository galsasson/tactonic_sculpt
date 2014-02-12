//
//  MaterialBlock.cpp
//  tactonic_test
//
//  Created by Gal Sasson on 1/31/14.
//
//

#include "MaterialBlock.h"


MaterialBlock::MaterialBlock()
{
    
}

void MaterialBlock::setup(int w, int h, int d)
{
    width = w;
    height = h;
    depth = d;
//    center = c;
//    size = s;
    
    initGeometry();
}

void MaterialBlock::update()
{
    for (int i=0; i<particles.size(); i++)
    {
        particles[i]->update();
        mesh.setVertex(i, (ofVec3f)*particles[i]);
    }
}

void MaterialBlock::draw()
{
//    ofSetColor(100);
    ofSetColor(255);
    ofFill();
    mesh.disableColors();
//    mesh.drawVertices();
    mesh.enableNormals();
    mesh.drawFaces();
//    mesh.draw();
//    ofSetColor(255);
    mesh.drawWireframe();
//    mesh.drawVertices();
}

void MaterialBlock::setToolPosition(ofVec3f p, float rad)
{
    for (int i=0; i<particles.size(); i++)
    {
        Vertex *v = particles[i];
        ofVec3f offset = (*v)-p;
        ofVec2f offset2d = ofVec2f(offset.x, offset.y);
        if (offset2d.length() < rad)
        {
            float newZ = p.z + rad * cos(offset2d.length()/rad);
            if (newZ > v->z) {
                v->z = newZ;
            }
        }
    }
}


void MaterialBlock::repulse(ofVec3f p, float rad)
{
    for (int i=0; i<particles.size(); i++)
    {
        Vertex *v = particles[i];
        ofVec3f offset = (*v)-p;
        float l = offset.length();
        if (l < rad) {
            // lerp force strength inside rad
            float strength = ofMap(l, 0, rad, 1, 0);
            v->applyForce(offset.normalized() * strength);
        }
    }
}

void MaterialBlock::attract(ofVec3f p, float rad)
{
    
}

void MaterialBlock::initGeometry()
{
//    particles = new vector<Vertex*>();
    // create vertices
    mesh.clearVertices();
    mesh.clearColors();
    mesh.clearNormals();
    
    float zStep = 0.008;
    float zDepth = 0.5+zStep*depth;
    float yStep = (float)2/height;
    float xStep = (float)2/width;
    for (float z=0.5; z<zDepth; z+=zStep)
    {
        for (float y=-1; y<=1; y+=yStep)
        {
            for (float x=-1; x<=1; x+=xStep)
            {
                Vertex *v = new Vertex();
                v->setup(ofVec3f(x, y, z));// + ofVec3f(ofRandom(xStep), ofRandom(yStep), ofRandom(zStep)));
                particles.push_back(v);
                mesh.addVertex((ofVec3f)(*v));
                mesh.addColor(ofColor(255, 255, 255, 255));//ofFloatColor(1, 1, 1));
                mesh.addNormal(ofVec3f(0, 0, -1));
            }
        }
    }
    
    // create indices
    mesh.clearIndices();
    int span = width+1;
    for (int y=0; y<height; y++)
    {
        for (int x=0; x<width; x++)
        {
            mesh.addIndex(y*span + x);
            mesh.addIndex(y*span + x+1);
            mesh.addIndex((y+1)*span + x);

            mesh.addIndex((y+1)*span + x);
            mesh.addIndex(y*span + x+1);
            mesh.addIndex((y+1)*span + x+1);
        }
    }
    
    mesh.enableColors();
    mesh.enableIndices();
    mesh.enableNormals();
}