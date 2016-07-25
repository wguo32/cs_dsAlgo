
// Program that illustrates hiding of methods using inheritance.

class Base
{
  public:
    virtual void bar( );           // METHOD A
};

class Derived : public Base
{
  public:
    void bar( int x );             // METHOD B
};

void test( Base & arg1, Derived & arg2 )
{
    arg1.bar( );      // Compiles, as expected.
    arg1.bar( 4 );    // Does not compile, as expected.
    arg2.bar( 4 );    // Compiles, as expected.
    arg2.bar( );      // Does not compile. Not expected.

    Base & tmp = arg2; tmp.bar( );   // Legal!!
}

int main( )
{
    return 0;
}