//
//  main.cpp
//  stdVector
//
//  Created by Mike Allison on 9/14/14.
//  Copyright (c) 2014 Mike Allison. All rights reserved.
//

#include <iostream>
#include <vector>

const int NUM = 10;

int main(int argc, const char * argv[])
{

    //a vector is a container object that holds a dynamic amount of items in contiguious memory
    std::vector<int> myInts;
    
    //resize allocates the memory space for NUM new ints and then some, in case you add more later
    myInts.resize(NUM);
    
    for(int i = 0; i < NUM; i++){
        
        //use push_back to place a new object on the back of the array
        myInts.push_back(i);
        
        //vectors use the '[]' operator to access at index positions just like regular arrays
        std::cout<< myInts[i] <<std::endl;
    }
    
    //get the whole size
    std::cout<< myInts.size() <<std::endl;

    
    //clear will free all the memory in the array, this happens automatically when the vector goes out of scope and the destructor gets called
    myInts.clear();
    
    return 0;
}

