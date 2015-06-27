//
//  Circle.h
//  CinderProject
//
//  Created by Mike Allison on 9/13/14.
//
//

#pragma once

#include "InteractableShape.h"

using CircleRef = std::shared_ptr<class Circle>;

class Circle : public InteractableShape {
public:
	Circle( const ci::ColorAf &color, const ci::vec2 &position, float radius );
	~Circle() {}
	
	static const int mId;
	
    void draw() override;
    void update() override;
	void hit() override;
	const int& getType() const { return mId; }

    float getRadius(){ return mRadius; }
    void  setRadius( float rad ){ mRadius = rad; }

private:
    float mRadius;
};
