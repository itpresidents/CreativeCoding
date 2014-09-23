//
//  main.cpp
//  StdCasts
//
//  Created by Mike Allison on 9/20/14.
//  Copyright (c) 2014 Mike Allison. All rights reserved.
//

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <array>

// So this example is going to show a couple of things past actual inheritance,
// if you need a refresher on what's going on with inheritance, look back at
// the BasicInheritance sample.

// This is probably the first time you've seen 'enum'. Even weirder it proceeds
// class. So what is going on between the braces. The use of the word class is
// meant to indicate that each enum type really is different and not comparable
// to other enum types. Strongly typed enums, enum classes, also have better
// scoping. Each enum value is scoped within the name of the enum class. In other
// words, to access the enum values, you must write: DerivedTypes::DERIVED_FLOAT.
// Look below for the usage. Also, for a further explanation checkout...
// http://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html
enum class DerivedTypes {
    DERIVED_FLOAT,
    DERIVED_ARRAY
};


// Simple Base class from the BasicInheritance sample. For an explanation of
// what isn't being explained look at that sample.
class Base {
public:
	
	// Constructor
    Base( const std::string& name ) : mName(name){}
	// Virtual Destructor
	// We saw this in the last sample but I didn't explain what was going on. Now I will.
	// Basically, like you saw in the last sample, we can cast derived classes into their
	// inherited from base classes. That's a really powerful concept as we'll see below.
	// However, think about what we're doing. We're essentially promising the compiler that
	// the Memory Layout of the object Memory Layout (that of any Derived Type we may make)
	// is actually a different Memory Layout (that of Base). We're lying, but because their's
	// a C++ Specification we can rest assured that if we just make sure we take the
	// lie all the way, we're safe. Think about what would happen if, after casting the Derived
	// instance to the Base class Memory Layout when, we destroyed that base object. Which
	// destructor would it use, clearly it would use the Base destructor, which knows nothing
	// of the Derived classes' Member variables that may need to be destroyed as well.
	// So just like when we want to override a virtual method in a derived class, we make
	// the Destructor of any class used as a Base class (a class meant to be inherited from)
	// virtual. That makes it overridable. However, different from normal virtual methods
	// it'll be called after the overriden destructor from a Derived class. Then we'll have
	// perfect cleanup! :) I'm going to print something out on destruction so you can see in
	// what order it will be called.
	virtual ~Base() { std::cout << "BASE Destructor with name: " << mName << std::endl; }
	// Getter
    const std::string& getName() { return mName; }
	// Pure Virtual Function - any inherited class is contractually obligated
	// to implement this if they'd like to make an instance of themselves
    virtual void print() = 0;
	
	// Note: Here's the first usage of the 'enum class' DerivedTypes. However, since it's pure virtual
	// I'm going to save the explanation until there's a definition. One thing is that I have defined
	// that this function should be const, because this function should not change anything about the
	// data members in the instance.
    virtual DerivedTypes getDerivedType() const = 0;

// 'protected:' so that inherited classes can use.
protected:
    std::string mName;
};

// Simple Derived class from the BasicInheritance sample. The name's been changed. For an explanation of
// what isn't being explained look at that sample.
class DerivedFloat : public Base {
public:
	
	// Constructor												Note: Base is initialized first.
    DerivedFloat( const std::string& name, const float& number ) : Base(name), mNumber(number){}
	
	// Overriding Destructor for Base. This is going to print out something so you can see the
	// order of destruction. Notice I don't have to write override because there can only be one
	// destructor.
	~DerivedFloat() { std::cout << "DERIVED_FLOAT Destructor with name: " << mName << std::endl; }
	
	// Implementation of the inherited pure virtual print function. Notice that I use override
	// as a nice safety net to make sure I'm actually overriding the function.
    void print() override { std::cout<< "I'm DerivedFloat: " << getNumber() << " " << mName <<std::endl; }
	
	// Simple other function not on Base. Used in the overriden print function.
    float getNumber(){ return mNumber; }
	
