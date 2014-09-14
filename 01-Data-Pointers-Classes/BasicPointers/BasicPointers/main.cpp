//
//  main.cpp
//  BasicPointers
//
//  Created by Mike Allison on 9/14/14.
//  Copyright (c) 2014 Mike Allison. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[])
{
    
    //create a real value in memory on the stack - the stack is local to the scope of the function, in this case main()
    int myInt = 200;
    
    //create a null pointer ( null means empty ) by using the '*' star operator after the type declaration
    int* myIntPtr;
    
    //log out some values to the console
    std::cout<< "myInt lvalue: "      <<    myInt     << std::endl;
    std::cout<< "myInt ptr address: " <<    &myInt    << std::endl;
    std::cout<< "myInt address: "     <<    myIntPtr  << std::endl;
    
    //Using the address-of operator '&' in front of an lvalue variable returns the address associcated with that variable, essentially the value a pointer would have -- something like 0xffac20cd

    //Use '&' to set the null pointer equal to the reference address of the real value in memory.
    myIntPtr = &myInt;
    
    //space
    std::cout<< std::endl;
    
    //look again, now myIntPtr points to the same value that myInt references.
    std::cout<< "myInt ptr address: "     <<    &myInt     << std::endl;
    std::cout<< "myIntPtr address: "      <<    myIntPtr   << std::endl;
    
    //use the '*' operator in front of a pointer to dereference the pointer and return the real value associated with that address.
    
    std::cout<< "Dereferenced myIntPtr: " <<    *myIntPtr  << std::endl;
    
    std::cout << std::endl;
    std::cout << std::endl;
    
    //for more info on lvaues and rvalues and the '&' operator see : http://eli.thegreenplace.net/2011/12/15/understanding-lvalues-and-rvalues-in-c-and-c/
    
    return 0;
}

