//
//  Square.h
//  Circles
//
//  Created by Mike Allison on 9/20/14.
//
//

#pragma once

#include "InteractableShape.h"

using SquareRef = std::shared_ptr<class Square>;

class Square : public InteractableShape {
public:
	
	Square( const ci::ColorAf &color, const ci::vec2 &position, const ci::vec2 &size );
    ~Square(){}
	
	static const int mId;
	
    void draw() override;
	void update() override;
	void hit() override;
	const int& getType() const { return mId; }
		
private:
};