	// Implementation of the inherited pure virtual 'getDerivedType' function from Base. Now I'll
	// explain what we're using this DerivedType, enum class, for. Basically, this paradigm is
	// a type of what is called RTTI, Run-Time Type Information. As you saw in the last sample
	// it may become important to know what type the Base Casted Class is in case we need to
	// use the derived class member's in any way that is outside of how the base interface is
	// designed. To see the actual usage look below. Also, notice that I've kept tight to the
	// contract by making this const and just inserting the DerivedTypes type directly in the
	// function. It doesn't need to be a member because it is constant to any instance that
	// I make of this class.
    DerivedTypes getDerivedType() const override { return DerivedTypes::DERIVED_FLOAT; }
 
// We don't need to derive from this, hence 'private:'.
private:
    float mNumber;
};

// Simple Derived class from the BasicInheritance sample. The name's been changed. And it is different
// from the above class in that it's 'mNumber' is an int. This is simple just to show that I could
// have a need of a 'Base' class that also has different functionality than the above derived class.
class DerivedArray : public Base {
public:
	
	// Constructor						Note: Base initializer first, then the braced initializer for my std::array
	DerivedArray( const std::string& name ) : Base(name), mNumbers( { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } ) {}
	
	// Overriding Destructor for Base. This is going to print out something so you can see the
	// order of destruction. Notice I don't have to write override because there can only be one
	// destructor.
	~DerivedArray() { std::cout << "DERIVED_ARRAY Destructor with name: " << mName << std::endl; }
	
	// Implementation of the inherited pure virtual print function. Notice that I use override
	// as a nice safety net to make sure I'm actually overriding the function.
    void print() override
	{
		std::cout<< "I'm DerivedInt: " << std::endl;
		// We haven't seen this yet but you've probably seen it in other languages. This is a
		// for-each loop and it is exactly that. This will iterate through this structure which
		// happens to be a std::array of integers (look below for a discussion of what std::array
		// is). Another thing we probably haven't seen is auto, which I'm going to defer explaining
		// until below. For now, think of it like a type definition (i.e. int, float, etc.)
		// that the compiler fills in at compile-time. So, this line is basically saying, for each
		// element of mNumber, which the compiler knows is a std::array of int type, iterate through
		// the entire array and for each element take a reference to that type (int in this case)
		// and stick it in number and print it.
		for( auto & number : mNumbers ) {
			std::cout << "\t" << number << std::endl;
		}
		std::cout << mName << std::endl;
	}
	
	// Implementation of the inherited pure virtual 'getDerivedType' function from Base. Look above
	// and below for a discussion of what it'll be used for.
    DerivedTypes getDerivedType() const override { return DerivedTypes::DERIVED_ARRAY; }

// We don't need to derive from this, hence 'private:'.
private:
	// This is a C++11 construct. Basically, it's very similar to an array declared like this...
	//
	// int mNumbers[10];
	//
	// In fact, though we haven't spoken about templates, this is the auto-complete
	// for std::array -
	//
	// std::array<<#class _Tp#>, <#size_t _Size#>>
	//
	// Without going too far into a template, take a look at the two arguments. The first is named _Tp
	// and the second is named _Size. _Tp stands for type, in other words, what type is this array, and
	// _Size stands for how big will it be. This is different from std::vector as it is a constant sized
	// array. To show how similar it is to the original array...the member variable in std::array is
	// basically defined like this...
	//
	// _Tp mElements[_Size];
	//
	// So it is very similar but unlike a C-Style array it provides a great amount of functionality
	// beyond what a C-Style array provides as can be seen in the for statement in this classes' 'print'
	// function.
    std::array<int, 10> mNumbers;
};

// I know I've introduced you to maybe some crazy stuff so far in this lesson, maybe not but what I'm
// trying to get across is that if you buy into the specification you can see how fluid the programming
// process can be. Basically (and I know I've used that word a lot), you just have to teach the compiler
// how you'd like to program and the compiler and you can talk for hours. Below is an example of this...

// Here is another C++11 construct. Basically, just like any variable you can define what you'd like
// to call types. C++ has some real ugly types. Take this example for instance...
//
// std::map<std::string, std::vector<std::shared_ptr<SomeEnormousType>>> mFloatMap;
//
// This is a simple key value structure that has a string as the key and the value would be a vector
// of shared_ptr's to a large type. Imagine having to type this everytime you wanted to create one.
// Awful! So, 'using' allows you to define another name for a type, just like you're defining a
// variable. Awesome! If I instead define the above like this.
//
// using FloatMap = std::map<std::string, std::vector<std::shared_ptr<SomeEnormousType>>>;
//
// Then I can define 'mFloatMap' (the instance of a FloatMap) or any other variable of this type like
// this.
//
// FloatMap mFloatMap;
//
// So much more readable! That's what I've done below.
using BaseRef = std::shared_ptr<Base>;
using DerivedFloatRef = std::shared_ptr<DerivedFloat>;
using DerivedArrayRef = std::shared_ptr<DerivedArray>;
using BaseList = std::vector<BaseRef>;


