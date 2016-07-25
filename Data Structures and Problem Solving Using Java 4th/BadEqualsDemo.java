final class SomeClass
{
    public SomeClass( int i )
    {
        id = i;
    }
    
    public boolean sameVal( Object other )
    {
        return other instanceof SomeClass && equals( other );
    }
    
    /**
     * This is a bad implementation!
     * other has the wrong type, so this does
     * not override Object's equals.
     */
    public boolean equals( SomeClass other )
    {
        return other != null && id == other.id;
    }
    
    private int id;
}

class BadEqualsDemo
{ 
    public static void main( String [ ] args )
    {
        SomeClass obj1 = new SomeClass( 4 );
        SomeClass obj2 = new SomeClass( 4 );
        
        System.out.println( "obj1.equals(obj2): " + obj1.equals( obj2 ) );
        System.out.println( "obj1.sameVal(obj2): " + obj1.sameVal( obj2 ) );
    }
}
