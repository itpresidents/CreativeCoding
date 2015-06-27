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

DrawableShape::DrawableShape( const vec2 &position )
: mPosition( position ), mColor( randFloat(), randFloat(), randFloat() )
{
}

void DrawableShape::update()
{
    mPosition += randVec2();
}


vec2 DrawableShape::getPosition()
{
    return mPosition;
}


