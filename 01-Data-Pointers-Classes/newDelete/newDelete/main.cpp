//
//  main.cpp
//  newDelete
//
//  Created by Mike Allison on 9/13/14.
//  Copyright (c) 2014 Mike Allison. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[])
{
    //create a null int pointer
    //this pointer memory lives on the stack memory, it will get destoryed when the variable goes out of scope
    int * myIntPtr;
    
    std::cout  <<   myIntPtr   <<  std::endl;
    
    //create new HEAP memory (dynamic runtime memory) at that address by calling 'new', this will not get freed up when the variable goes out of scope
    myIntPtr = new int(200);
    
    std::cout  <<   *myIntPtr  << std::endl;
    
    //calling delete frees the heap memory at the pointers address
    delete myIntPtr;
    
     //if we didn't call delete, the stack pointer would go out of local scope and get destroyed but the heap memory that was created by 'new' at the pointer address would live on and causing a memory leak.
    
    return 0;
}

