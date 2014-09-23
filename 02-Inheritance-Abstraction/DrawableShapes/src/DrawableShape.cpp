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

DrawableShape::DrawableShape( const Vec2f &position )
: mPosition( position ), mColor( randFloat(), randFloat(), randFloat() )
{
}

void DrawableShape::update()
{
    mPosition += randVec2f();
}


Vec2f DrawableShape::getPosition()
{
    return mPosition;
}


