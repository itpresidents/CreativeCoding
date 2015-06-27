//
//  Circle.h
//  CinderProject
//
//  Created by Mike Allison on 9/13/14.
//
//

#pragma once

// Syntax to declare a class. If you start typing class,
// it will usually auto complete the entire declaration
class Circle {
// Public signifies that everything under will be available
// to use outside of the class. Normally what is made public
// is the interface you want people or even yourself to
// be able to use.
public:
	
	// Constructor's and destructors are named as the class
    Circle(); // Default Constructor, takes no arguments
    Circle( int x, int y ); // Constructor Overload, takes 2 arguments
    ~Circle(); // Destructor, takes no arguments and can't be overloaded
	
	// This will now draw the circle in any way we desire to define it.
    void draw();
	
	// These are the getters that allow classes outside of this one
	// to have access to the private member variables contained in
	// the class. Note there is one for each of the member variables
	// but there doesn't have to be.
    int getX();
    int getY();
    int getRadius();
	// This one has a weird return value. Basically if I were to
	// return ci::ColorAf, at runtime every time I wanted to
	// call this function it would have to construct a whole
	// new ci::ColorAf, this is called Pass-by-Value, because this
	// is a larger class than an int like above, I'd rather pass
	// a reference for efficiency sake, which is like a pointer,
	// see References and Pointers example, and to make sure it
	// is safe like Pass-by-Value. I'll make what it is refering
	// to const. This way I pass only what I need to pass which
	// is the underlying memory.
	const ci::ColorAf& getColor();
	
	// These are the setters which allow me to change the underlying
	// values of my member functions.
	void setX( int x ) { mX = x; }
	void setY( int y ) { mY = y; }
	void setRadius( int radius ) { mRadius = radius; }
	// This just like the one above is going to be passing by
	// const reference because like the one above I don't want
	// to construct a ci::Colorf to pass to mColor. I just
	// want to have a reference to it.
	void setColor( const ci::Colorf &color ) { mColor = color; }

// Private signifies that everything under will not be
// available outside of the class. Normally what is private
// are the member variables that should only be accessible
// through your public interface. For instance, getters and
// setters.
private:
	// It is a convention to name member variable with a preceding
	// m. Some people name it m_someVar. Some people name it mSomeVar
	// You can do as you see fit.
    int mX, mY;
    int mRadius;
    ci::Colorf mColor;
};
