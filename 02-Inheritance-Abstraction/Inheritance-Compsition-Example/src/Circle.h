//
//  Circle.h
//  CinderProject
//
//  Created by Mike Allison on 9/13/14.
//
//

#pragma once
#include "DrawableShape.h"

class Circle : public DrawableShape {

public:
	
    Circle();
    Circle( int x, int y );
    ~Circle();
    
    void draw() override;
    void update() override;
    bool isHit();
	
    float getRadius(){ return mRadius; }
    void  setRadius( float rad ){ mRadius = rad; }
    
private:
    
    float mRadius;

};
