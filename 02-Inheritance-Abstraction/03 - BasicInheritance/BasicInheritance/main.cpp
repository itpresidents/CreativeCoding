//
//  main.cpp
//  BasicInheritance
//
//  Created by Ryan Bartley on 9/22/14.
//  Copyright (c) 2014 Ryan Bartley. All rights reserved.
//

#include <iostream>

// Inheritance is a key concept in Object-Oriented programming.
// Below, is a basic example of what it means to inherit.

// Let's say that I've made a class that could be used in more
// than one way. This class ('Base') has the functionality of
// not only storing a name (mName) in a string but it also allows
// us to get that name and to print that name. That seems like
// it may be useful to many different classes, which is why it
// becomes a BASE Class that can be inherited from. Inheritance
// is just like it sounds. You take some general functionality
// and extend that functionality with some other things that are
// more specific to the needs of your program. You inherit the
// base functionality in your extended functionality. That way
// you can change implementation or use the original implementation

// Here's a very basic class that stores a name that can be
// retrieved and printed. however, this base class is agnostic
// to how or where you'd like to print that name or even whether
// you'd like to print it. Therefore, it has declared the print()
// function abstract. Look below...
class Base {
public:
	
	// Constructor
	Base( const std::string& name ) : mName(name) {}
	// Getter
	const std::string& getName() { return mName; }
	
	// Virtual functions allow inheriting classes to override their functionality.
	// Look below at the way Derived can not only override the Base's setName()
	// functionality but also how you can still gain access to this functionality.
	// A virtual function with a definition is used as a default. You're allowing
	// people or yourself to do something by default but also allowing them or
	// yourself to change it if they need to.
	virtual void setName( const std::string &name ) { mName = name; }
	
	// This is what is called an pure virtual function. You are literally saying print
	// is a virtual function (meaning it can be overridden) and that we are not
	// providing a definition (as can be seen by the '= 0;', meaning that this function
	// must be overridden). This also makes 'Base' an abstract class, meaning you
	// can't construct an instance of it. Something must derive from it and fill
	// in the blanks. This is kind of an abstract idea, pun intended. It's a design
	// choice basically. Basically, when you or someone else looks at this class,
	// they'd read into it that you, as the writer of the class, could see the value
	// of a 'print' function but had no idea or reason to define default functionality
	// for the function.
	virtual void print() = 0;
	
// This is the first time we've seen 'protected:'. 'protected:' is in between
// 'public:' and 'private:' access rules. Basically, it allows classes that
// inherit from this one, like Derived below, access member variables but
// doesn't allow public access or access outside of this class or a class
// that inherits from it.
protected:
	std::string mName;
};

// This is a simple example of a class that derives from Base,
// called aptly Derived. This class adds a float variable and
// some member functions to manipulate that float.
// The first line defines that the class Derived inherits publicly
// from the class Base.
class Derived : public Base {
public:
	
	// Constructor, notice that the first member we construct in our initializer list
	// is 'Base'. That isn't an accident. When you inherit from a class you need to
	// first initialize the base class.
	Derived( const std::string& name, const float& number ) : Base(name), mNumber(number) {}
	
	// I'm choosing to override the 'setName' because I want this class to print to the console
	// everytime someone sets the name. Notice the override after the function. That is a
	// compiler flag letting the compiler know that I mean to override the function from a
	// base implementation. I first get to call the original functionality which does
	// exactly what I want but then I also get to print out the info.
	void setName( const std::string &name ) override
	{
		Base::setName( name );	// I can call the original base implementation like so
		print();				// and I can now add this functionality to the idea of
	}							// setting a name
	
	
	// Un-comment the commented decl of 'setName' to see that because the arguments are
	// different from the virtual (overridable) function the compiler will throw errors
	// That's convenient, it's like spell check!
	
	//void setName( std::string &name ) override;
	
	void someotherFunc();
	
	// Here's the implementation of print that we're contractually obligated to implement
	// because we're inheriting from 'Base'. As you can see this implementation just prints
	// some info to the console but we could just as easily print to a file on the computer,
	// or to somewhere that we as the writers of the base class wouldn't have known. Hence,
	// the pure virtual function.
	void print() override {
		std::cout<< "I'm Derived and mNumber is: " << mNumber << ", and my name is: " << mName <<std::endl;
	}

// We make Derived's members private because we don't need to inherit from
// Derived.
private:
	float mNumber;
};

// Alright enough talking let's see how they work in practice...

int main(int argc, const char * argv[]) {
	
	// I construct a derived just like any other type.
	Derived derived( "Ryan", 20.0f );
	
	// Now let's use the print command.
	derived.print();  // Prints 'I'm Derived and mNumber is: 20, and my name is: Ryan'
	
	// Great! That's exactly what we wanted.
	// Now we'll setName to see that we've overriden the function
	derived.setName( "Mike" );
	
	Base* basePtr = dynamic_cast<Base*>(&derived);
	
	basePtr->print();
	
	basePtr->setName( "TK" );

	
	// Now we can use Derived throughout our program.
	
    return 0;
}











