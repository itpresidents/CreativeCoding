
// This includes the functionality associated with cout (console out) and endl (end line)
#include <iostream>

// int is the return value, main is the name of the function and inside the parentheses
// are the arguments to the function argc -> Argument Count, argv -> string array of
// arguments, for instance if I were to type... git commit -m "Initial Commit"
// ... on the command line argc would be 3 and argv would be ["commit", "-m", "\"Initial Commit\""]
int main(int argc, const char * argv[])
{
    
    // create a real value in memory on the stack - the stack is local to the scope
	// of the function, in this case main()
    int myInt = 200;
    
    // create a null pointer ( null means empty ), the * means pointer and the int is
	// the type of data this pointer can point at
    int* myIntPtr = nullptr;
    
    // use the cout object and the stream operator (<<) to log what is contained in each
	// variable
	std::cout<< "myInt lvalue: "      <<    myInt     << std::endl;
	// Using the address-of operator '&' in front of an lvalue (something that has an address
	// in memory) returns the address associcated with that variable, essentially the value a
	// pointer would store -- something like 0xffac20cd
    std::cout<< "myInt ptr address: " <<    &myInt    << std::endl;
	// This should be zero because we initialized it with nullptr.
    std::cout<< "myInt address: "     <<    myIntPtr  << std::endl;

    // Now that we see that using the & operator gives us the address of an lvalue we can use it
	// to store the address inside the pointer, thus making the pointer point to the memory
	// associated with myInt.
    myIntPtr = &myInt;
    
    // This will make a space between the above and below console out statements.
    std::cout<< std::endl;
    
    // look again, now myIntPtr points to the same value that myInt references.
    std::cout<< "myInt ptr address: "     <<    &myInt     << std::endl;
    std::cout<< "myIntPtr address: "      <<    myIntPtr   << std::endl;
    
    // use the '*' operator in front of a pointer to dereference the pointer and return the real value
	// associated with that address.
    std::cout<< "Dereferenced myIntPtr: " <<    *myIntPtr  << std::endl;

    // This returns zero from Main meaning that the program exited successfully.
    return 0;
}

// for more info on lvaues and rvalues and the '&' operator see : http://eli.thegreenplace.net/2011/12/15/understanding-lvalues-and-rvalues-in-c-and-c/
