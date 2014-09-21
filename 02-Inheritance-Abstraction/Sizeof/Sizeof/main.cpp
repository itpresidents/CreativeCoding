//
//  main.cpp
//  Sizeof
//
//  Created by Mike Allison on 9/20/14.
//  Copyright (c) 2014 Mike Allison. All rights reserved.
//

#include <iostream>

//a struct is a collection of datatypes, like a group.  Similar to a class it can have a constructor/destructor and member functions

struct Stuff {
    
    float mFloat; //4 bytes
    int   mInt;   //4 bytes
    long  mLong[1000];  //8 bytes

};


int main(int argc, const char * argv[])
{

    //sizeof() is a function built into c++ that returns the size in bytes of the argument type
    
    std::cout << "size of float: " << sizeof( float ) << std::endl;
    std::cout << "size of long: "  << sizeof( long ) << std::endl;
    std::cout << "size of int: "   << sizeof( int ) << std::endl;
    
    std::cout << std::endl;
    
    std::cout << "size of stuff: "         << sizeof( Stuff ) << std::endl;
    std::cout << "size of stuff pointer: " << sizeof( Stuff* ) << std::endl;

    return 0;
}

