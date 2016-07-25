
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
    #include <vector>
    using namespace std;
#else
    #include "mystring.h"
    #include "vector.h"
    #include "StartConv.h"
#endif

// Abstract base class for shapes
//
// CONSTRUCTION: is not allowed; Shape is abstract
//
// ******************PUBLIC OPERATIONS**********************
// double area( )           --> Return the area (abstract)
// bool operator< ( rhs )   --> Compare 2 Shape objects by area
// void print( out = cout)  --> Standard print method

class Shape
{
  public:
    Shape( const string & shapeName = "" )
      : name( shapeName ) { }
    virtual ~Shape( ) { }

    virtual double area( ) const = 0;

    bool operator< ( const Shape & rhs ) const
      { return area( ) < rhs.area( ); }

    virtual void print( ostream & out = cout ) const
      { out << name << " of area " << area( ); }

  private:
    string name;
};

// Output routine for Shape.
ostream & operator<< ( ostream & out, const Shape & rhs )
{
    rhs.print( out );
    return out;
}

// Circle, Square, Rectangle class interfaces;
//     all based on Shape
//
// CONSTRUCTION: with (a) no initializer or (b) radius (for
//     circle), side length (for square), length and width
//     (for rectangle)
// ******************PUBLIC OPERATIONS**********************
// double area( )       --> Implements Shape pure virtual area

const double PI = 3.1415927;

class Circle : public Shape
{
  public:
    Circle( double rad = 0.0 )
      : Shape( "circle" ), radius( rad ) { }
    double area( ) const
      { return PI * radius * radius; }

  private:
    double radius;
};

class Rectangle : public Shape
{
  public:
    Rectangle( double len = 0.0, double wid = 0.0 )
      : Shape( "rectangle" ), length( len ), width( wid ) { }
    double area( ) const
      { return length * width; }

  private:
    double length;
    double width;
};

class Square : public Rectangle
{
  public:
    Square( double side = 0.0 )
      : Rectangle( side, side ) { }
};

// Create an appropriate Shape object based on input.
// The user types 'c', 's', or 'r' to indicate the shape
// and then provides dimensions when prompted.
// A zero-radius circle is returned for any error.
istream & operator>>( istream & in, Shape * & s )
{
    char ch;
    double d1, d2;

    in.get( ch );      // First character represents shape
    switch( ch )
    {
      case 'c':
        in >> d1;
        s = new Circle( d1 );
        break;

      case 'r':
        in >> d1 >> d2;
        s = new Rectangle( d1, d2 );
        break;

      case 's':
        in >> d1;
        s = new Square( d1 );
        break;

      case '\n':
        return in >> s;

      default:
        cerr << "Needed one of c, r, or s" << endl;
        s = new Circle;      // Radius is 0
        break;
    }

    return in;
}

struct PtrToShape
{
    Shape *ptr;

    bool operator< ( const PtrToShape & rhs ) const
      { return *ptr < *rhs.ptr; }
    const Shape & operator*( ) const
      { return *ptr; }
};

// Simple insertion sort.
template <class Comparable>
void insertionSort( vector<Comparable> & a )
{
    int j;

    for( int p = 1; p < a.size( ); p++ )
    {
        Comparable tmp = a[ p ];
        for( j = p; j > 0 && tmp < a[ j - 1 ]; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}

// main: read shapes and output in increasing order of area.
// Error checks omitted for brevity.
int main( )
{
    int numShapes;
    cout << "Enter number of shapes: ";
    cin >> numShapes;

      // Read the shapes
    vector<PtrToShape> array( numShapes );
    for( int i = 0; i < numShapes; i++ )
    {
        cout << "Enter a shape (c, r, or s with dimensions): ";
        cin >> array[ i ].ptr;
    }

    insertionSort( array );
    cout << "Sorted by increasing size:" << endl;
    for( int j = 0; j < numShapes; j++ )
        cout << *array[ j ] << endl;

    for( int k = 0; k < numShapes; k++ )
        delete array[ k ].ptr;

    return 0;
}


#ifdef SAFE_STL
    #include "EndConv.h"
#endif
