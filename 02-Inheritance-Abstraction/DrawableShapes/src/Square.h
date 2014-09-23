//
//  Square.h
//  Circles
//
//  Created by Mike Allison on 9/20/14.
//
//

#pragma once

#include "DrawableShape.h"

// An example of an inherited class. Square, does what it needs to
// to create an instance. It implements the pure virtual 'draw' and
// also removes the jiggle implementation by creating a blank update
// function.

class Square : public DrawableShape {
public:
	
	// Constructor
	Square( const ci::Vec2f &position, const ci::Vec2f &size );
	// Destructor which will append itself to the destruction process
	// of square.
    ~Square(){}
	
	// Implementation of the pure virtual 'draw'. Notice the override.
    void draw() override;
	// Override of 'update'.
    void update() override { }
	
	// Getter for the 'Square'-specific data member.
    ci::Vec2f getSize(){ return mSize; }
	// Setter for the 'Square'-specific data member.
    void setSize( const ci::Vec2f& size ){ mSize = size; }
	
// 'private:' because you don't need to allow access
private:
    ci::Vec2f mSize;
};