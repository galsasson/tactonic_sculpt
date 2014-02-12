#pragma once

#include "ofMain.h"
#include "ofxTactonic.h"
#include "ForceMap.h"
#include "Ball.h"
#include "MaterialBlock.h"
#include "Tool.h"
#include "ofxOsc.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void exit();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void frameCallback(TactonicFrameEvent *evt);

    bool initialized = false;
    
private:
    ofxTactonic tactonic;
    TactonicFrame* frame;
    bool isDown;
    ofEasyCam cam;
    ofLight light;
    MaterialBlock material;
    
    
    Tool tool;

    ofVec2f sensorSizePixels;
    ofVec2f sensorSquareSizePixels;
    ofVec3f sensorToScreen;
    ofMutex mutex;
    
    ofVec3f lastPos;
    ofVec2f maxPos;
    float maxForce;
    float totalForce;
    
    vector<ofVec2f> xLineScan;
    vector<ofVec2f> yLineScan;
    void calcLineScan(float x, float y);
    
    // 3D position with coordinates of (-1, -1, -1)-->(1, 1, 1)
    ofVec3f unitPosition;
    
    ofVec3f screenPosition;
    
    // OSC
    ofxOscSender oscSend;
    void sendOscPosition(float x, float y, float z, float hyst);
};
