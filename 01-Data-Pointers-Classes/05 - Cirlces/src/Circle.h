//
//  Circle.h
//  CinderProject
//
//  Created by Mike Allison on 9/13/14.
//
//

#pragma once

class Circle {
public:
    
    Circle();
    Circle( int x, int y );
    ~Circle();
    
    void draw();
    
    int getX();
    int getY();
    int getRadius();
    
private:
    int mX, mY;
    int mRadius;
    ci::Colorf mColor;
};
