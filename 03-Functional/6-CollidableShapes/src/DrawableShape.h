//
//  DrawableShape.h
//  Circles
//
//  Created by Mike Allison on 9/20/14.
//
//

#pragma once

class DrawableShape {
public:
	
	// Constructor
	DrawableShape( const ci::ColorAf &color );
    virtual ~DrawableShape(){}
	
    virtual void draw() = 0;
	
	const ci::ColorAf& getColor();
	void setColor( const ci::Colorf &color ) { mColor = color; }

protected:
    ci::ColorAf mColor;
};


