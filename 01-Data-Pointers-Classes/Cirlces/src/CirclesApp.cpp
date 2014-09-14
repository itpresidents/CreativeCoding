#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "Circle.h"

#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

const int NUM_CIRCLES = 1000;

class CirclesApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    std::vector<std::shared_ptr<Circle>> mCircles;
        
};

void CirclesApp::setup()
{
    
    mCircles.resize( NUM_CIRCLES );
    for( int i = 0; i < NUM_CIRCLES; ++i ) {
        mCircles[i].reset( new Circle( randFloat( 0, getWindowWidth() ), randFloat( 0, getWindowHeight() ) ) );
    }
    
}

void CirclesApp::mouseDown( MouseEvent event )
{
}

void CirclesApp::update()
{
}

void CirclesApp::draw()
{
    // clear out the window with black
    gl::clear( Color( 0, 0, 0 ) );
    for( int i = 0; i < NUM_CIRCLES; ++i ) {
        mCircles[i]->draw();
    }
    
    
    
    
}

CINDER_APP_NATIVE( CirclesApp, RendererGl )
