import weiss.util.Comparator;
import weiss.util.Collection;
import weiss.util.Collections;
import weiss.util.Iterator;
import weiss.util.List;
import weiss.util.Set;
import weiss.util.ArrayList;
import weiss.util.LinkedList;
import weiss.util.TreeSet;
import weiss.util.HashSet;

/**
 * Illustrates use of Comparator for ignoring case distinctions.
 */
class IgnoreCase implements Comparator<String>
{
    public int compare( String s1, String s2 )
    {
        return s1.compareToIgnoreCase( s2 );
    }
}

/**
 * Test program for lots of collections.
 */
class IteratorTest
{
    /**
     * Print any collection.
     */
    public static <AnyType> void printCollection( Collection<AnyType> c )
    {
        for( AnyType val : c )
            System.out.print( val + " " );
        System.out.println( );
    }
        
    public static void main( String [ ] args )
    {
        List<String> l1 = new ArrayList<String>( );
        l1.add( "Jack" );
        l1.add( "Jill" );
        l1.add( "Bill" );
        
        List<String> l2 = new LinkedList<String>( l1 );
        Set<String>  s1 = new TreeSet<String>( l1 );
        Set<String>  s2 = new HashSet<String>( l1 );
        Set<String>  s3 = new TreeSet<String>( Collections.<String>reverseOrder( ) );
        Set<String>  s4 = new TreeSet<String>( new IgnoreCase( ) );
        
        s3.add( "joe" );
        s3.add( "bob" );
        s3.add( "hal" );
        
        s4.add( "Jeb!" );
        s4.add( "jill" );
        s4.add( "jack" );
        
        printCollection( l1 );   // Jack Jill Bill
        printCollection( l2 );   // Jack Jill Bill
        printCollection( s1 );   // Bill Jack Jill
        printCollection( s2 );   // Some unspecified order
        printCollection( s3 );   // joe hal bob
        printCollection( s4 );   // jack Jeb! jill
        
        List<SimpleStudent> stud1 = new ArrayList<SimpleStudent>( );
        stud1.add( new SimpleStudent( "Bob", 0 ) );
        stud1.add( new SimpleStudent( "Joe", 1 ) );
        stud1.add( new SimpleStudent( "Bob", 2 ) ); // duplicate
        
        Set<SimpleStudent>  stud2 = new TreeSet<SimpleStudent>( stud1 );  // will only have 2 items
        Set<SimpleStudent>  stud3 = new HashSet<SimpleStudent>( stud1 );  // will only have 2 items, if hashCode is
                                                                          // implemented. Otherwise will have 3
                                                                          // because duplicate will not be detected.          
        printCollection( stud1 ); // Bob Joe Bob
        printCollection( stud2 ); // Bob Joe
        printCollection( stud3 ); // Two items in unspecified order
    }
}


/**
 * Illustrates use of hashCode/equals for a user-defined class.
 * Also illustrates the compareTo function.
 * Students are ordered on basis of name only.
 */
class SimpleStudent implements Comparable<SimpleStudent>
{    
    String name;
    int id;    
        
    public SimpleStudent( String n, int i )
    {
        name = n;
        id = i;
    }

    public String toString( )
    {
        return name + " " + id;
    }
    
    public boolean equals( Object rhs )
    {
        if( rhs == null || getClass( ) != rhs.getClass( ) )
            return false;
                
        SimpleStudent other = (SimpleStudent) rhs;
        return name.equals( other.name );
    }
    
    public int compareTo( SimpleStudent other )
    {
        return name.compareTo( other.name );
    }

    public int hashCode( )
    {
        return name.hashCode( );
    }
}
