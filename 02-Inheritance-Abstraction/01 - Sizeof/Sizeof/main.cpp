//
//  main.cpp
//  Sizeof
//
//  Created by Mike Allison on 9/20/14.
//  Copyright (c) 2014 Mike Allison. All rights reserved.
//

// Re-read the first chapter first section to figure out
// what include is doing here
#include <iostream>

// A struct is something that you should know about because
// you'll see it but don't worry about it too much. It's from
// the c days. It was the original user defined type. Basically
// it took atomic types (like int, float, etc...) and collected
// them into one structure, hence struct. In C++, struct's are
// almost exactly the same as classes. The big difference are
// the semantics of use, by that I mean, when you see a struct
// you can be sure that it is being used as a, sometimes, small
// collection of data. The biggest difference is in default
// member visibility. What I mean is that struct members are by
// default public, whereas class members are by default private.
struct Stuff {

	// Note: The member variables below are public, even though I haven't
	// written 'public:' under the struct statement. This means they can
	// be accessed outside of this struct.
	
	// The order in which you write member variables is important. Take the
	// following member variables, for instance. I have a float, an int, and
	// a long, which is 4 bytes, 4 bytes and eight bytes. That fits neatly
	// into a 16 byte alignment. These members want to be aligned with similar
	// spacing. If you un-comment the first long and comment out the second
	// long, when you run the program you'll see that the size of this struct
	// grows. It's growing because of the padding the compiler is adding.
	// I don't want to go too far down the rabbit hole with this at this point.
	// I just want to point out the way that you write things is the way the
	// compiler is going to structure and read things and it may not be
	// the way that you think.
	
	// if you're interested in exactly what's going on take a look here
	// http://en.wikipedia.org/wiki/Data_structure_alignment#Typical_alignment_of_C_structs_on_x86
	
    float mFloat;			//
	// long mLong;			// 1st Long - This long will throw off the spacing and add padding to the size. Most Likely 24 bytes
    int   mInt;				//
	long  mLong;			// 2nd Long - This long is placed appropriately to allow for optimal size. 16 bytes
	
    // long  mLong[1000];	// The size of this array is 8 bytes (size of long) * 1000. Uncomment this to see how the size of
							// a pointer doesn't change no matter what the size of the object. The reason being is that
							// a pointer is simply an address, like you'd see on an envelope, and the object is like the house
							// at that address. Look below for an explanation.
};


int main(int argc, const char * argv[])
{

    // 'sizeof' is a great function. It really shows you how the computer is
	// storing your memory. It's also calculates this size at compile time so
	// it's a little tricky. Basically, you pass it either a type or a variable
	// created from a type and it will give you the compile-time size of that
	// variable in bytes. If you run this program you'll see what I mean...
    
    std::cout << "size of float: " << sizeof( float ) << std::endl; // Prints out 'size of float: 4'
    std::cout << "size of long: "  << sizeof( long ) << std::endl;	// Prints out 'size of long: 8'
    std::cout << "size of int: "   << sizeof( int ) << std::endl;   // Prints out 'size of int: 4'
    
    std::cout << std::endl; // seperator
	
	// The above is what we expect for the atomic types. Now it gets interesting.
	// If you look at what the next two lines prints out, it's most likely this...
	
	// 'size of Stuff: 16'
	// 'size of Stuff pointer: 8'
	
	// This exemplifies one of the important aspects of pointers. Pointers on 64-bit machines are 8 bytes.
	// They're the size of 'long'. This doesn't change. We can pass pointers around and only
	// incur the cost of creating a long no matter what the type of data we're pointing to.
	
	// After you've run this once, un-comment the first long and comment out the second long.
	// You should see a significant size difference, depending on architecture. That is due
	// to the padding the compiler creates based upon the alignment of the data. Again,
	// if you're interested in what's going on there, follow the link, it's a quick read.
	// Then uncomment the long array and see that the size of the pointer (the address on the envelope)
	// never changes even though the size of Stuff (the house) grows to whatever size.
	
    std::cout << "size of Stuff: "         << sizeof( Stuff ) << std::endl;		// before the swap 16 bytes, after the swap 24 bytes,
																				// with the array somewhere over 8k.
	
    std::cout << "size of Stuff pointer: " << sizeof( Stuff* ) << std::endl;	// always 8 - bytes
	
	// sizeof acts a little different with references, even though references act similarly to pointers.
	// The C++ spec says this about 'sizeof' - 'When applied to a reference or a reference type,
	// the result is the size of the referenced type.' That's weird I know but references are typically
	// still the same size as a pointer.
	
	Stuff myStuff;
	Stuff & stuffReference = myStuff; // References have to be initialized with some value.
	
	std::cout << "size of Stuff reference: " << sizeof( stuffReference ) << std::endl;
	
	std::cout << std::endl;

    return 0;
}

