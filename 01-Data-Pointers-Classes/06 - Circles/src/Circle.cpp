//
//  Circle.cpp
//  CinderProject
//
//  Created by Mike Allison on 9/13/14.
//
//

// Here I'm including files from cinder, which will give me specific
// functionality that I need for drawing and for random number generation.
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

// I also need to include my Circle interface so that the compiler can
// link the declared functionality (in my .h) with the defined functionality,
// below.
#include "Circle.h"

// I include this file for the cout and endl functionality to log to the
// screen.
#include <iostream>

// Using namespace tells the compiler that when looking for certain
// functions to first check in whatever namespaces that i'm using.
// For instance below, you'll see the objects 'cout' and 'endl'. Those
// are within the 'std' namespace. When the compiler sees that it knows
// that you're using the 'std' version of these objects. If you comment
// out these lines, take a look at the errors you get and try to fix
// them yourself.
using namespace std;
using namespace ci;

// Here I am defining my declared default constructor. The syntax is very
// similar to calling a function in a specific namespace. What I'm telling
// the compiler, with Circle::Circle() is in the class Circle there is a function
// called Circle(). Then I can define it.
Circle::Circle()
: mX( 0 ), mY( 0 ), mRadius( 10 ),						// Here is my initializer list and this is almost
	mColor( randFloat(), randFloat(), randFloat() )		// always going to be the way you initialize member vars
{
	// I'm using console out here, Note: without 'std::', to log when something uses
	// this function. This is a great way to debug.
    cout << "I'm constructing with zero integers" << endl;
}

// Here I'm defining my Overloaded Constructor. There can be as many overloads
// as you want but they have to differ in their arguments. I can't have (int, int)
// and then make another (int, int) constructor but I could have (float, float)
// the arguments must be different enough for the compiler to make a best match.
Circle::Circle( int x, int y )
: mX( x ), mY( y ), mRadius( 10 ), mColor( randFloat(), randFloat(), randFloat() )
{
    cout << "I'm constructing with two integers" << endl;
}

// Here is the definition of Circle. Unlike constructors, destructors can't be
// overloaded. There should be one way to destroy a specific class. We'll learn
// next week though why this is and how to get around it.
Circle::~Circle()
{
    cout << "I'm destructing myself" << endl;
}

// Definition of getX which returns an int, specifically mX.
int Circle::getX()
{
    return mX;
}

// Definition of getY as above.
int Circle::getY()
{
    return mY;
}

// Definition of getRadius as above.
int Circle::getRadius()
{
    return mRadius;
}

// Definition of draw. What's great about this is that I can abstract away
// how I want to draw my circle's and we'll see next week why this is powerful.
// for now, imagine if I'm tweaking the way I'd like to present my circle, and
// I have circle instances all over my program in different places drawing.
// If I were to want to tweak my circle's drawing, I'd have to make changes
// everywhere in my code. With the simple addition of a draw method, I can just
// write mCircle.draw() in all of those places and come here to the source to
// tweak knowing that all of those instances will share this functional implementation.
void Circle::draw()
{
    gl::color( mColor );
    gl::drawSolidCircle( vec2( mX, mY ), mRadius );
}

