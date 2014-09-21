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
    DrawableShape();
    DrawableShape( int x, int y );
    virtual ~DrawableShape(){}
    
    virtual void draw() = 0; //pure virtual function
	
    ci::Vec2f getPosition();
    
	const ci::ColorAf& getColor();
	
	void setPosition( const ci::Vec2f& position ){ mPosition = position; }
    
	void setColor( const ci::Colorf &color ) { mColor = color; }
    
    virtual void update();

protected:
    
    ci::Vec2f mPosition;
    ci::Colorf mColor;

};


