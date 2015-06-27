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

// Here's our implementation of the declared functions for circle.

Circle::Circle( const vec2 &position, float radius )
// DrawableShape is inialized first.
: DrawableShape( position ), mRadius( radius )
{
}

// Here's our update implementation that calls the base class
// implementation (jiggle) before testing whether it's been
// hit.
void Circle::update()
{
    DrawableShape::update();
    if ( isHit() ) {
        // do something 
    }
}

// Pretend that 'Circle' can collide with things and so we need
// this function to tell us if we've hit. Right now it just is
// default to true.
bool Circle::isHit()
{
    return true;
}

// This implementation is specific to Circle which DrawableShape allows
// us to create because of the pure virtual function of 'draw'.
void Circle::draw()
{
    gl::color( mColor );
    gl::drawSolidCircle( mPosition, mRadius );
}

