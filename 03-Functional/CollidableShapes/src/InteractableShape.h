//
//  CollidableShape.h
//  CollidableShapes
//
//  Created by Ryan Bartley on 9/25/14.
//
//

#pragma once

#include "cinder/Rect.h"

#include "DrawableShape.h"

using InteractableShapeRef = std::shared_ptr< class InteractableShape >;

class InteractableShape : public DrawableShape {
public:
	
	InteractableShape( const ci::ColorAf &color, const ci::Vec2f &position, const ci::Vec2f &size )
	: DrawableShape( color ), mPosition( position ), mVelocity( ci::Vec2f::zero() ),mSize( size ){}
	
	virtual ~InteractableShape() {}
	
	virtual void update() {
		
		//update position
		
		mPosition += mVelocity;
	
		//check edges
		
		if( mPosition.x > ci::app::getWindowWidth() - mSize.x/2 || mPosition.x < mSize.x/2) mVelocity.x *= -1;
		if( mPosition.y > ci::app::getWindowHeight() - mSize.y/2 || mPosition.y < mSize.y/2) mVelocity.y *= -1;
	
	}
	
	virtual void hit() { mVelocity *= -1; }
	
	virtual const int& getType() const = 0;
		
	bool contains( const ci::Vec2f &position ) { return ci::Rectf( mPosition, mPosition+mSize ).contains( position ); }
	bool intersects( const ci::Rectf &boundingRect ) { return ci::Rectf( mPosition, mPosition+mSize ).intersects( boundingRect ); }
	
	const ci::Vec2f& getVelocity() { return mVelocity; }
	
	const ci::Vec2f& getPosition() { return mPosition; }
	void setPosition( const ci::Vec2f& position ){ mPosition = position; }
	
	const ci::Vec2f& getSize() { return mSize; }

	
protected:
	
	void setVelocity( const ci::Vec2f& velocity ) { mVelocity = velocity; }
	
	ci::Vec2f mPosition;
	ci::Vec2f mVelocity;
	ci::Vec2f mSize;
	
	friend class CollisionSystem;
};
