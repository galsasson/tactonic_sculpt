#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
testApp *app;

int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
    app = new testApp();
	ofRunApp(app);
}

void FrameCallback(TactonicFrameEvent *evt)
{
    if (app->initialized) {
        app->frameCallback(evt);
    }
}
