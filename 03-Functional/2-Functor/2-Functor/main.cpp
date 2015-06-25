//
//  main.cpp
//  2-Functor
//
//  Created by ryan bartley on 6/25/15.
//  Copyright (c) 2015 ryan bartley. All rights reserved.
//

#include <iostream>

using namespace std;

// Wikipedia definition of a Functor in C++: a function object
// may be used instead of an ordinary function by defining a class
// that overloads the function call operator by defining an operator()
// member function. In C++, this is called a class type functor.

// That's a lot of words. Hopefully you know what most of it means
// but even if you don't you will. So basically, a functor is a
// class construct that overloads the "callable" operator (or operator())

class PrintFunctor {
public:
	void operator()( const std::string & string ) { cout << string << endl; }
};

int main(int argc, const char * argv[]) {
	
	PrintFunctor p;
	
	p( "Hello Functor World" );
	
    return 0;
}
