//
//  main.cpp
//  2-Functor
//
//  Created by ryan bartley on 6/25/15.
//  Copyright (c) 2015 ryan bartley. All rights reserved.
//

#include <iostream>
#include <map>
#include <chrono>

using namespace std;
using namespace std::chrono;
// This is being used below and will be explained below.
chrono::high_resolution_clock::time_point StartTime = chrono::high_resolution_clock::now();

// Wikipedia definition of a Functor in C++: a function object
// may be used instead of an ordinary function by defining a class
// that overloads the function call operator by defining an operator()
// member function. In C++, this is called a class type functor.

// That's a lot of words. Hopefully you know what most of it means by now
// but even if you don't you will. Basically, a functor is a class construct
// that overloads the "callable" operator (or operator()) to allow the object
// to act as a function. Take the class below for example.

// PrintFunctor is a very simple class that has an overloaded operator() taking
// a string, which simply prints the string to the console. Anytime you instantiate
// PrintFunctor, you can use it to print strings to the console as is the case below
// in main. Pretty simple.
class PrintFunctor {
public:
	void operator()( const std::string & string ) { cout << string << endl; }
};

// The real power of functors happens when you realize you can hold state inside
// them. Since it's a class, functors can have member variables, functions etc.
// Take the next functor for example. This is a simple logger that grabs a time
// and string and holds them till it's reached a certain amount of logs, and then
// prints them formatted to the console.
class LogFunctor {
public:
	// As you'll see, Functors can wrap complicated logic and state around an object
	// that looks and acts like a function.
	void operator()( const std::string &string )
	{
		// First timestamp when this happened. For more info about std::chrono take
		// a look here http://en.cppreference.com/w/cpp/chrono
		auto logTime = high_resolution_clock::now();
		// insert your log entry into the log map. Map's insert function returns a
		// std::pair<iterator,bool>, the bool represents whether or not the entry
		// was inserted. Also, in this case std::map will help keep the entries in
		// order for basically free. Because maps keep the keys in an order, the times
		// as keys will be stored in ascending order. For more on maps check out the
		// next chapter.
		auto inserted = mLog.insert( make_pair( logTime, string )  );
		// if it wasn't inserted. Log an error to console.
		if( ! inserted.second ) {
			cout << "[ERROR] Problem with entry, " << string << endl;
			return;
		}
		// otherwise check to see if we're at our capacity and dump the log.
		else if( mLog.size() > 5 ) {
			dump();
		}
	}
	// Here's a function that is public which deals with iterating our log entries
	// and calling our private printFormatted function, which actually prints logs
	// to the console.
	void dump()
	{
		// Here's a for each loop that will iterate through the log entries.
		for( auto & logEntry : mLog ) {
			// First see how much time has elapsed from the start time.
			auto elapsed_seconds = logEntry.first - StartTime;
			// now print this entry formatted to the console.
			printFormatted( elapsed_seconds, logEntry.second );
		}
		// now clear the entries that have been printed to the console.
		mLog.clear();
	}
private:
	// we've made this function private as it doesn't need to be accessed outside this
	// functor. It contains implemenatation details.
	void printFormatted( duration<double> elapsed, const string &string )
	{
		cout << "[LOG ENTRY]: " << elapsed.count() << "s, Entry: " << string << endl;
	}
	
	// this is our entry container, a map with time_points as a key and strings as a
	// value.
	std::map<high_resolution_clock::time_point, std::string> mLog;
};

int main(int argc, const char * argv[]) {
	
	// instantiate PrintFunctor
	PrintFunctor print;
	// now use it like you'd use any function.
	print( "Hello Functor World" );
	
	// take up a bit of time so that the log times are easier to read.
	for( int i = 0; i < 1000000; i++ ) {}
	
	// instantiate a LogFunctor
	LogFunctor log;
	
	// now use it like you'd use any function.
	log( "I'll use a log." );
	log( "This log will gather all of my entries" );
	log( "Then once I get to the amount," );
	log( "it'll dump everything at once" );
	log( "One more and it will dump everything" );
	
	// print something to the console just to show that the logic of waiting until
	// the log is "full" is working correctly
	print( "I can't wait." );
	
	// with this log, all of the entries will be spit out onto the console
	log( "This is it." );
	
	// call it one last time.
	log( "One more log just to show the dump on the object" );
	// then call the function on the object to show that it's acting like an object
	// as well.
	log.dump();
	
    return 0;
}
