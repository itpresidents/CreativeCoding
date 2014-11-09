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

Circle::Circle(  const ci::ColorAf &color, const Vec2f &position, float radius )
: InteractableShape( color, position, Vec2f( radius*2, radius*2 ) ), mRadius( radius )
{
}

const int Circle::mId = 0;

void Circle::update()
{
    InteractableShape::update();
	
	//circle update stuff here

}

void Circle::hit(){
	
	InteractableShape::hit();
	
	//do something here when it gets hit.
	
}


void Circle::draw()
{
    gl::color( mColor );
    gl::drawSolidCircle( mPosition, mRadius );
}

