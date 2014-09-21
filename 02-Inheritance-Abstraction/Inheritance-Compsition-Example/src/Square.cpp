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

Square::Square()
: mSize(Vec2f::zero())
{
}

Square::Square(float x, float y)
: DrawableShape( x, y ), mSize(Vec2f( 10,10 ))
{
}

void Square::draw()
{
    gl::color(mColor);
    gl::drawSolidRect(Rectf( mPosition, mPosition+mSize ));
    
}