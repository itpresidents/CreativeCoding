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
#include "cinder/app/App.h"

using InteractableShapeRef = std::shared_ptr< class InteractableShape >;

class InteractableShape : public DrawableShape {
public:
	
	InteractableShape( const ci::ColorAf &color, const ci::vec2 &position, const ci::vec2 &size )
	: DrawableShape( color ), mPosition( position ), mVelocity( ci::vec2( 0 ) ), mSize( size ) {}
	
	virtual ~InteractableShape() {}
	
	virtual void update() {
		
		//update position
		
		mPosition += mVelocity;
	
		//check edges
		
		if( mPosition.x > ci::app::getWindowWidth() - mSize.x/2 || mPosition.x < mSize.x/2
		   || mPosition.y > ci::app::getWindowHeight() - mSize.y/2 || mPosition.y < mSize.y/2 )
			mVelocity.y *= -1;
	}
	
	virtual void hit() { mVelocity *= -1; }
	
	virtual const int& getType() const = 0;
		
	bool contains( const ci::vec2 &position ) { return ci::Rectf( mPosition, mPosition+mSize ).contains( position ); }
	bool intersects( const ci::Rectf &boundingRect ) { return ci::Rectf( mPosition, mPosition+mSize ).intersects( boundingRect ); }
	
	const ci::vec2& getSize() { return mSize; }
	const ci::vec2& getVelocity() { return mVelocity; }
	const ci::vec2& getPosition() { return mPosition; }
	void setPosition( const ci::vec2& position ){ mPosition = position; }
	
protected:
	
	void setVelocity( const ci::vec2& velocity ) { mVelocity = velocity; }
	
	ci::vec2 mPosition;
	ci::vec2 mVelocity;
	ci::vec2 mSize;
	
	friend class CollisionSystem;
};
