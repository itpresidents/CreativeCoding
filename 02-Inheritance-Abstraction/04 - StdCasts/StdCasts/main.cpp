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

enum DerivedTypes {
    DERIVED_FLOAT,
    DERIVED_INT
};

class Base {
public:
    
    Base( const std::string& name ) : mName(name){}
    const std::string& getName(){ return mName; }
    virtual void print() = 0;
    
    virtual DerivedTypes getDerivedType() = 0;
    
protected:
    std::string mName;
    
};

class DerivedFloat : public Base {
public:
    
    DerivedFloat( const std::string& name, const float& number ): Base(name), mNumber(number){}
    
    void print() override { std::cout<< "I'm DerivedFloat: " << mNumber << " " << mName <<std::endl; }
    
    float someotherthing(){ return mNumber; }
    
    DerivedTypes getDerivedType() override { return DerivedTypes::DERIVED_FLOAT; }
    
private:
    
    float mNumber;
    
};

class DerivedInt : public Base {
public:
    
    DerivedInt( const std::string& name, const int& number ): Base(name), mNumber(number){}
    
    void print() override { std::cout<< "I'm DerivedInt: " << mNumber << " " << mName <<std::endl; }
    
    DerivedTypes getDerivedType() override { return DerivedTypes::DERIVED_INT; }
private:
    
    int mNumber;
    
};

using BaseRef = std::shared_ptr<Base>;
using DerivedFloatRef = std::shared_ptr<DerivedFloat>;
using DerivedIntRef = std::shared_ptr<DerivedInt>;
using MyVectorBase = std::vector<BaseRef>;


int main(int argc, const char * argv[])
{

    MyVectorBase mBaseNames;
    
    mBaseNames.push_back( DerivedFloatRef( new DerivedFloat("Mike", 29.f) ) );
    mBaseNames.push_back( DerivedIntRef( new DerivedInt("Ryan", 187) ) );

    
    for ( auto & basePtr : mBaseNames ) {
        std::cout << basePtr->getName() << std::endl;
        basePtr->print();
        
        if( basePtr->getDerivedType() == DerivedTypes::DERIVED_FLOAT ) {
            auto mDerivedFloatPtr = std::dynamic_pointer_cast<DerivedFloat>( basePtr );
            std::cout << "I'm a derived float ptr: " << mDerivedFloatPtr->someotherthing() << std::endl;
        }
    }
    
    return 0;
}














