//
//  Circle.cpp
//  CinderProject
//
//  Created by Mike Allison on 9/13/14.
//
//


#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "Circle.h"

#include <iostream>


using namespace std;
using namespace ci;


Circle::Circle()
: mRadius( 10 )
{
	
    cout << "I'm constructing with zero integers" << endl;
}


Circle::Circle( int x, int y )
: DrawableShape(x,y), mRadius( 10 )
{
    cout << "I'm constructing with two integers" << endl;
}

Circle::~Circle()
{
    cout << "I'm destructing myself" << endl;
}

void Circle::update()
{
    DrawableShape::update();
    if ( isHit() ) {
        // do something 
    }
}

bool Circle::isHit()
{
    return true;
}

void Circle::draw()
{
    gl::color( mColor );
    gl::drawSolidCircle( mPosition, mRadius );
}

