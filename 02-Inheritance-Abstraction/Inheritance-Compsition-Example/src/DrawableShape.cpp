//
//  DrawableShape.cpp
//  DrawableShapes
//
//  Created by Mike Allison on 9/20/14.
//
//

#include "DrawableShape.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include <iostream>


using namespace std;
using namespace ci;


DrawableShape::DrawableShape()
: mPosition( Vec2f::zero() ),
mColor( randFloat(), randFloat(), randFloat() )
{
	
    cout << "I'm constructing with zero integers" << endl;
}


DrawableShape::DrawableShape( int x, int y )
: mPosition(Vec2f( x, y)), mColor( randFloat(), randFloat(), randFloat() )
{
    cout << "I'm constructing with two integers" << endl;
}

void DrawableShape::update()
{
    mPosition += randVec2f();
}


Vec2f DrawableShape::getPosition()
{
    return mPosition;
}


