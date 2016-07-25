#include <string.h>
#include <ctype.h>
#include "mystring.h"
#include "Except.h"

#include "StartConv.h"


string::string( const char * cstring )
{
    if( cstring == NULL )
        cstring = "";
    strLength = strlen( cstring );
    bufferLength = strLength + 1;
    buffer = new char[ bufferLength ];
    strcpy( buffer, cstring );
}

string::string( const string & str )
{
    strLength = str.length( );
    bufferLength = strLength + 1;
    buffer = new char[ bufferLength ];
    strcpy( buffer, str.buffer );
}

string::string( char ch )
{
    strLength = 1;
    bufferLength = strLength + 1;
    buffer = new char[ bufferLength ];
    buffer[ 0 ] = ch;
    buffer[ 1 ] = '\0';
}

const string & string::operator=( const string & rhs )
{
    if( this != &rhs )
    {
        if( bufferLength < rhs.length( ) + 1 )
        {
            delete [ ] buffer;
            bufferLength = rhs.length( ) + 1;
            buffer = new char[ bufferLength ];
        }
        strLength = rhs.length( );
        strcpy( buffer, rhs.buffer );
    }
    return *this;
}

const string & string::operator+=( const string & rhs )
{
    if( this == &rhs )
    {
        string copy( rhs );
        return *this += copy;
    }

    int newLength = length( ) + rhs.length( );
    if( newLength >= bufferLength )
    {
        bufferLength = 2 * ( newLength + 1 );

        char *oldBuffer = buffer;
        buffer = new char[ bufferLength ];
        strcpy( buffer, oldBuffer );
        delete [ ] oldBuffer;
    }

    strcpy( buffer + length( ), rhs.buffer );
    strLength = newLength;
    return *this;
}

char & string::operator[ ]( int k )
{
    if( k < 0 || k >= strLength )
        throw StringIndexOutOfBoundsException( k, length( ) );
    return buffer[ k ];
}

char string::operator[ ]( int k ) const
{
    if( k < 0 || k >= strLength )
        throw StringIndexOutOfBoundsException( k, length( ) );
    return buffer[ k ];
}

string operator+( const string & lhs, const string & rhs )
{
    string result = lhs;
    result += rhs;
    return result;
}

ostream & operator<<( ostream & out, const string & str )
{
    return out << str.c_str( );
}

istream & operator>>( istream & in, string & str )
{
    char ch;
    str = "";
    in >> ch;
    
    if( !in.fail( ) )
    {
        do
        {
            str += ch;
            in.get( ch );
        } while( !in.fail( ) && !isspace( ch ) );
        
        if( isspace( ch ) )    // put whitespace back on the stream
            in.putback( ch );     
    }
    
    return in;
}

istream & getline( istream & in, string & str, char delim )
{
    char ch;
    str = "";     // empty string, will build one char at-a-time
    
    while( in.get( ch ) && ch != delim )
        str += ch;
    
    return in;
}

istream & getline( istream & in, string & str )
{
    return getline( in, str, '\n' );
}

bool operator==( const string & lhs, const string & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) == 0;
}

bool operator!=( const string & lhs, const string & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) != 0;
}

bool operator<( const string & lhs, const string & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) < 0;
}

bool operator<=( const string & lhs, const string & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) <= 0;
}

bool operator>( const string & lhs, const string & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) > 0;
}

bool operator>=( const string & lhs, const string & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) >= 0;
}

#include "EndConv.h"
