//
//  main.cpp
//  1-Functions
//
//  Created by Ryan Bartley on 1/22/15.
//  Copyright (c) 2015 Ryan Bartley. All rights reserved.
//

#include <iostream>
// Using cout and endl from std::
using namespace std;

// The line below is an alias of a pointer to this type of
// function. It's really handy to write these in this way.
// Before C++11 you'd have written the following line...
//
// typedef void (*PointerToRegularFunction)();
//
// I personally don't find this to be as clean as below,
// especially when you get argument lists that are somewhat
// intense. This alias basically tells the compiler, when you
// see PointerToRegularFunction, I really mean a ptr to a
// function whose return type is void and which accepts no
// arguments.
using PointerToRegularFunction = void (*)();

// This is similar to the above but it is a ptr to a function
// whose return type is void and which accepts one argument of
// type int.
using PointerToIntFunction = void (*)( int );

// It just so happens that we have some functions defined below.
// The first two are functions like PointerToRegularFunction,
// void return type and takes no parameters. The function3
// is like the PointerToIntFunction type. And the fourth function
// takes a function, specifically a PointerToIntFunction, as a
// parameter.
void function1()
{
	// I'd like to point out this weird looking __FUNCTION__ thing
	// in this function. It's a compiler variable that contains the
	// name of the function in human readable form. If you were to
	// run this program, as part of the output, you'd see each of
	// the function names.
	cout << "I'm in " << __FUNCTION__ << endl;
}

// A second simple function
void function2()
{
	// __FUNCTION__ used as before.
	cout << "I'm in " << __FUNCTION__ << endl;
}

// A third simple function, this time takes an integer as a parameter
void function3( int number )
{
	cout << "I'm in " << __FUNCTION__ << " and the number is " << number << endl;
}

// A fourth more complicated function that takes a ptr to a function as
// a parameter. This entire lesson is to show that functions can be variables
// just like integers or floats. Therefore, we can pass a function, in this
// case, that takes an int to this function and call it from this function.
// The biggest thing to remember is that a pointer is an address. And functions
// just like integers and floats have an address in memory where they contain
// the code within the function. Therefore, we can query whether or not we're
// pointing to anything or if it's null. More below.
bool function4( PointerToIntFunction func )
{
	// as before
	cout << "I'm in " << __FUNCTION__ << endl;
	// Being that func is a pointer we can test whether it's null just like
	// any regular pointer
	if( func ) {
		func( 20 );
		return true;
	}
	// If not we can do something else.
	else {
		cout << "No func given" << endl;
		return false;
	}
}

int main(int argc, const char * argv[]) {
	
	// Let's start by calling the function1 just like always
	function1();
	
	// Next we'll take the address of that function1 just like
	// we'd do an int or float.
	PointerToRegularFunction awkwardFuncPtr = &function1;
	
	// Now we'll call that function pointer.
	awkwardFuncPtr();
	
	// The reason I named that awkward is because having to write
	// that long alias to the left makes no sense. In C++11, we
	// should be using auto as much as possible.
	auto easyPtrFunc = &function1;
	
	// Works as before
	easyPtrFunc();
	
	// Now since the variable easyPtrFunc is a pointer, we can reassign
	// it easily.
	easyPtrFunc = &function2;
	
	// Now the variable is the same but it's pointing to a different
	// function and so therefore it will have a diffeerent output.
	easyPtrFunc();
	
	// And we can reassign it again.
	easyPtrFunc = &function1;
	
	// And call it again.
	easyPtrFunc();
	
	// This blew my mind when I started. The implications are pretty
	// amazing. You can now use functions in much the same way as any
	// other variable. Think of a counter, if something happens it ticks
	// up or down. If the counter were instead a function ptr, it could
	// do much more than tick. It could call different parts of your
	// program.
	
	// Anyway, everything's working well. However, if we were to try and
	// assign the address of function3 (the one with a signature of void(int))
	// to our easyPtrFunc, we'll get a compiler error. C++ knows that
	// easyPtrFunc points to functions with signatures of void(), so it
	// won't work. Thanks C++!
	// easyPtrFunc = &function3;
	
	// Let's use it anyway, again i could write auto and the compiler
	// wouldn't skip a beat.
	PointerToIntFunction ptrToIntFunc = &function3;
	
	// Now I'll call it passing an integer and vóila, new function call
	// new output.
	ptrToIntFunc( 10 );
	
	// Alright now lets get a bit more complicated. So function4 has
	// a different signature than the others. It takes a function ptr as
	// argument. Then it's going to call that function inside itself.
	// Many functional programmers will scoff at this because it's basically
	// all they do :) . Anyway, what I'm doing is passing a function, which
	// takes a parameter, into another function which will supply that
	// parameter.
	function4( &function3 );
	
	return 0;
}
