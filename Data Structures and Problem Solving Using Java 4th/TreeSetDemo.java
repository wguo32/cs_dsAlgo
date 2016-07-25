import java.util.Iterator;

import weiss.util.Collection;
import weiss.util.Set;
import weiss.util.SortedSet;
import weiss.util.TreeSet;
import weiss.util.Collections;

public class TreeSetDemo
{
    public static void printCollection( Collection<String> c )
    {
        for( String str : c )
            System.out.println( str );
    }
    
    public static void main( String [ ] args )
    {
        Set<String> s = new TreeSet<String>( Collections.reverseOrder( ) );
        s.add( "joe" );
        s.add( "bob" );
        s.add( "hal" );
        printCollection( s );    // Figure 6.8
    }
}