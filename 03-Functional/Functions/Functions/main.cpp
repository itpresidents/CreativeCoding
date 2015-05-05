//
//  main.cpp
//  Functions
//
//  Created by Ryan Bartley on 1/22/15.
//  Copyright (c) 2015 Ryan Bartley. All rights reserved.
//

#include <iostream>
// Using cout and endl from std::
using namespace std;

// This is an alias of a pointer to this type of function.
// It's really handy to write these in this way. Before C++11
// you'd have written the following line...
//
// typedef void (*PointerToRegularFunction)();
//
// I personally don't find this to be as clean, especially
// when you get argument lists that are somewhat intense.
// This alias basically tells the compiler, when you see
// PointerToRegularFunction, I really mean a ptr to a function
// whose return type is void and which accepts no arguments.
using PointerToRegularFunction = void (*)();
// This is similar to the above but it is a ptr to a function
// whose return type is void and which accepts one argument of
// type int.
using PointerToIntFunction = void (*)( int );

// It just so happens that we have some functions defined below.
// The first two are functions like PointerToRegularFunction,
// void return type and takes no parameters. The thirdFunction
// is like the PointerToIntFunction type. And the fourth function
// takes a function, specifically a PointerToIntFunction, as a
// parameter.
void firstFunction()
{
	// I'd like to point out this weird looking __FUNCTION__ thing
	// in this function. It's a compiler variable that contains the
	// name of the function in human readable form. If you were to
	// run this program, as part of the output, you'd see each of
	// the function names.
	cout << "I'm in " << __FUNCTION__ << endl;
}

// A second simple function
void secondFunction()
{
	// __FUNCTION__ used as before.
	cout << "I'm in " << __FUNCTION__ << endl;
}

// A third simple function, this time takes an integer as a parameter
void thirdFunction( int number )
{
	cout << number << " I'm in " << __FUNCTION__ << endl;
}

// A fourth more complicated function that takes a ptr to a function as
// a parameter. This entire lesson is to show that functions can be variables
// just like integers or floats. Therefore, we can pass a function, in this
// case, that takes an int to this function and call it from this function.
// The biggest thing to remember is that a pointer is an address. And functions
// just like integers and floats have an address in memory where they contain
// the code within the function. Therefore, we can query whether or not the
// function 
bool fourthFunction( PointerToIntFunction func )
{
	// as before
	cout << "I'm in " << __FUNCTION__ << endl;
	//
	if( func ) {
		func( 20 );
		return true;
	}
	else {
		cout << "No func given" << endl;
		return false;
	}
}

int main(int argc, const char * argv[]) {
	
	firstFunction();
	
	PointerToRegularFunction awkwardPtrFuncInit = &firstFunction;
	
	awkwardPtrFuncInit();
	
	auto easyPtrFunc = &firstFunction;
	
	easyPtrFunc();
	
	easyPtrFunc = &secondFunction;
	
	easyPtrFunc();
	
	easyPtrFunc = &firstFunction;
	
	// easyPtrFunc = &thirdFunction;
	
	PointerToIntFunction ptrToIntFunc = &thirdFunction;
	
	ptrToIntFunc( 10 );
	
    return 0;
}
