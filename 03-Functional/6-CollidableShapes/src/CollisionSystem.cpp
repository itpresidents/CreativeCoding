//
//  CollisionSystem.cpp
//  CollidableShapes
//
//  Created by Ryan Bartley on 9/25/14.
//
//

#include "CollisionSystem.h"
#include "Circle.h"
#include "Square.h"
#include "cinder/Rand.h"
#include "cinder/Log.h"

using namespace ci;
using namespace ci::app;

void CollisionSystem::update(){
	
	for(auto & shape : mShapes ){
		
		for(auto & other_shape : mShapes ){

			if( shape != other_shape && shape->intersects( Rectf( other_shape->getPosition(), other_shape->getPosition() + other_shape->getSize() )) ){
			
				
				shape->hit();
				
				switch (shape->getType()) {
						
					case 0: {
						if( mCallbacks.count(Square::mId) > 0 )
							mCallbacks[Square::mId]();
					}
					break;
					case 1: {
						if( mCallbacks.count(Circle::mId) > 0 )
							mCallbacks[Circle::mId]();
					}
					break;
					default: {
						CI_LOG_E("CollisionSystem::Update couldn't find a callback for this type.");
					}
					break;
				}
			}
			
		}
		
		shape->update();
	}

}

void CollisionSystem::checkMouse(const ci::vec2 &mousePos){
	
	for( auto & shape : mShapes ){
		if( shape->contains(mousePos) ){
			shape->hit();
		}
	}
	
}


void CollisionSystem::draw(){
	
	
	for(auto & shape : mShapes )shape->draw();
	
}


void CollisionSystem::addShape( const InteractableShapeRef& shape ){
	shape->setVelocity( randVec2f() * randFloat( 1, 3 ) );
	mShapes.push_back(shape);
}
void CollisionSystem::addCallback( int type, const Callback& callback ){ mCallbacks.insert(std::make_pair(type,callback)); }
