#include "testApp.h"

void FrameCallback(TactonicFrameEvent *evt);
#define MAX_FORCE 3872
//#define DO_BLUR

//--------------------------------------------------------------
void testApp::setup(){
    
    glEnable(GL_DEPTH_TEST); //make sure we test depth for 3d
    
    ofSetVerticalSync(true);
    ofEnableLighting();
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofEnableBlendMode(ofBlendMode(OF_BLENDMODE_ALPHA));

    tactonic.init(true);
    tactonic.createFrame(&frame);
    tactonic.addFrameCallback(FrameCallback);
    tactonic.start();
    
    sensorSquareSizePixels = ofVec2f(ofGetWidth() / tactonic.getWidth(), ofGetWidth() / tactonic.getWidth());
    sensorSizePixels = ofVec2f(sensorSquareSizePixels.x * tactonic.getWidth(), sensorSquareSizePixels.y * tactonic.getHeight());
    
//    sensorToScreen = ofVec2f(ofGetWidth() / tactonic.getWidth(), ofGetHeight() / tactonic.getHeight());
    sensorToScreen = ofVec3f(500, -250, -250);
    
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
    maxForce = 0;
    isDown = false;
    
    material.setup(200, 200, 1);
    
    cam = ofEasyCam();
    cam.setPosition(500, 250, 1200);
    cam.setNearClip(0.01);

    light.enable();
    light.setPointLight();
    light.setPosition(0, 0, 3000);
    // osc
//    oscSend.setup("localhost", 9999);
    
    // initialized
    initialized = true;
}

//--------------------------------------------------------------
void testApp::update(){
    
    
//    material.repulse(tool.pos, 0.07);
    material.setToolPosition(tool.pos, 0.07);
    material.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableLighting();

    ofPushMatrix();

    ofScale(300, 300, 300);

    cam.begin();
    
    ofClear(0);

    
    
    material.draw();
    tool.draw();
    
//    ofSetColor(255);
//    light.draw();
    

    cam.end();

    ofPopMatrix();
    return;
    
    
    ofVec2f screenCoords = ofVec2f(ofGetWidth(), -100);
    ofSetColor(0,0,255);
    for (int i=1; i<xLineScan.size(); i++)
    {
        ofLine(xLineScan[i] * screenCoords + ofVec2f(0, 100), xLineScan[i-1] * screenCoords + ofVec2f(0, 100));
    }
    
    screenCoords = ofVec2f(100, ofGetHeight());
    for (int i=1; i<yLineScan.size(); i++)
    {
        ofLine(yLineScan[i] * screenCoords + ofVec2f(100, 0), yLineScan[i-1] * screenCoords + ofVec2f(100, 0));
    }
    
    cout<<"Max force/Total force ("<<maxForce<<"/"<<totalForce<<")\n";
}

//--------------------------------------------------------------
void testApp::exit(){
//    tactonic.stop();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

static unsigned long long lastFrameEvent = 0;

void testApp::frameCallback(TactonicFrameEvent *evt)
{
//    cout<<"start\n";
//    mutex.lock();
//    cout<<"start (after lock)\n";
    tactonic.copyFrame(evt->frame, frame);
    unsigned long long time = ofGetElapsedTimeMicros();
    unsigned long long rate = 1000000 / (time - lastFrameEvent);
    
    // find center of interaction
    int numPoints = frame->cols * frame->rows;
    int maxVal = 0;
    int *xVals = new int[frame->cols];
    int *yVals = new int[frame->rows];
    memset(xVals, 0, sizeof(int)*frame->cols);
    memset(yVals, 0, sizeof(int)*frame->rows);
    totalForce = 0;
    
    for (int i=0; i<numPoints; i++) {
        int x = i%frame->cols;
        int y = frame->rows - 1 - (i/frame->cols);
        int val = frame->forces[i];
        
        // find max value
        if (maxVal < frame->forces[i]) {
            maxVal = frame->forces[i];
            maxPos = ofVec2f(x, y);
        }
        
        maxForce = maxVal;
        
        totalForce += val;
        
        // sum all x in that row
        xVals[x] += val;
        // sum all y in that column
        yVals[y] += val;
    }
    
    if (maxVal < 25) {
        delete [] xVals;
        delete [] yVals;
//        mutex.unlock();
//        cout<<"end\n";
        return;
    }

    unitPosition.set(0, 0, 0);
    if (totalForce > 0) {
        // find x avg
        for (int i=0; i<frame->cols; i++)
        {
            unitPosition.x += xVals[i]*i;
        }
        unitPosition.x /= totalForce;
        
        // find y avg
        for (int i=0; i<frame->rows; i++)
        {
            unitPosition.y += yVals[i]*i;
        }
        unitPosition.y /= totalForce;
    }
    
    calcLineScan(unitPosition.x, unitPosition.y);
    
    unitPosition.x = ofMap(unitPosition.x, 0, tactonic.getWidth(), -1, 1);
    unitPosition.y = ofMap(unitPosition.y, 0, tactonic.getHeight(), -1, 1);
    unitPosition.z = ofMap(totalForce, 0, 50000, -1, 1);
    
//    sendOscPosition(unitPosition.x, unitPosition.y, unitPosition.z, 0.95);
    
    maxPos *= sensorToScreen;

    if (totalForce > 50) {
        tool.setPos(unitPosition, 0.95);
    }
    tool.setForce(totalForce);
    
    lastFrameEvent = time;
    delete [] xVals;
    delete [] yVals;
//    mutex.unlock();
//    cout<<"end\n";
}

void testApp::calcLineScan(float x, float y)
{
    xLineScan.clear();
    int fLine = (int)y;
    int sLine = (int)(y+1);
    float w1 = 1-(y-fLine);
    float w2 = 1-(sLine-y);
    fLine = frame->rows - fLine - 1;
    sLine = frame->rows - sLine - 1;
    for (int i=0; i<frame->cols; i++)
    {
        float f1 = (float)frame->forces[fLine*frame->cols + i]/MAX_FORCE * w1;
        float f2 = (float)frame->forces[sLine*frame->cols + i]/MAX_FORCE * w2;
        
        xLineScan.push_back(ofVec2f((float)i/tactonic.getWidth(), f1+f2));
    }
    
    yLineScan.clear();
    int fCol = (int)x;
    int sCol = (int)(x+1);
    w1 = 1-(x-fCol);
    w2 = 1-(sCol-x);
    for (int i=0; i<frame->rows; i++)
    {
        float f1 = (float)frame->forces[i*frame->cols + fCol]/MAX_FORCE * w1;
        float f2 = (float)frame->forces[i*frame->cols + sCol]/MAX_FORCE * w2;
        
        yLineScan.push_back(ofVec2f(f1+f2, (float)(frame->rows - 1 - i)/tactonic.getHeight()));
    }
}

void testApp::sendOscPosition(float x, float y, float z, float hyst)
{
    lastPos.x += (x - lastPos.x) * (1-hyst);
    lastPos.y += (y - lastPos.y) * (1-hyst);
    lastPos.z += (z - lastPos.z) * (1-hyst);

    ofxOscMessage msg;
    msg.setAddress("/pos");
    msg.addFloatArg(lastPos.x);
    msg.addFloatArg(lastPos.y);
    msg.addFloatArg(lastPos.z);
    oscSend.sendMessage(msg);
}
