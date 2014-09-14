
#include <iostream>

// include the code that contains the vector functionality
#include <vector>

// when we know that a number should remain constant, we use
// the keyword 'const' in front of the datatype. This is a
// compiler flag that will throw compile time errors if we
// try to change the value after it has been initialized.
// It is a convention to use all capital letters for the
// variable names. This is also a global variable because
// it is outside any local scopes we've created.
const int NUM_INTS = 10;

// Uncomment the line below to see what happens

// NUM_INTS = 12;

int main(int argc, const char * argv[])
{

    // A vector, in the 'std' namespace, is a container object, akin to ArrayList in Java
	// or Array in JavaScript, that holds a dynamic amount of a specific type, in this case
	// integer, and it guarantees that the elements it contains will be in contiguous
	// memory. This is also the first time we've come across templates, which are denoted
	// by the '< >' operators. This allows us to make truly generic types that can be
	// rewritten at compile time. You can think of the type of myInts as not std::vector
	// but std::IntVector, because we put 'int' inside the '< >'. We could also put
	// std::vector<float> and that would be a different type than std::vector<int>.
    std::vector<int> myInts;
    
    // Vectors have a number of different member functions and helpers to work with the
	// specific functionality central to std::vector<>. For instance, resize will check
	// the amount of ints it can contain and change that amount to what we pass into it's
	// argument. Here we're saying resize myInts to NUM_INTS. It will first check to see
	// if the HEAP memory it contains is large enough to store NUM_INTS and if it isn't
	// it will go back to the operating system, ask for that amount of memory, copy all
	// of the current contents into the 'new' memory and then 'delete' the old memory
    myInts.resize( NUM_INTS );
    
    for(int i = 0; i < NUM_INTS; i++){
        // You can use std::vector very similarly to a regular array. '[]' operator will access
		// the memory at that index.
        myInts[i] = i;
		
		// We can print out the contents similarly as well.
        std::cout << myInts[i] << std::endl;
    }
	
	// Lets say that we're somewhere else in the program and we need to add some other elements
	// that we didn't intend to add. All we have to do is use the push_back function, this is
	// very similar to ArrayList in Java and Array in Javascript.
	myInts.push_back( NUM_INTS );
	myInts.push_back( NUM_INTS + 1 );
	
	// Now it is storing 2 more than it was resized to have. It will go through the same process
	// as it went through with resize to make sure it has enough memory to store them or it
	// will go back to the operating system and get more memory.
	std::cout << myInts[ NUM_INTS ] << std::endl;
	std::cout << myInts[ NUM_INTS + 1 ] << std::endl;
	
    // The size() function will return the number of elements the vector contains. In our case,
	// we originally created 10 or NUM_INTS and then we pushed two more elements onto it so the
	// final size is 12.
    std::cout << "Number of Integers currently stored in myInts: " << myInts.size() << std::endl;

    // The clear() function will free all the memory in the vector, this happens automatically
	// when the vector goes out of scope and the destructor gets called
    myInts.clear();
    
    return 0;
}

