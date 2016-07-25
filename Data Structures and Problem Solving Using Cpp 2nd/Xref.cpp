// Xref class interface: generate cross-reference.
//
// CONSTRUCTION: with an istream object.
//
// ******************PUBLIC OPERATIONS***********************
// void generateCrossReference( ) --> Name says it all ...
// ******************ERRORS**********************************
// Error checking on comments and quotes is performed.

#include "Tokenizer.h"

#ifdef USE_DOT_H
    #include <iostream.h>
    #include <fstream.h>
#else
    #include <fstream>
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;      // Borland 5.0 has a bug
    #endif
#endif
    
#ifndef SAFE_STL
    #include <list>
    #include <string>
    #include <map>
    #include <functional>
    using namespace std;
#else
    #include "list.h"
    #include "mystring.h"
    #include "map.h"
    #include "functional.h"
    #include "StartConv.h"
#endif


class Xref
{
  public:
    Xref( istream & input ) : tok( input ) { }

    void generateCrossReference( );

  private:
    Tokenizer tok;      // Token source
};

// Output the cross reference.
void Xref::generateCrossReference( )
{
    typedef map<string,list<int>, less<string> > MapType;
    typedef MapType::const_iterator MapIteratorType;

    MapType xrefMap;
    string current;

      // Insert identifiers into the map.
    while( ( current = tok.getNextID( ) ) != "" )
        xrefMap[ current ].push_back( tok.getLineNumber( ) );

      // Iterate through map and output
      // identifiers and their line number.
    MapIteratorType itr;
    for( itr = xrefMap.begin( ); itr != xrefMap.end( ); ++itr )
    {
        const list<int> & theLines = (*itr).second;
        list<int>::const_iterator lineItr = theLines.begin( );

          // Print identifier and first line where it occurs.
        cout << (*itr).first << ": " << *lineItr;


          // Print all other lines on which it occurs.
        for( ++lineItr; lineItr != theLines.end( ); ++lineItr )
            cout << ", " << *lineItr;
        cout << endl;
    }
}


int main( int argc, const char **argv )
{
    if( argc == 1 )
    {
        Xref p( cin );
        p.generateCrossReference( );
        return 0;
    }

    while( --argc )
    {
        ifstream ifp( *++argv );
        if( !ifp )
        {
            cout << "Cannot open " << *argv << endl;
            continue;
        }
        cout << "*********" << *argv << "*********\n";
        Xref p( ifp );
        p.generateCrossReference( );
    }

    return 0;
}

#ifdef SAFE_STL
    #include "EndConv.h"
#endif
