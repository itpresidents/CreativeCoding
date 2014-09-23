#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "DrawableShape.h"
#include "Circle.h"
#include "Square.h"


using namespace ci;
using namespace ci::app;
using namespace std;

const int NUM_SHAPES = 1000;

// If you need a refresher of what is going on here, look to the 04 - Cpp11AndTypes
// sample. We're basically just defining human readable types.
using DrawableShapeRef = std::shared_ptr< DrawableShape >;
using CircleRef = std::shared_ptr<Circle>;
using SquareRef = std::shared_ptr<Square>;
using DrawableShapes = std::vector<DrawableShapeRef>;

class DrawableShapesApp : public AppNative {
public:
	void setup() override;
	void mouseDown( MouseEvent event );
	void update();
	void draw();
	
	DrawableShapes mShapes;
};

void DrawableShapesApp::setup()
{
	
	mShapes.resize( NUM_SHAPES );
	
	int i = 0;
	for( auto & shape : mShapes ) {
		auto position = Vec2f( randFloat( 0, getWindowWidth() ), randFloat( 0, getWindowHeight() ) );
		
		if( (i = 1 - i) ) {
			auto size = Vec2f( randFloat( 5, 10 ), randFloat( 5, 10 ) );
			shape.reset( new Square( position, size ) );
		}
		else {
			auto radius = randFloat( 5, 10 );
			shape.reset( new Circle( position, radius ) );
		}
	}
}

void DrawableShapesApp::mouseDown( MouseEvent event )
{
	
}

void DrawableShapesApp::update()
{
}

void DrawableShapesApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
	
	for( auto& shape : mShapes ) {
		shape->update();
		shape->draw();
	}
}

CINDER_APP_NATIVE( DrawableShapesApp, RendererGl )
