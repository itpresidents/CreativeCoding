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

// Here's our implementation of the declared functions for square.

Square::Square( const Vec2f &position, const Vec2f &size )
// DrawableShape is inialized first.
: DrawableShape( position ), mSize( size )
{
}

// This implementation is specific to Square which DrawableShape allows
// us to create because of the pure virtual function of 'draw'.
void Square::draw()
{
    gl::color(mColor);
    gl::drawSolidRect(Rectf( mPosition, mPosition+mSize ));
    
}