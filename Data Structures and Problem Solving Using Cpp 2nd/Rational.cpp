#include "Rational.h"

// n is guaranteed non-negative
IntType gcd1( const IntType & n, const IntType & m )
{
    if( n % m == 0 )
        return m;
    else
        return gcd1( m, n % m );
}

IntType gcd( const IntType & m, const IntType & n )
{
    if( m > 0 )
        return gcd1( n, m );
    else
        return gcd1( n, -m );
}
void Rational::fixSigns( )
{
    if( denom < 0 )
    {
        denom = -denom;
        numer = -numer;
    }
}

void Rational::reduce( )
{
    IntType d = 1;

    if( denom != 0 && numer != 0 )
        d = gcd( numer, denom );

    if( d > 1 )
    {
        numer /= d;
        denom /= d;
    }
}

const Rational & Rational::operator=( const Rational & rhs )
{
    if( this != &rhs )
    {
        numer = rhs.numer;
        denom = rhs.denom;
    }
    return *this;
}

const Rational & Rational::operator+=( const Rational & rhs )
{
    numer = numer * rhs.denom + rhs.numer * denom;
    denom = denom * rhs.denom;
    reduce( );

    return *this;
}

const Rational & Rational::operator-=( const Rational & rhs )
{
    numer = numer * rhs.denom - rhs.numer * denom;
    denom = denom * rhs.denom;
    reduce( );

    return *this;
}


const Rational & Rational::operator*=( const Rational & rhs )
{
    IntType newNumer = numer * rhs.numer;
    IntType newDenom = denom * rhs.denom;

    numer = newNumer;
    denom = newDenom;
    reduce( );

    return *this;
}

const Rational & Rational::operator/=( const Rational & rhs )
{
    IntType newNumer = numer * rhs.denom;
    IntType newDenom = denom * rhs.numer;

    numer = newNumer;
    denom = newDenom;

    fixSigns( );
    reduce( );

    return *this;
}

Rational Rational::operator+( const Rational & rhs ) const
{
    Rational answer( *this ); // Initialize answer with *this
    answer += rhs;            // Add the second operand
    return answer;            // Return answer by copy
}


Rational Rational::operator-( const Rational & rhs ) const
{
    Rational answer( *this ); // Initialize answer with *this
    answer -= rhs;            // Subtract the second operand
    return answer;            // Return answer by copy
}

Rational Rational::operator*( const Rational & rhs ) const
{
    Rational answer( *this ); // Initialize answer with *this
    answer *= rhs;            // Multiply the second operand
    return answer;            // Return answer by copy
}

Rational Rational::operator/( const Rational & rhs ) const
{
    Rational answer( *this ); // Initialize answer with *this
    answer /= rhs;            // Divide the second operand
    return answer;            // Return answer by copy
}


bool Rational::operator==( const Rational & rhs ) const
{
    return numer * rhs.denom == denom * rhs.numer;
}

bool Rational::operator!=( const Rational & rhs ) const
{
    return numer * rhs.denom != denom * rhs.numer;
}

bool Rational::operator<=( const Rational & rhs ) const
{
    return numer * rhs.denom <= denom * rhs.numer;
}

bool Rational::operator<( const Rational & rhs ) const
{
    return numer * rhs.denom < denom * rhs.numer;
}

bool Rational::operator>=( const Rational & rhs ) const
{
    return numer * rhs.denom >= denom * rhs.numer;
}

bool Rational::operator>( const Rational & rhs ) const
{
    return numer * rhs.denom > denom * rhs.numer;
}

const Rational & Rational::operator++( )  // Prefix form
{
    numer += denom;
    return *this;
}

Rational Rational::operator++( int )      // Postfix form
{
    Rational tmp = *this;
    numer += denom;
    return tmp;
}

const Rational & Rational::operator--( )  // Prefix form
{
    numer -= denom;
    return *this;
}

Rational Rational::operator--( int )      // Postfix form
{
    Rational tmp = *this;
    numer -= denom;
    return tmp;
}

bool Rational::operator!( ) const
{
    return !numer;
}

const Rational & Rational::operator+( ) const
{
    return *this;
}

Rational Rational::operator-( ) const
{
    return Rational( -numer, denom );
}

istream & operator>>( istream & in, Rational & value )
{
    in >> value.numer;
    value.denom = 1;

    char ch;
    in.get( ch );
    
    if( !in.eof( ) )
    {
        if( ch == '/' )
        {
            in >> value.denom;
            value.fixSigns( );
            value.reduce( );
        }
        else
            in.putback( ch );
    }

    return in;
}

ostream & operator<<( ostream & out, const Rational & value )
{
    if( value.denom != 0 )
    {
        out << value.numer;
        if( value.denom != 1 )
            out << '/' << value.denom;
        return out;
    }

      // Messy code for denom == 0
    if( value.numer == 0 )
        out << "indeterminate";
    else
    {
        if( value.numer < 0 )
            out << '-';
        out << "infinity";
    }
    return out;
}