int main(int argc, const char * argv[])
{
	// Make an instance of BaseList. If you, or anyone, forgets what BaseList, all you do is Cmd-Click
	// (on Mac) the type and it'll bring you to the definition. Also, here I'll discuss what auto is
	// doing. If you look at the line below you can read it like mBases is being initialized with a
	// construction of BaseList. Therefore, there's no doubt as to what type mBases is. It is clearly
	// an instance of BaseList. 'auto' allows us to use type-inference in C++ which is another great
	// expressive idea that has been a part of higher-level languages for a long time but unlike many
	// higher-languages that need to run-time check the type information of an object. The inferring
	// happens at compile time so there's no penalty for that inference. That is amazing. Also, look
	// at what we've written, BaseList is a type that we've defined above with our using statement,
	// our using statement uses a type BaseRef that we defined above that. In essence without these
	// constructs we'd be writing this line like this.
	//
	// std::vector<std::shared_ptr<Base>> mBases = std::vector<std::shared_ptr<Base>>();
	//
	// Could you imagine how awful that'd be? Can you see why C++ has had a bad name for so long? The
	// below line show just how much more modern C++ has become. It is so much more expressive!
    auto mBases = BaseList();
	
	// Now I can add instances of Derived Classes that inherit from Base easily into this vector because
	// shared_ptr's will implicitly cast the underlying pointer, which is of Derived type, to the base
	// type and it does this safely by checking types at compile-time and throwing errors if you're doing
	// something you shouldn't be, like trying to convert something you think is derived that isn't actually
	// So Safety! So Nice! Also notice how nice the type definitions are to write!
    mBases.push_back( DerivedFloatRef( new DerivedFloat( "Mike", 29.0f ) ) );
    mBases.push_back( DerivedArrayRef( new DerivedArray( "Ryan" ) ) );

    // Now hopefully you can see what is going on with auto here. Basically because the compiler
	// knows that mBases is a std::vector of BaseRefs it already knows what type 'basePtr' should
	// be, BaseRef. After it figures out what type 'basePtr' is, I then tell it that I'd like
	// to take a reference to that type which means that 'basePtr' is going to point to the
	// shared_ptr which holds the instance of Base. It seems like I'm saying a lot with just a
	// couple of letters, which happens to be only good. This is the reason that we've spent
	// so much time on syntax, because once you understand what's going on, you'll be able to
	// just express what you mean.
    for ( auto & basePtr : mBases ) {
		// Use base like it has been created to be used.
        std::cout << basePtr->getName() << std::endl;
        basePtr->print();
		
		// I'd like to do something with DerivedFloat specifically. So, let's check it's run-time
		// type information.
        if( basePtr->getDerivedType() == DerivedTypes::DERIVED_FLOAT ) {
			// Yaaaayyyy auto! std also provides a function called dynamic_pointer_cast for std::shared_ptr's
			// you put the type of shared pointer (DerivedFloat) you'd like to cast to and provide the
			// object you'd like to cast (basePtr) and It will return a std::shared_ptr<DerivedFloat>. Now
			// we can see that auto will work because we've told the compiler all the info it needs to descern
			// the type of derivedFloatPtr. Simple!
            auto derivedFloatPtr = std::dynamic_pointer_cast<DerivedFloat>( basePtr );
			// Let's check that.
            std::cout << "I'm a derived float ptr: " << derivedFloatPtr->getNumber() << std::endl;
        }
		else {
			std::cout << basePtr->getName() << " isn't a DERIVED_FLOAT" << std::endl;
		}
    }
	
	// After this function returns you'll be able to see the way in which order everything is destroyed.
	// Check the console! And thanks for following me through this windy road. I promise when you understand
	// what's basically going on in the lessons up to here things about C++ will become much easier.
	
    return 0;
}














