#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "CollisionSystem.h"
#include "Circle.h"
#include "Square.h"

using namespace ci;
using namespace ci::app;
using namespace std;

enum ShapeType {
	SQUARE = 0,
	CIRCLE = 1
};

class DrawableShapesApp : public AppNative {
public:
	void setup() override;
	void mouseDown( MouseEvent event );
	void update();
	void draw();
	
	CollisionSystem mSystem;

};

void DrawableShapesApp::setup()
{

	for( int i = 0; i < 100; i++){
		
		if( i % 2 == 0 )
			mSystem.addShape(
							 CircleRef( new Circle(
												   ColorAf( randFloat(), randFloat(), randFloat(), 1. ),
												   vec2( randFloat(getWindowWidth()), randFloat(getWindowHeight()) ),
												   randFloat(5, 15)
												   )
									   )
							 );
		else
			mSystem.addShape(
							 SquareRef( new Square(
												   ColorAf( randFloat(), randFloat(), randFloat(), 1. ),
												   vec2( randFloat(getWindowWidth()), randFloat(getWindowHeight()) ),
												   vec2(randFloat(5, 10),randFloat(5,10) )
												   )
									   )
							 );

		
	}
	
}

void DrawableShapesApp::mouseDown( MouseEvent event )
{
	mSystem.checkMouse(event.getPos());
}

void DrawableShapesApp::update()
{
	mSystem.update();
}

void DrawableShapesApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
	mSystem.draw();

}

CINDER_APP_NATIVE( DrawableShapesApp, RendererGl )
