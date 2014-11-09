//
//  Square.cpp
//  Circles
//
//  Created by Mike Allison on 9/20/14.
//
//

#include "Square.h"

using namespace ci;
using namespace ci::app;


Square::Square( const ci::ColorAf &color, const Vec2f &position, const Vec2f &size )
: InteractableShape( color, position, size )
{
}

const int Square::mId = 0;

void Square::update(){
	
	InteractableShape::update();
	
	//square update stuff here
	
}

void Square::draw()
{
    gl::color(mColor);
    gl::drawSolidRect(Rectf( mPosition, mPosition+mSize ));
    
}

void Square::hit(){
	
	InteractableShape::hit();
	
	//do something here when it gets hit
	
}