//
//  main.cpp
//  pointerArray
//
//  Created by Mike Allison on 9/13/14.
//  Copyright (c) 2014 Mike Allison. All rights reserved.
//

#include <iostream>



int main(int argc, const char * argv[])
{
    
    //create a new array of 10 null int pointers
    int * myIntArray = new int[10];
    
    //fill the array with new data and stream it out
    for( int i = 0; i < 10 ; i++ ){
        
        myIntArray[i] = i;
        
        std::cout <<  myIntArray[i] <<  std::endl;
        
    }
    
    //free the memory
    delete [] myIntArray;

    return 0;
}

