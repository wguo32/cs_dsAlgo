// This demo illustrates that parameters are always statically deduced.

class Base
{
    public void foo( Base x )
    {
        System.out.println( "Base.Base" );
    }
    
    public void foo( Derived x )
    {
        System.out.println( "Base.Derived" );
    }
}

class Derived extends Base
{
    public void foo( Base x )
    {
        System.out.println( "Derived.Base" );
    }
    
    public void foo( Derived x )
    {
        System.out.println( "Derived.Derived" );
    }
}

class StaticParamsDemo
{
    public static void whichFoo( Base arg1, Base arg2 )
    {
        // It is guaranteed that we will call foo( Base )
        // Only issue is which class's version of foo( Base )
        // is called; the dynamic type of arg1 is used to decide.
        arg1.foo( arg2 );
    }

    public static void main( String [ ] args )
    {
        Base b = new Base( );
        Derived d = new Derived( );

        whichFoo( b, b );
        whichFoo( b, d );
        whichFoo( d, b );
        whichFoo( d, d );
    }
}