//
//  main.cpp
//  05 - PointersAndReferences
//
//  Created by Ryan Bartley on 9/15/14.
//  Copyright (c) 2014 Ryan Bartley. All rights reserved.
//

#include <iostream>

using namespace std;

// This example comes from the article - Distinguish between
// pointers and references in C++, go here for a one page
// explanation http://www.cplusplus.com/articles/ENywvCM9/

// Declarations of two different functions taking two different
// types. For the definitions look below...
void changeInt( int * myFuncIntPtr );
void changeInt( int & myFuncIntRef );


int main(int argc, const char * argv[]) {
	
	// Pointers and References are very similar but have enough
	// differences as to make them very different as well. Below
	// we'll try to go over a few of their differences and similarities.
	
	int myInt = 10;
	
	int * myIntPtr = &myInt;
	
	// First some syntax. To create a reference, you use the (&). Using
	// the & here is different than using the address-of operator. The
	// way you can tell is that the address-of operator is always used
	// on the right side of an assignment and the reference type is always
	// used on the left hand side of the assignment.
	int & myIntReference = myInt;
	// Now both myIntPtr and myIntReference point to the same object in memory
	
	cout << "Address-of myInt: " << &myInt << " Value of myInt: " << myInt << endl;
	cout << "Address-of myInt stored in myIntPtr: " << myIntPtr << " Value of what myIntPtr is pointing to: " << *myIntPtr << endl;
	cout << "Address-of myIntReference: " << &myIntReference << " Value of myIntReference: " << myIntReference << endl;
	// As you should be able to see other than the initialization of a reference
	// you are able to use a reference just like you were using the actual object
	// that you were refering to. Notice when I put an & in front of my reference
	// it gives the same value as myInt, and when I want the value of what it is
	// refering to I use it the same as using myInt. myIntPtr, stores an address
	// and has to be de-referenced to get at the value. myIntReference, stores
	// a reference to myInt and can be used just like you were using myInt.
	
	
	// Pointers can be null and reassigned. This is a major difference between
	// pointers and references.
	myIntPtr = nullptr;
	
	// References cannot be null, below is something that should absolutely
	// positively never happen...
	
	// int & myIntPtrReference = *myIntPtr;
	
	// What I'm saying here is that myIntReference should refer to the
	// dereferenced int that myIntPtr points to, which is nothing (nullptr). If you
	// tried to use myIntReference in any way after this, your computer
	// would explode. Also, as you can see we can change what a pointer
	// points to. We cannot change what a reference points to. The below line
	// will simply reassign the value of the object myIntReference is pointing
	// to, which is myInt and the value is 10. This will try and assign nullptr
	// to an int which will also explode your computer. Uncomment the to lines
	// to see the run-tme errors they will cause.
	
	// myIntReference = *myIntPtr;
	
	// To show more fully that you can't change what a reference points to uncomment
	// this line.
	
	// int & myNextReference;
	
	// A reference has to be initialized with something.
	
	// Now we'll pass myInt around to some different functions using pointers
	// and references...
	
	// First we'll pass our myIntPtr, which is null to changeInt to see what happens
	changeInt( myIntPtr );
	
	// Now we'll see that myInt hasn't changed.
	cout << "After passing a nullptr to the function, Value of myInt: " << myInt << endl;

	// Now we'll assign myIntPtr to store the address of myInt again. And send it
	// back into the function.
	myIntPtr = &myInt;
	
	changeInt( myIntPtr );
	
	// Now we can see that the value of myInt has changed.
	cout << "After Pointer Overloaded function, Value of myInt: " << myInt << endl;
	
	// Now we'll use the reference...
	changeInt( myIntReference );
	
	// It's important to realize here that the compiler will pick the best matching
	// function overload. In the above two function overloads one takes a pointer and
	// the other takes a reference. The compiler will match the argument to the
	// version that best matches. Reference for reference and pointer for pointer.
	cout << "After Reference Overloaded function, Value of myInt: " << myInt << endl;
	
	// I can also pass myInt's address to the function and it will pick the pointer
	// version of the function...
	changeInt( &myInt );
	
	cout << "After passing myInt's address, Value of myInt: " << myInt << endl;
	
	// In a similar way if I just pass myInt to the function, the compiler will choose
	// the reference version of the function.
	changeInt( myInt );
	
	cout << "After passing myInt as a reference, Value of myInt: " << myInt << endl;
	
    return 0;
}

void changeInt( int * myFuncIntPtr )
{
	// We need to check myFuncIntPtr because pointers can be null and they can
	// be reassigned. So if it is null it would be 0x0 which in this condition
	// would be false. Therefore we don't want to do anything to it. Otherwise
	// change the value.
	if (myFuncIntPtr) {
		// First we dereference the value with (*) operator and then we assign
		// the value. Which will assign the value to myInt outside the function
		// This shows a really powerful technique. We don't have to calculate
		// and return something, we can just take the pointer from an object
		// and assign it as though that object were inside this function.
		*myFuncIntPtr = 20;
	}
	else {
		cout << "This is a null pointer" << endl;
	}
}

void changeInt( int & myFuncIntRef )
{
	// Here we don't need to check if the ref is initialized because it has to
	// be initialized, unless you poorly initialize it to a nullptr like above
	// but you'll immediately be able to tell if you did that because your
	// computer will explode. This also works the same way that the pointer version
	// does, it will also change the value of myInt as though myInt was a
	// part of this function.
	myFuncIntRef = 15;
}
