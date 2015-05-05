//
//  CollisionSystem.h
//  CollidableShapes
//
//  Created by Ryan Bartley on 9/25/14.
//
//

#pragma once

#include "InteractableShape.h"

using Callback = std::function<void()>;

class CollisionSystem {
public:
	
	CollisionSystem(){}
	~CollisionSystem(){}
	
	void update();
	void draw();
	
	void addShape( const InteractableShapeRef& shape );
	void addCallback( int type, const Callback& callback );
	
	void checkMouse( const ci::vec2& mousePos );
	
private:
	std::vector<InteractableShapeRef> mShapes;
	std::map<int, Callback> mCallbacks;
};