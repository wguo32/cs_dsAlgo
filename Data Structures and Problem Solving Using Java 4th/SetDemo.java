import weiss.util.Collection;
import java.util.Iterator;
import weiss.util.Set;
import weiss.util.SortedSet;
import weiss.util.TreeSet;
import weiss.util.HashSet;
import weiss.util.Collections;

class SetDemo
{
    public static <AnyType> void printCollection( Collection<AnyType> c )
    {
        Iterator<AnyType> itr = c.iterator( );
        while( itr.hasNext( ) )
        {
            System.out.println( itr.next( ) );
            itr.remove( );
        }
    }
    
    public static void main( String [ ] args )
    {
		
        Set<String> s2 = new HashSet<String>( );
        s2.add( "joe" );
        s2.add( "bob" );
        s2.add( "hal" );
        printCollection( s2 );   
        System.out.println( "Now it is: " );
        printCollection( s2 );
		
		/*
        Set<String> s1 = new TreeSet<String>( Collections.<String>reverseOrder( ) );
        s1.add( "joe" );
        s1.add( "bob" );
        s1.add( "hal" );
        printCollection( s1 );    // Figure 6.8
        System.out.println( "Now it is: " );
        printCollection( s1 );
		*/
    }
}