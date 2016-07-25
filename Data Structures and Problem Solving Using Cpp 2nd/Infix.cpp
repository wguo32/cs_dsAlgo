#pragma warning (disable: 4786)

// Evaluator class interface: evaluate infix expression.
// NumericType: Must have standard set of arithmetic operators
//
// CONSTRUCTION: with a string.
//
// ******************PUBLIC OPERATIONS***********************
// NumericType getValue( ) --> Return value of infix expression
// ******************ERRORS**********************************
// Some error checking is performed.

#ifdef USE_DOT_H
    #include <iostream.h>
    #include <fstream.h>
    #define USE_STR_DOT_H
#else
    #include <fstream>
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;
    #else
        #define USE_STR_DOT_H
    #endif
#endif
    
#ifdef __GNUC__
    #include <strstream.h>
    #define USE_STR_DOT_H
#else
#ifdef unix
    #include <strstream.h>
    #define USE_STR_DOT_H
#else
#ifdef USE_STR_DOT_H
    #include <strstrea.h>
    #include "getline.cpp"
#else
    #include <sstream>
    #include "getline.cpp"
#endif
#endif
#endif

#ifndef SAFE_STL
    #include <vector>
    #include <string>
    #include <stack>
    using namespace std;
#else
    #include "vector.h"
    #include "stack.h"
    #include "mystring.h"
    #include "StartConv.h"
#endif

#include <stdlib.h>
#include <math.h>



// A Pow routine for exponentiation.
template <class NumericType>
NumericType pow( const NumericType & x, const NumericType & n )
{
    if( x == 0 )
    {
        if( n == 0 )
            cerr << "0^0 is undefined" << endl;
        return 0;
    }
    if( n < 0 )
    {
        cerr << "Negative exponent" << endl;
        return 0;
    }
    if( n == 0 )
        return 1;
    if( n % 2 == 0 )
        return pow( x * x, n / 2  );
    else
        return x * pow( x, n - 1 );
}

enum TokenType { EOL, VALUE, OPAREN, CPAREN, EXP, MULT, DIV, PLUS, MINUS };

template <class NumericType>
class Token
{
  public:
    Token( TokenType tt = EOL, const NumericType & nt = 0 )
      : theType( tt ), theValue( nt ) { }

    TokenType getType( ) const
      { return theType; }
    const NumericType & getValue( ) const
      { return theValue; }

  private:
    TokenType   theType;
    NumericType theValue;
};

template <class NumericType>
class Tokenizer
{
  public:
    Tokenizer( istream & is ) : in( is ) { }

    Token<NumericType> getToken( );

  private:
    istream & in;
};


  // PREC_TABLE matches order of Token enumeration
struct Precedence
{
    int inputSymbol;
    int topOfStack;
} PREC_TABLE [ ] =
{
    { 0, -1 }, { 0, 0 },       // EOL, VALUE
    { 100, 0 }, { 0, 99 },     // OPAREN, CPAREN
    { 6, 5 },                  // EXP
    { 3, 4 }, { 3, 4 },        // MULT, DIV
    { 1, 2 }, { 1, 2 }         // PLUS, MINUS
};


template <class NumericType>
class Evaluator
{
  public:
#ifdef USE_STR_DOT_H
    #define istringstream istrstream
    Evaluator( const string & s ) : str( (char *) s.c_str( ), s.length( ) )
#else
    Evaluator( const string & s ) : str( s )
#endif
      { opStack.push_back( EOL ); }

        // The only publicly visible routine
    NumericType getValue( );          // Do the evaluation

  private:
    vector<TokenType>   opStack;      // Operator stack for conversion
    vector<NumericType> postFixStack; // Stack for postfix machine

    istringstream str;                // String stream

        // Internal routines
    NumericType getTop( );                // Get top of postfix stack
    void binaryOp( TokenType topOp );     // Process an operator
    void processToken( const Token<NumericType> & lastToken ); // Handle LastToken
};


