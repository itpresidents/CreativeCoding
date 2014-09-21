//
//  Square.h
//  Circles
//
//  Created by Mike Allison on 9/20/14.
//
//

#pragma once
#include "DrawableShape.h"



class Square : public DrawableShape {
public:
    
    Square();
    Square( float x, float y);
    ~Square(){}
    
    void draw() override;
    void update() override {}
    ci::Vec2f getSize(){ return mSize; }
    void setSize( const ci::Vec2f& size ){ mSize = size; }
    
protected:

    ci::Vec2f mSize;
    
};