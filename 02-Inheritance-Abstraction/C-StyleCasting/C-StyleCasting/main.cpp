//
//  main.cpp
//  C-StyleCasting
//
//  Created by Mike Allison on 9/20/14.
//  Copyright (c) 2014 Mike Allison. All rights reserved.
//

#include <iostream>

//simple class that holds and returns a float
class Object {
public:
    
    Object():mFloat(0){}
    Object( const float& initial_value ):mFloat(initial_value){}
    ~Object(){ std::cout<<"I am destroyed" << std::endl; }
    
    float getValue(){ return mFloat; }
    void setFloat( const float& new_val ){ mFloat = new_val; }
    
private:
    float mFloat;
    
};


int main(int argc, const char * argv[])
{

    //create an instance of object with value of 20
    Object obj = Object(20);
    
    //lets log it out to see it
    std::cout << obj.getValue() <<std::endl;
    
    //here we are doing a c-style cast of the object's reference to a void* type
    void* ptr = (void*)&obj;
    
    //now we have a void pointer, lets see its address because thats all the information we can know about void pointers
    std::cout << ptr <<std::endl;
    
    //now if we c-style cast that void pointer back to a pointer of type Object, then we have a new pointer that is pointing to exactly the same memory ocupied by our original Object
    Object* objPtr = (Object*)ptr;
    
    //see, the value is exactly the same.
    std::cout << objPtr->getValue() << std::endl;
    
    //in this example, we c-style casted from an Object to void* and back to an Object
    
    return 0;
}

