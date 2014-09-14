
#include <iostream>

int main(int argc, const char * argv[])
{
    // Pointers can point to many things. Pointers can point to stack
	// memory, i.e. int myInt = 200; int* myIntPtr = &myInt;, they can
	// point to heap memory, i.e. int* myIntPtr = new int(200), they're
	// used for stack arrays, i.e. int myIntArray[20] (in this case
	// myIntArray is a pointer to the first element of myIntArray, using
	// [] dereferences the pointer and adds the multiple of the number
	// by the size of the data, i.e. myIntArray[4] takes the address at
	// myIntArray and adds 4 * sizeof(int), which is 16, to myIntArray,
	// and they can be used with heap arrays in a very similar way. For
	// instance...
	

    // create a new array of 10 ints on the heap
    int * myIntHeapArray = new int[10];
	// create a new array of 10 ints on the stack
	int myIntStackArray[10];
    
    // initialize the data inside each array and stream it out
    for( int i = 0; i < 10 ; i++ ){
        myIntHeapArray[i] = i;
		myIntStackArray[i] = i * 2;
		
        std::cout << "myIntHeapArray[" << i << "]: " <<  myIntHeapArray[i] <<  std::endl;
        std::cout << "myIntStackArray[" << i << "]: " <<  myIntStackArray[i] <<  std::endl;
    }
    
    // Even though the two different arrays act very similarly,
	// one array (heap) was created by talking to the operating system,
	// the other array (stack) was created during compile time so your
	// program already knows about the memory specifications of it and
	// will free the memory when it leaves scope.
	
	// To free the memory associated with the heap array you use a similar
	// delete command just this time you use the brackets ([]) to let the
	// program know that you are going to be giving back an array of things
	// to the operating system
    delete [] myIntHeapArray;
	
	// It is important to never try to free stack memory with the delete
	// operator. Below, I've commented out the call but you will get errors
	// from the compiler if you do this, because when stack memory is known
	// at compile time, the program takes care of freeing the memory for you.
	// uncomment it to see the errors.
	
	// delete [] myIntStackArray;

    return 0;
}

