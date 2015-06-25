//
//  Circle.h
//  CinderProject
//
//  Created by Mike Allison on 9/13/14.
//
//

#pragma once
#include "DrawableShape.h"

// An example of an inherited class. Circle, does what it needs to
// to create an instance. It implements the pure virtual 'draw' and
// also removes the jiggle implementation by creating a blank update
// function. Remember that you can call the base classes implementation
// of a virtual function if a default implementation exists.

class Circle : public DrawableShape {
public:
	// Constructor
	Circle( const ci::vec2 &position, float radius );
	// Destructor which will append itself to the destruction process
	// of circle.
	~Circle() {}
	
	// Implementation of the pure virtual 'draw'. Notice the override.
    void draw() override;
	// Override of 'update'.
    void update() override;
	
	// Another function that could be and is used in the update override.
    bool isHit();
	
	// Getter for the 'Circle'-specific data member.
    float getRadius(){ return mRadius; }
	// Setter for the 'Circle'-specific data member.
    void  setRadius( float rad ){ mRadius = rad; }

// 'private:' because you don't need to allow access
private:
    float mRadius;
};
