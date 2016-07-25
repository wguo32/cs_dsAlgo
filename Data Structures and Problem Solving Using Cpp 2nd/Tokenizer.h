#ifndef TOKENIZER_H
#define TOKENIZER_H

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;      // Borland 5.0 has a bug
    #endif
#endif
    
#ifndef SAFE_STL
    #include <string>
    using namespace std;
#else
    #include "mystring.h"
    #include "StartConv.h"
#endif


#include <stdlib.h>

class Tokenizer
{
  public:
    Tokenizer( istream & input )
      : currentLine( 1 ), errors( 0 ), inputStream( input ) { }

      // The public routines
    char getNextOpenClose( );
    string getNextID( );
    int getLineNumber( ) const;
    int getErrorCount( ) const;

  private:
    enum CommentType { SLASH_SLASH, SLASH_STAR };

    istream & inputStream;     // Reference to the input stream
    char ch;                   // Current character
    int currentLine;           // Current line
    int errors;                // Number of errors detected

      // A host of internal routines
    bool nextChar( );
    void putBackChar( );
    void skipComment( CommentType start );
    void skipQuote( char quoteType );
    string getRemainingString( );
};


#endif

#ifdef SAFE_STL
    #include "EndConv.h"
#endif
