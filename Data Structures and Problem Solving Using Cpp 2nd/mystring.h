#ifndef MY_STRING_H_
#define MY_STRING_H_

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;      // Borland has a bug
    #endif
#endif

#include "StartConv.h"

class string
{
  public:
    string( const char *cstring = "" );               // Constructor
    string( char ch );              	              // Constructor
    string( const string & str );                     // Copy constructor
    ~string( )                                        // Destructor
      { delete [ ] buffer; }

    const string & operator= ( const string & rhs );  // Copy
    const string & operator+=( const string & rhs );  // Append

    const char *c_str( ) const        // Return C-style string
      { return buffer; }
    int length( ) const               // Return string length
      { return strLength; }

    char   operator[]( int k ) const; // Accessor operator[]
    char & operator[]( int k );       // Mutator  operator[]

  private:
      char *buffer;                  // storage for characters
      int strLength;                 // length of string (# of characters)
      int bufferLength;              // capacity of buffer
};

ostream & operator<<( ostream & out, const string & str );    // Output
istream & operator>>( istream & in, string & str );           // Input
istream & getline( istream & in, string & str );              // Read line
istream & getline( istream & in, string & str, char delim );  // Read line

string operator+( const string & lhs, const string & rhs );   // Concatenation

bool operator==( const string & lhs, const string & rhs );    // Compare ==
bool operator!=( const string & lhs, const string & rhs );    // Compare !=
bool operator< ( const string & lhs, const string & rhs );    // Compare <
bool operator<=( const string & lhs, const string & rhs );    // Compare <=
bool operator> ( const string & lhs, const string & rhs );    // Compare >
bool operator>=( const string & lhs, const string & rhs );    // Compare >=

#include "EndConv.h"

#endif
