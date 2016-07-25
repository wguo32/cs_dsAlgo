
#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;      // Borland 5.0 has a bug
    #endif
#endif

class Derived;   // Incomplete declaration

class Base
{
  public:
    virtual void foo( const Base & x );      // METHOD A
    virtual void foo( const Derived & x );   // METHOD B
};

class Derived : public Base
{
  public:
    virtual void foo( const Base & x );      // METHOD C
    virtual void foo( const Derived & x );   // METHOD D
};

void whichFoo( Base & arg1, Base & arg2 )
{
    arg1.foo( arg2 );
}

void Base::foo( const Base & x )
{
    cout << "METHOD A" << endl;
}

void Base::foo( const Derived & x )
{
    cout << "METHOD B" << endl;
}

void Derived::foo( const Base & x )
{
    cout << "METHOD C" << endl;
}

void Derived::foo( const Derived & x )
{
    cout << "METHOD D" << endl;
}

int main( )
{
    Base b;
    Derived d;

    whichFoo( b, b );
    whichFoo( b, d );
    whichFoo( d, b );
    whichFoo( d, d );
    return 0;
}