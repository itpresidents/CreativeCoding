#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "Circle.h"
#include "DrawableShape.h"
#include "Square.h"
#include "cinder/Rand.h"


using namespace ci;
using namespace ci::app;
using namespace std;

const int NUM_SHAPES = 1000;

using DrawableShapeRef = std::shared_ptr< DrawableShape >;
using CircleRef = std::shared_ptr<Circle>;
using SquareRef = std::shared_ptr<Square>;
using DrawableShapes = std::vector<DrawableShapeRef>;

class CirclesApp : public AppNative {
  public:
	void setup() override;
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

    DrawableShapes mShapes;
    
};

void CirclesApp::setup()
{

    mShapes.resize( NUM_SHAPES );

    for( int i = 0; i < NUM_SHAPES; ++i ) {
		
        if(i % 2 == 0 ){
        
            mShapes[i].reset( new Square( randFloat( 0, getWindowWidth() ), randFloat( 0, getWindowHeight() ) ) );
            
        }else{
            mShapes[i].reset( new Circle( randFloat( 0, getWindowWidth() ), randFloat( 0, getWindowHeight() ) ) );
        }
    
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
	
    for( auto& shape : mShapes ) {
        shape->update();
        shape->draw();
    }
}

CINDER_APP_NATIVE( CirclesApp, RendererGl )
