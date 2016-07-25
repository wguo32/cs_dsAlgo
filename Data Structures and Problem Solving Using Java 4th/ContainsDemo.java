public class ContainsDemo
{
    public static <AnyType> boolean contains( AnyType [ ] a, AnyType x )
    {
        for( AnyType val : a )
            if( x.equals( val ) )
                return true;
            
        return false;    
    }
    
    public static void main( String [ ] args )
    {
        Object [ ] arr = 
        { "Hello", "world" 
        };
        
        System.out.println( contains( arr, "Hello" ) );
    }
}
