//
//  main.cpp
//  C-StyleCasting
//
//  Created by Mike Allison on 9/20/14.
//  Copyright (c) 2014 Mike Allison. All rights reserved.
//

#include <iostream>

// Simple class that holds and returns a float. Note also,
// the 'public:'. If it weren't there you wouldn't be able
// to access the member functions.
class Object {
public:
	
	// Constructor for this object
    Object( const float& initial_value )
	: mFloat( initial_value )				// initializer list
	{}
	// Destructor for this object
	~Object() { std::cout << "I am being destroyed" << std::endl; }
	
	// Getter and Setter to allow access to the private member data
    float getValue() { return mFloat; }
    void setFloat( const float& new_val ) { mFloat = new_val; }
    
private:
	// Simple float
	float mFloat;
};


int main(int argc, const char * argv[])
{

    // I'm creating an instance of object with a value of 20.
    Object obj( 20.0f );
    
    // Just to make sure everything is as I expect.
    std::cout << "Object's float value: " << obj.getValue() << std::endl;	// Prints 'Object's float value: 20'
	std::cout << "Object's size: " << sizeof( obj ) << std::endl;			// Prints 'Object's size: 4'
	
	std::cout << std::endl;
    
    // In C and C++, you can cast any object to any other object
	// using the syntax...
	//
	// _type_ new_variable_casted = ( _type_ ) original_variable;
	//
	// You've probably seen this style of cast in Processing (Java).
	// Basically, you're saying take 'original_variable' and change
	// the memory layout to '_type_'s memory layout. That's weird I
	// know but you can do some pretty insane stuff casting from pointers
	// of a specific type to pointers of another type.
	
	// Here we're casting objects address to a 'void *' which is just
	// a pointer of void (nothing) type.
    void* ptr = (void*) &obj;
    
    // When we print out the address of obj and ptr, you can see that
	// ptr is just storing the address of obj, which is what pointers
	// do.
	std::cout << "obj's address: " << &obj << std::endl;
    std::cout << "ptr's address: " << ptr << std::endl;
	
	std::cout << std::endl;
	
	// However, if we try and use ptr, we'll get an error because we
	// told the compiler that ptr doesn't point to a specific type (void).
	// Therefore, the compiler sees ptr as not having a memory layout.
	// Un-comment the code to see the error.
	
	// ptr->getValue();
    
    // However, if we can go one way, why not go the other way. We'll take
	// ptr and C-style cast it to an Object*. Then we have a new Object pointer
	// that is pointing to exactly the same memory address ocupied by our original
	// Object.
    Object* objPtr = (Object*)ptr;
	
	// And now that the compiler knows the memory layout of objPtr, it
    // can access the objPtr's getValue member function.
    std::cout << "objPtr's value: " << objPtr->getValue() << std::endl;
	
	std::cout << std::endl;
	
	// Here's something really insane. Because Object only holds a float,
	// I can cast object's address to a float pointer. NUTS.... This is
	// absolutely dangerous and you shouldn't do it normally, but I want
	// to drive home the fact that pointers are just addresses to memory
	// of a specific type and that the way the compiler looks at memory is
	// standardized. Basically, the instance of 'Object' ('obj' in this
	// case) has a memory layout that we've defined above. That memory
	// layout is just one float, basically just the 4 byte float member
	// variable 'mFloat'. Because the address of an instance begins at the
	// first member variable and because that member is a float in this
	// case, I can get to that float by casting 'obj's address to a float pointer.
	
	float* floatPtr = (float*) &obj;
	
	// This is conceptually nuts, but it brings up a good point and definitely
	// read the above again to understand. If you don't believe me and think
	// it's just black magic that the console printed out 20, change the float
	// that you're constructing 'obj' with to be a different value and run it
	// again.
	std::cout << "Object's value: " << obj.getValue() << std::endl; // Prints 'Object's value: 20'
	std::cout << "floatPtr's value: " << *floatPtr << std::endl;	// Prints 'floatPtr's value: 20'
	
    // That's crazy I know but that's what casting allows. You might not see
	// the reasoning for this now but you definitely will soon.
    
    return 0;
}

