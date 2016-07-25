#include "Tokenizer.h"
#include <ctype.h>

#ifndef SAFE_STL
    #include <string>
    using namespace std;
#else
    #include "mystring.h"
    #include "StartConv.h"
#endif

// nextChar sets ch based on the next character in
// inputStream and adjusts currentLine if necessary.
// It returns the result of get.
// putBackChar puts the character back onto inputStream.
// Both routines adjust currentLine if necessary.
bool Tokenizer::nextChar( )
{
    if( !inputStream.get( ch ) )
        return false;
    if( ch == '\n' )
        currentLine++;
    return true;
}

void Tokenizer::putBackChar( )
{
    inputStream.putback( ch );
    if( ch == '\n' )
        currentLine--;
}

// Precondition: We are about to process a comment;
//                 have already seen comment start token.
// Postcondition: Stream will be set immediately after
//                 comment ending token.
void Tokenizer::skipComment( CommentType start )
{
    if( start == SLASH_SLASH )
    {
        while( nextChar( ) && ( ch != '\n' ) )
            ;
        return;
    }

        // Look for */
    bool state = false;    // Seen first char in comment ender.

    while( nextChar( ) )
    {
        if( state && ch == '/' )
            return;
        state = ( ch == '*' );
    }
    cout << "Unterminated comment at line " << getLineNumber( ) << endl;
    errors++;
}

// Precondition: We are about to process a quote;
//                   have already seen beginning quote.
// Postcondition: Stream will be set immediately after
//                   matching quote.
void Tokenizer::skipQuote( char quoteType )
{
    while( nextChar( ) )
    {
        if( ch == quoteType )
            return;
        if( ch == '\n' )
        {
            cout << "Missing closed quote at line " << ( getLineNumber( ) - 1 ) << endl;
            errors++;
            return;
        }
        // If a backslash, skip next character.
        else if( ch == '\\' )
            nextChar( );
    }
}

// Return the next opening or closing symbol or '\0' (if EOF).
// Skip past comments and character and string constants.
char Tokenizer::getNextOpenClose( )
{
    while( nextChar( ) )
    {
        if( ch == '/' )
        {
            if( nextChar( ) )
            {
                if( ch == '*' )
                    skipComment( SLASH_STAR );
                else if( ch == '/' )
                    skipComment( SLASH_SLASH );
                else if( ch != '\n' )
                    putBackChar( );
            }
        }
        else if( ch == '\'' || ch == '"' )
            skipQuote( ch );
        else if( ch == '\\' )  // Extra case, not in text
            nextChar( );
        else if( ch == '(' || ch == '[' || ch == '{' ||
                 ch == ')' || ch == ']' || ch == '}' )
            return ch;
    }
    return '\0';       // End of file
}

// Return current line number.
int Tokenizer::getLineNumber( ) const
{
    return currentLine;
}

// Return current line number.
int Tokenizer::getErrorCount( ) const
{
    return errors;
}

// Return indicates if ch can be part of a C++ identifier.
bool isIdChar( char ch )
{
    return ch == '_' || isalnum( ch );
}

// Return an identifier read from input stream.
// First character is already read into ch.
string Tokenizer::getRemainingString( )
{
    string result;

    for( result = ch; nextChar( ); result += ch )
        if( !isIdChar( ch ) )
        {
            putBackChar( );
            break;
        }

    return result;
}

// Return next identifier, skipping comments
// string constants, and character constants.
// Return "" if end of stream is reached.
string Tokenizer::getNextID( )
{
    while( nextChar( ) )
    {
        if( ch == '/' )
        {
            if( nextChar( ) )
            {
                if( ch == '*' )
                    skipComment( SLASH_STAR );
                else if( ch == '/' )
                    skipComment( SLASH_SLASH );
                else
                    putBackChar( );
            }
        }
        else if( ch == '\\' )
            nextChar( );
        else if( ch == '\'' || ch == '"' )
            skipQuote( ch );
        else if( !isdigit( ch ) && isIdChar( ch ) )
            return getRemainingString( );
    }
    return "";       // End of file
}



#ifdef SAFE_STL
    #include "EndConv.h"
#endif
