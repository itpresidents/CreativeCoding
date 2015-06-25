//
//  DrawableShape.h
//  Circles
//
//  Created by Mike Allison on 9/20/14.
//
//

#pragma once

// Here's our Abstract Base Class. It is very similar to the implementation of
// Circle in the 1st lesson. Basically, it's a structure that has a position and
// color and it is abstract in the syntactically and conceptually. I as the
// writer created this class to represent all DrawableShapes.
class DrawableShape {
public:
	
	// Constructor
	DrawableShape( const ci::vec2 &position );
	// Virtual Destructor. Created this way because we intend to derive from
	// this base class. For a further explanation take a look at 04 - C++11AndTypes
    virtual ~DrawableShape(){}
	
	// Here's our pure virtual function that contractually obligates the classes
	// that want to inherit from a DrawableShape to implement. At this point, we
	// as the writers of the class have no interest how people implement drawing
	// to the screen, we just realize that for a DrawableShape, you have to be able
	// to draw. Therefore, classes inheriting from this must implement a draw method
	// that fulfills the purpose of putting pixels to the screen.
    virtual void draw() = 0;
	// Here's an overridable virtual function that isn't pure virtual like above.
	// I've decided by writing this function that drawable shapes should jiggle,
	// which isn't necessarily what DrawableShapes always do. Therefore, any class
	// can use this or override it.
	virtual void update();
	
	// Getter for Position.
    ci::vec2 getPosition();
	// Setter for Position.
	void setPosition( const ci::vec2& position ){ mPosition = position; }
	
	// Getter for Color.
	const ci::ColorAf& getColor();
	// Setter for Color.
	void setColor( const ci::Colorf &color ) { mColor = color; }

// 'protected:' so that our inheriting classes can use.
protected:
    ci::vec2 mPosition;
    ci::Colorf mColor;
};


