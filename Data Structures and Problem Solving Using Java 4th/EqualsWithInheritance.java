class BaseClass
{
    public BaseClass( int i )
    {
        x = i;
    }
    
    public boolean equals( Object rhs )
    {
        if( EqualsWithInheritance.BROKEN )
        {
            // This is the wrong test (ok if final class)
            if( !( rhs instanceof BaseClass ) )
              return false;
        }
        else
        {
            // This is the correct test, if class is not final
            if( rhs == null || getClass( ) != rhs.getClass( ) )
                return false;
        }    
         
        return x == ( (BaseClass) rhs ).x;   
    }
        
    int x;
}

class DerivedClass extends BaseClass
{
    public DerivedClass( int i, int j )
    {
        super( i );
        y = j;
    }
    
    public boolean equals( Object rhs )
    {
        if( EqualsWithInheritance.BROKEN )
        {
            // This is the wrong test.
            // Test is not needed if getClass() done in superclass equals
            if( !( rhs instanceof DerivedClass ) )
               return false;
        }   

        return super.equals( rhs ) && y == ( (DerivedClass) rhs ).y;   
    }
        
    int y;
}

public class EqualsWithInheritance
{
    /**
     * Change this variable. If true, equals is not
     * symmetric. If false, it is.
     */
    public static final boolean BROKEN = false;
    
    public static void main( String [ ] args )
    {
        BaseClass a = new BaseClass( 5 );
        DerivedClass b = new DerivedClass( 5, 8 );
        DerivedClass c = new DerivedClass( 5, 8 );
    
        System.out.println( "b.equals(c): " + b.equals( c ) );
        System.out.println( "a.equals(b): " + a.equals( b ) );
        System.out.println( "b.equals(a): " + b.equals( a ) );
    }
}