// Public routine that performs the evaluation.
// Examines the postfix machine to see if a single result
// is left and if so, returns it; otherwise prints error.
template <class NumericType>
NumericType Evaluator<NumericType>::getValue( )
{
    Tokenizer<NumericType> tok( str );
    Token<NumericType> lastToken;

    do
    {
        lastToken = tok.getToken( );
        processToken( lastToken );
    } while( lastToken.getType( ) != EOL );

    if( postFixStack.empty( ) )
    {
        cerr << "Missing operand!" << endl;
        return 0;
    }

    NumericType theResult = postFixStack.back( );
    postFixStack.pop_back( );
    if( !postFixStack.empty( ) )
        cerr << "Warning: missing operators!" << endl;

    return theResult;
}

// After token is read, use operator precedence parsing
// algorithm to process it; missing opening parentheses
// are detected here.
template <class NumericType>
void Evaluator<NumericType>::processToken( const Token<NumericType> & lastToken )
{
    TokenType topOp;
    TokenType lastType = lastToken.getType( );

    switch( lastType )
    {
      case VALUE:
        postFixStack.push_back( lastToken.getValue( ) );
        return;

      case CPAREN:
        while( ( topOp = opStack.back( ) ) != OPAREN && topOp != EOL )
            binaryOp( topOp );
        if( topOp == OPAREN )
            opStack.pop_back( );  // Get rid of opening parentheseis
        else
            cerr << "Missing open parenthesis" << endl;
        break;

      default:    // General operator case
        while( PREC_TABLE[ lastType ].inputSymbol <=
               PREC_TABLE[ topOp = opStack.back( ) ].topOfStack )
            binaryOp( topOp );
        if( lastType != EOL )
            opStack.push_back( lastType );
        break;
    }
}

// top and pop the postfix machine stack; return the result.
// If the stack is empty, print an error message.
template <class NumericType>
NumericType Evaluator<NumericType>::getTop( )
{
    if( postFixStack.empty( ) )
    {
        cerr << "Missing operand" << endl;
        return 0;
    }

    NumericType tmp = postFixStack.back( );
    postFixStack.pop_back( );
    return tmp;
}

// Process an operator by taking two items off the postfix
// stack, applying the operator, and pushing the result.
// Print error if missing closing parenthesis or division by 0.
template <class NumericType>
void Evaluator<NumericType>::binaryOp( TokenType topOp )
{
    if( topOp == OPAREN )
    {
        cerr << "Unbalanced parentheses" << endl;
        opStack.pop_back( );
        return;
    }
    NumericType rhs = getTop( );
    NumericType lhs = getTop( );

    if( topOp == EXP )
        postFixStack.push_back( pow( lhs, rhs ) );
    else if( topOp == PLUS )
        postFixStack.push_back( lhs + rhs );
    else if( topOp == MINUS )
        postFixStack.push_back( lhs - rhs );
    else if( topOp == MULT )
        postFixStack.push_back( lhs * rhs );
    else if( topOp == DIV )
        if( rhs != 0 )
            postFixStack.push_back( lhs / rhs );
        else
        {
            cerr << "Division by zero" << endl;
            postFixStack.push_back( lhs );
        }

    opStack.pop_back( );
}

// Find the next token, skipping blanks, and return it.
// Print error message if input is unrecognized.
template <class NumericType>
Token<NumericType> Tokenizer<NumericType>::getToken( )
{
    char ch;
    NumericType theValue;

        // Skip blanks
    while( in.get( ch ) && ch == ' ' )
        ;

    if( in.good( ) && ch != '\n' && ch != '\0' )
    {
        switch( ch )
        {
          case '^': return EXP;
          case '/': return DIV;
          case '*': return MULT;
          case '(': return OPAREN;
          case ')': return CPAREN;
          case '+': return PLUS;
          case '-': return MINUS;

          default:
            in.putback( ch );
            if( !( in >> theValue ) )
            {
                cerr << "Parse error" << endl;
                return EOL;
            }
            return Token<NumericType>( VALUE, theValue );
        }
    }

    return EOL;
}

// A simple main to exercise Evaluator class.
int main( )
{
    string str;

    while( getline( cin, str ) )
    {
        Evaluator<int> e( str );
        cout << e.getValue( ) << endl;
    }

    return 0;
}

#ifdef SAFE_STL
    #include "EndConv.h"
#endif
