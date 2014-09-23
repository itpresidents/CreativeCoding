//
//  main.cpp
//  BasicInheritance
//
//  Created by Ryan Bartley on 9/22/14.
//  Copyright (c) 2014 Ryan Bartley. All rights reserved.
//

#include <iostream>

// Inheritance is a key concept in Object-Oriented programming.
// Below, is a basic example, even though there are a lot of
// words :), of what it means to inherit.

// Let's say that I've made a class that could be used in more
// than one way. This class ('Base') has the functionality of
// not only storing a name (mName) in a string but it also allows
// us to get that name and to print that name. That seems like
// it may be useful to many different classes, which is why it
// becomes a BASE Class that can be inherited from. Inheritance
// is just like it sounds. You inherit the base functionality in
// your extended functionality. That way you can change
// implementation or use the original implementation

// Here's a very basic class that stores a name that can be
// retrieved and printed. however, this base class is agnostic
// to how or where you'd like to print that name or even whether
// you'd like to print it. Therefore, it has declared the print()
// function 'pure virtual'. Look below...
class Base {
public:
	
	// Constructor
	Base( const std::string& name ) : mName(name) {}
	// Virtual Destructor
	// This is important but I won't talk about it here. Just take note of it.
	virtual ~Base() {}
	
	// Getter
	const std::string& getName() { return mName; }
	
	// Virtual functions allow inheriting classes to override their functionality.
	// Look below at the way Derived can not only override the Base's setName()
	// functionality but also how you can still gain access to Base's functionality.
	// A virtual function with a definition represents a default. You're allowing
	// people or yourself to do something by default but also allowing them or
	// yourself to change it if they need to.
	virtual void setName( const std::string &name ) { mName = name; }
	
	// The print functions is what is called an pure virtual function. You are
	// literally saying 'print' is a virtual function (meaning it can be overridden)
	// and that we are not providing a definition (as can be seen by the '= 0;',
	// meaning that this function must be overridden). This also makes 'Base' an
	// abstract class, meaning you can't construct an instance of it, directly.
	// Something must derive from it and fill in the blanks. This is kind of an
	// abstract idea, pun intended. It's a design choice basically. When you or
	// someone else decides to use this class, they'd read into it that you, as
	// the writer of the class, could see the value or need of a 'print' function
	// but had no idea or reason to define default functionality for the function.
	virtual void print() = 0;
	
// This is the first time we've seen 'protected:'. 'protected:' is in between
// 'public:' and 'private:' access rules. Basically, it allows classes that
// inherit from this one, like Derived below, access to these member variables
// or functions but doesn't allow public access or access outside of this class
// or a class that inherits from it.
protected:
	std::string mName;
};

// This is a simple example of a class that derives from Base,
// called aptly Derived. This class adds a float variable and
// some member functions to manipulate that float.
// This first line defines that the class Derived inherits publicly
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
	// base implementation. In the function, I first get to call the original functionality
	// which does exactly what I want (sets the member var mName) but then I also get to
	// print out the info.
	void setName( const std::string &name ) override
	{
		Base::setName( name );	// I can call the original base implementation like so
		print();				// and I can now add this functionality to the idea of
	}							// setting a name
	
	
	// Un-comment the commented declaration of 'setName' to see that because the arguments are
	// different from the virtual (or overridden) function the compiler will throw errors
	// That's convenient, it's like spell check!
	
	//void setName( std::string &name ) override;
	
	// This is just a function that I'm adding to drive home the point that derived has other
	// functionality that Base would never know about.
	void someotherFunc() { std::cout << "I'm in someOtherFunc" << std::endl; }
	
	// Here's the implementation of print that we're contractually obligated to implement
	// because we're inheriting from 'Base'. As you can see this implementation just prints
	// some info to the console but we could just as easily print to a file on the computer,
	// or to somewhere that we as the writers of the base class wouldn't have known. Hence,
	// the pure virtual function.
	void print() override
	{
		std::cout<< "I'm Derived and mNumber is: "
				<< mNumber << ", and my name is: " << mName <<std::endl;
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
	
	// Great! That's exactly what we wanted. Now we'll setName to see that we've
	// overriden the function.
	derived.setName( "Mike" );	// Remember that this will setName first with the base
								// implementation of setName and then it will use the
								// print function.
	
	// Now I'm going to show something that I'll get deeper into in the next lesson.
	// This is a C++11 cast. It is different from the C-Style casts, clearly. It is
	// more verbose, which isn't a problem as we'll find in the next chapter. Basically,
	// the code inside of the function is a c-style cast but there are more protections
	// with this, that we won't get into right now.
	Base* basePtr = static_cast<Base*>(&derived);
	
	// What I wanted to show you is that you can use 'basePtr' to call any of the
	// functions that Base has declared, including the 'print' function. This is
	// because the compiler knows that if this is a Base* that points to an
	// instantiated object. It can guarantee that the object has a valid implementation
	// of print. Otherwise, it would've thrown a compile-time error that we were trying to
	// make an instance of an abstract class (a class with a pure virtual function).
	basePtr->print(); // Prints 'I'm Derived and mNumber is: 20, and my name is: Ryan'
	
	basePtr->setName( "TK" );	// This also works the way we expect, because we've overriden
								// the function and it still has the expected memory layout.
	
	// But obviously if we tried to call a function declared by Derived, we'll get an error.
	// Memory Layout. Memory Layout. Memory Layout. That is all the compiler know's. When
	// you cast to another type the compiler sees the memory layout of that type only.
	// So, 'basePtr' wouldn't know anything about 'someotherFunc'.
	
	// basePtr->someotherFunc();
	
	// If we can go one way, we can go the other...sometimes. To cast from a base
	// class to a derived class we use 'dynamic_cast'. 'dynamic_cast' will check
	// whether or not 'Derived' is-a 'Base', if not it will return nullptr, which
	// is super great because nullptr will evaluate to false. Convenient for
	// conditionals like the one below.
	
	// This is basically saying, if 'basePtr' casts to a Derived* then continue
	// execution of the block.
	if( Derived* derivedPtr = dynamic_cast<Derived*>(basePtr) ) {
		derivedPtr->someotherFunc();
		std::cout << "basePtr was able to be cast" << std::endl;
	}
	// otherwise do something else.
	else {
		std::cout << "basePtr couldn't be cast" << std::endl;
	}
	
	// In a collection, this is so powerful because you can test cast objects and if
	// they're a type then you can do something with that type. We'll see more of this
	// next.
	
    return 0;
}











