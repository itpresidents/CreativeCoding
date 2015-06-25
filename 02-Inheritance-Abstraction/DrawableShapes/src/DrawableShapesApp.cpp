#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "DrawableShape.h"
#include "Circle.h"
#include "Square.h"

using namespace ci;
using namespace ci::app;
using namespace std;

// I know how many shapes I'd like to make. So, instead of magic numbers all over my
// code. I'll make a global const int and by convention, I'll capitalize all the letters
// to emphasize that it's constant.
const int NUM_SHAPES = 1000;

// If you need a refresher of what is going on here, look to the 04 - Cpp11AndTypes
// sample. We're basically just defining human readable types.
using DrawableShapeRef = std::shared_ptr< DrawableShape >;
using CircleRef = std::shared_ptr<Circle>;
using SquareRef = std::shared_ptr<Square>;
using DrawableShapes = std::vector<DrawableShapeRef>;

class DrawableShapesApp : public App {
public:
	void setup() override;
	void mouseDown( MouseEvent event );
	void update();
	void draw();
	
	// My human readable type, which is defined above as...
	// std::vector<std::shared_ptr<DrawableShape>>
	DrawableShapes mShapes;
};

void DrawableShapesApp::setup()
{
	// I know how many shapes I'd like so I'll resize the vector to that exact number.
	mShapes.resize( NUM_SHAPES );
	
	
	bool square = false;
	// Now I just for each mShapes, which constructed nullptr'd shared_ptr's of type
	// DrawableShapes, inside the loop I initialize each one.
	for( auto & shape : mShapes ) {
		// both need a position. Remember because the type on the right is already
		// figured out, 'auto' is here to tell the compiler to infer it. therefore
		// position is of type vec2.
		auto position = vec2( randFloat( 0, getWindowWidth() ), randFloat( 0, getWindowHeight() ) );
		
		// I use this construct to create half as circle's and half as squares.
		if( square ) {
			// same use of auto here as above.
			auto size = vec2( randFloat( 5, 10 ), randFloat( 5, 10 ) );
			// we use the 'reset' function of shape which destroys the inner member
			// pointer if it exists. One doesn't exist as the above comment tells
			// us that resize just creates NUM_SHAPES instances of empty shared_ptr's
			// Then reset takes the pointer returned by new and stores that pointer
			// inside this shape.
			shape.reset( new Square( position, size ) );
		}
		else {
			// same use of auto as above. randFloat returns a float so radius is
			// inferred to float.
			auto radius = randFloat( 5, 10 );
			shape.reset( new Circle( position, radius ) );
		}
		// swap to create a square or circle.
		square = !square;
	}
}

void DrawableShapesApp::mouseDown( MouseEvent event )
{
	
}

void DrawableShapesApp::update()
{
	// Just iterate through mShapes and update. it uses either the default or the
	// overriden implementation.
	for( auto& shape : mShapes ) {
		shape->update();
	}
}

void DrawableShapesApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
	
	// As above, we just iterate through mShapes and use the draw function of the
	// current shape's (which could be either Circle's or Square's) implementation
	for( auto& shape : mShapes ) {
		shape->draw();
	}
}

CINDER_APP( DrawableShapesApp, RendererGl )
