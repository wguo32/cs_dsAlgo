#pragma warning (disable: 4786)

// Balance class interface: check for balanced symbols
//
// CONSTRUCTION: with an istream object
// ******************PUBLIC OPERATIONS********************
// int CheckBalance( )   --> Print mismatches
//                           return number of errors

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
    #include <vector>
    #include <stack>
    using namespace std;
#else
    #include "vector.h"
    #include "stack.h"
    #include "StartConv.h"
#endif

#include <stdlib.h>

// Symbol is the class that will be placed on the Stack.
struct Symbol
{
    char token;
    int  theLine;
};

class Balance
{
  public:
    Balance( istream & input ) : tok( input ), errors( 0 ) { }

    int checkBalance( );

  private:
    Tokenizer tok;
    int errors;

    void checkMatch( const Symbol & opSym, const Symbol & clSym );
};


// Print error message for unbalanced symbols.
int Balance::checkBalance( )
{
    char ch;
    Symbol lastSymbol, match;
    stack<Symbol, vector<Symbol> > pendingTokens;  // Open symbols pending

    while( ( ch = tok.getNextOpenClose( ) ) != '\0' )
    {
        lastSymbol.token = ch;
        lastSymbol.theLine = tok.getLineNumber( );

        switch( ch )
        {
          case '(': case '[': case '{':
            pendingTokens.push( lastSymbol );
            break;
        
          case ')': case ']': case '}':
            if( pendingTokens.empty( ) )
            {
                cout << "Extraneous " << ch << " at line " << tok.getLineNumber( ) << endl;
                errors++;
            }
            else
            {
                match = pendingTokens.top( );
                pendingTokens.pop( );
                checkMatch( match, lastSymbol );
            }
            break;

          default: // Can't happen
            break;
        }
    }

    while( !pendingTokens.empty( ) )
    {
        match = pendingTokens.top( );
        pendingTokens.pop( );
        cout << "Unmatched " << match.token << " at line "
                    << match.theLine << endl;
        errors++;
    }

    return errors + tok.getErrorCount( );
}

// Print an error message if clSym does not match opSym.
// Update errors.
void Balance::checkMatch( const Symbol & opSym, const Symbol & clSym )
{
    if( opSym.token == '(' && clSym.token != ')' ||
        opSym.token == '[' && clSym.token != ']' ||
        opSym.token == '{' && clSym.token != '}' )
    {
        cout << "Found " << clSym.token << " on line " <<
            tok.getLineNumber( ) << "; does not match " << opSym.token
            << " at line " << opSym.theLine << endl;
        errors++;
    }
}


// main routine for balanced symbol checker.
int main( int argc, char **argv )
{
    if( argc == 1 )
    {
        Balance p( cin );
        if( p.checkBalance( ) == 0 )
            cout << "No errors" << endl;
        return 0;
    }

    while( --argc )
    {
        ifstream ifp( *++argv );
        if( !ifp )
        {
            cerr << "Cannot open " << *argv << endl;
            continue;
        }
        cout << *argv << ":" << endl;
        Balance p( ifp );
        if( p.checkBalance( ) == 0 )
            cout << "No errors" << endl;
    }

    return 0;
}

#ifdef SAFE_STL
    #include "EndConv.h"
#endif
