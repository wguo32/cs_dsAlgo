#ifndef RATIONAL_H
#define RATIONAL_H

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using std::ostream;
        using std::istream;     // Borland 5.0 has a bug
    #endif
#endif


// Rational class interface: support operations for rationals
//
// CONSTRUCTION: with (a) no initializer, or (b) an integer
//     that specifies the numerator, or (c) two integers
//     specifying numerator and denominator, or
//     (d) another Rational
//
// ******************PUBLIC OPERATIONS**********************
// =, +=, -=, /=, *=      --> Usual assignment
// +, -, /, *             --> Usual binary arithmetic
// <, <=, >, >=, ==, !=   --> Usual relational and equality
// ++, --, +, -, !        --> Usual prefix, postfix, unary
// >> and <<              --> Input and output
// double toDouble( )     --> Return double equivalent

typedef long IntType;    // Better method is in Chapter 3

class Rational
{
  public:
      // Constructors
    Rational( const IntType & numerator = 0 )
      : numer( numerator ), denom( 1 ) { }
    Rational( const IntType & numerator,
              const IntType & denominator )
      : numer( numerator ), denom( denominator )
            { fixSigns( ); reduce( ); }
    Rational( const Rational & rhs )
      : numer( rhs.numer ), denom( rhs.denom ) { }

      // Destructor
    ~Rational( ) { }

      // Assignment Ops (implementation in Figure 2.15)
    const Rational & operator= ( const Rational & rhs );
    const Rational & operator+=( const Rational & rhs );
    const Rational & operator-=( const Rational & rhs );
    const Rational & operator/=( const Rational & rhs );
    const Rational & operator*=( const Rational & rhs );

      // Math Binary Ops (implementation in Figure 2.16)
    Rational operator+( const Rational & rhs ) const;
    Rational operator-( const Rational & rhs ) const;
    Rational operator/( const Rational & rhs ) const;
    Rational operator*( const Rational & rhs ) const;

      // Relational & Equality Ops (implemented in Figure 2.17)
    bool operator< ( const Rational & rhs ) const;
    bool operator<=( const Rational & rhs ) const;
    bool operator> ( const Rational & rhs ) const;
    bool operator>=( const Rational & rhs ) const;
    bool operator==( const Rational & rhs ) const;
    bool operator!=( const Rational & rhs ) const;

      // Unary Operators (implemented in Figures 2.18 and 2.19)
    const Rational & operator++( );      // Prefix
    Rational operator++( int );          // Postfix
    const Rational & operator--( );      // Prefix
    Rational operator--( int );          // Postfix
    const Rational & operator+( ) const;
    Rational operator-( ) const;
    bool operator!( ) const;

      // Member Function
    double toDouble( ) const     // Do the division
      { return static_cast<double>( numer ) / denom; }

      // I/O friends: privacy is waived (see Figure 2.20)
    friend ostream & operator<< ( ostream & out,
                                  const Rational & value );
    friend istream & operator>> ( istream & in,
                                  Rational & value );

  private:
      // A rational number is represented by a numerator and
      // denominator in reduced form
    IntType numer;                  // The numerator
    IntType denom;                  // The denominator

    void fixSigns( );               // Ensures denom >= 0
    void reduce( );                 // Ensures lowest form
};


#endif
