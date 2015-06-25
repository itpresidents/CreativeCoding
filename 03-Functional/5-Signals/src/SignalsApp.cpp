#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SignalsApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void SignalsApp::setup()
{
}

void SignalsApp::mouseDown( MouseEvent event )
{
}

void SignalsApp::update()
{
}

void SignalsApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( SignalsApp, RendererGl )
