#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "Circle.h"

// I include random functionality here. See Circle.cpp as well.
// Even though I include it here, since I'm only including it
// in Circle.cpp, this file can't see it because I haven't included
// it. So I include files, everywhere that I'd like to see them.
#include "cinder/Rand.h"

// See Circle.cpp for an explanation of why we'd like to be using
// namespaces.
using namespace ci;
using namespace ci::app;
using namespace std;

// As we spoke about before, I use const and uppercase to illicit
// the fact that if this number changes, it should be changed here
// at the source.
const int NUM_CIRCLES = 1000;

class CirclesApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	
	// This is a vector of shared_ptrs of type Circle. Using templates
	// allows us to create complex meanings for types. We'll talk about
	// this more next week.
    std::vector<std::shared_ptr<Circle>> mCircles;
};

void CirclesApp::setup()
{
    // I resize mCircles because I know how many I'd like to have. This
	// makes it so that mCircles only goes to the operating system at most
	// twice to allocate enough memory for the amount of circle shared_ptr's
	// that I'm going to need. The use of a const here also makes it easy
	// to read and easy to change if I want more. I just change it at
	// the initialization point and it changes that number throughout the
	// file.
    mCircles.resize( NUM_CIRCLES );
	
	// Vectors again act like arrays so I can iterate through the vector and
	// initialize all of my Circle shared pointers.
    for( int i = 0; i < NUM_CIRCLES; ++i ) {
		// reset is a member function of shared_ptr that takes as an argument a
		// raw pointer and replaces whatever was stored in the shared_ptr before.
		// in this case the shared_ptr's were containing a nullptr so it doesn't
		// do anything other than store the raw Circle pointer we receive from
		// the new operator. Look to mouseDown for further explanation.
        mCircles[i].reset( new Circle( randFloat( 0, getWindowWidth() ), randFloat( 0, getWindowHeight() ) ) );
		
		// This would be similar to the above. It just constructs a shared_ptr
		// and passes it through the assignment operator
		
		// mCircles[i] = std::shared_ptr<Circle>( new Circle( randFloat( 0, getWindowWidth() ), randFloat( 0, getWindowHeight() ) ) );
    }
    
}

void CirclesApp::mouseDown( MouseEvent event )
{
	for( int i = 0; i < NUM_CIRCLES; ++i ) {
		// This time we use reset it will destroy the past raw pointer using the
		// delete operator. The reason is that when we constructed the shared_ptr's
		// above, we only had one shared_ptr pointing to any one of them. Now,
		// when reset recieves the raw pointer from new, it will check to see that
		// it has a raw pointer already as a member variable, it will the decrement
		// it's counter and find that it's counter is 0 at which point it will call
		// delete on the raw pointer it already holds. Then it will take the raw
		// pointer it was passed as an argument and store that address in it's member
		// variable.
		mCircles[i].reset( new Circle( randFloat( 0, getWindowWidth() ), randFloat( 0, getWindowHeight() ) ) );
		
		// This would be similar to the above. It just constructs a shared_ptr
		// and passes it through the assignment operator doing the same check
		// that reset will do.
		
		// mCircles[i] = std::shared_ptr<Circle>( new Circle( randFloat( 0, getWindowWidth() ), randFloat( 0, getWindowHeight() ) ) );
	}
}

void CirclesApp::update()
{
}

void CirclesApp::draw()
{
    // clear out the window with black
    gl::clear( Color( 0, 0, 0 ) );
	
	// Because we made the draw function inside of the circle class, drawing each
	// circle becomes as easy as just calling draw. Whenever we want to change how
	// we draw, we simply change the draw method inside the class and this will
	// reflect our changes.
    for( int i = 0; i < NUM_CIRCLES; ++i ) {
		// Instead of dot notation we use (->) pointer notation to get at the members
		// of our instance.
        mCircles[i]->draw();
		
		// You can see what member functions shared_ptr has by uncommenting this line
		// and putting a period (.) after the name and waiting for xcode to decide
		// when it would like to start auto completeing :)
		
		// mCircles[i].
    }
    
    
    
    
}

CINDER_APP_NATIVE( CirclesApp, RendererGl )
