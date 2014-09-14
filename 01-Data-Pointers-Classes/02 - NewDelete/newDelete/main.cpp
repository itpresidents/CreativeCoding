
#include <iostream>

// See Basic Pointers for explanation of these.
int main(int argc, const char * argv[])
{
    // create a null int pointer (nullptr is a value used to initialize pointers
	// to 0x0, meaning it doesn't point to anything) this variable (myIntPtr) lives
	// on the stack of main, it will get destoryed when the variable goes out of scope
	// basically when main returns at the bottom
    int * myIntPtr = nullptr;
	
	// Check to see the address stored in myIntPtr, it should be something like 0x0
    std::cout  <<   myIntPtr   <<  std::endl;
	
	// To create dynamic memory (on the Heap), you use the 'new' operator. 'new' asks the
	// operating system if it has memory it can afford to give, in this case 4 bytes for the
	// int that we'd like to initialize to 200. 'new' will then return an address to the
	// initialized memory that the operating system found which we'll store in myIntPtr.
    myIntPtr = new int(200);
	
	// Print out the 'new' address stored inside myIntPtr, as you'll see the value stored in
	// this pointer will no longer be 0x0, it'll be the address that 'new' returned
	std::cout  <<   myIntPtr   << std::endl;
	// Print out the value stored at that address by dereferencing myIntPtr with the '*'
    std::cout  <<   *myIntPtr  << std::endl;
    
    // This is the most important aspect of using Heap memory, after the operating system
	// gives you the address it forgets that it even had a conversation with your program.
	// It is your responsibility to give back the memory associated with myIntPtr. The way
	// to do this is by calling 'delete'. 'delete' is an operator like 'new' that tells the
	// operating system that you're done with the memory, otherwise the operating system
	// believes that you are still using that memory. That is called a memory leak. If
	// myIntPtr, a variable created on the stack, goes out of scope and therefore is destroyed
	// you will not be able to find that memory address and thus it gets leaked.
	delete myIntPtr;
	
    return 0;
}

