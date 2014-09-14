//
//  Circle.cpp
//  CinderProject
//
//  Created by Mike Allison on 9/13/14.
//
//

#include "Circle.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include <iostream>

using namespace std;
using namespace ci;

Circle::Circle()
: mX( 0 ), mY( 0 ), mRadius( 10 ), mColor( randFloat(), randFloat(), randFloat() )
{
    cout << "I'm constructing with zero integers" << endl;
}

Circle::Circle( int x, int y )
: mX( x ), mY( y ), mRadius( 10 ), mColor( randFloat(), randFloat(), randFloat() )
{
    cout << "I'm constructing with two integers" << endl;
}

Circle::~Circle()
{
    cout << "I'm destructing myself" << endl;
}

int Circle::getX()
{
    return mX;
}

int Circle::getY()
{
    return mY;
}

int Circle::getRadius()
{
    return mRadius;
}

void Circle::draw()
{
    gl::color( mColor );
    gl::drawSolidCircle( Vec2f( mX, mY ), mRadius );
}

