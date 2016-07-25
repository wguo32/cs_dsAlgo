package weiss.nonstandard;

// DisjointSets class
//
// CONSTRUCTION: with int representing initial number of sets
//
// ******************PUBLIC OPERATIONS*********************
// void union( root1, root2 ) --> Merge two sets
// int find( x )              --> Return set containing x
// ******************ERRORS********************************
// Error checking or parameters is performed

/**
 * Disjoint set class. (Package friendly so not used accidentally)
 * Does not use union heuristics or path compression.
 * Elements in the set are numbered starting at 0.
 * @author Mark Allen Weiss
 * @see DisjointSetsFast
 */
class DisjointSetsSlow
{
    /**
     * Construct the disjoint sets object.
     * @param numElements the initial number of disjoint sets.
     */
    public DisjointSetsSlow( int numElements )
    {
        s = new int [ numElements ];
        for( int i = 0; i < s.length; i++ )
            s[ i ] = -1;
    }

    /**
     * Union two disjoint sets.
     * root1 and root2 are distinct and represent set names.
     * @param root1 the root of set 1.
     * @param root2 the root of set 2.
     * @throws IllegalArgumentException if root1 or root2
     * are not distinct roots.
     */
    public void union( int root1, int root2 )
    {
        assertIsRoot( root1 );
        assertIsRoot( root2 );
        if( root1 == root2 )
            throw new IllegalArgumentException( "Union: root1 == root2 " + root1 );
            
        s[ root2 ] = root1;
    }

    /**
     * Perform a find.
     * @param x the element being searched for.
     * @return the set containing x.
     * @throws IllegalArgumentException if x is not valid.
     */
    public int find( int x )
    {
        assertIsItem( x );
        if( s[ x ] < 0 )
            return x;
        else
            return find( s[ x ] );
    }

    private void assertIsRoot( int root )
    {
        assertIsItem( root );
        if( s[ root ] >= 0 )
            throw new IllegalArgumentException( "Union: " + root + " not a root" );
    }
    
    private void assertIsItem( int x )
    {
        if( x < 0 || x >= s.length )
            throw new IllegalArgumentException( "Disjoint sets: " + x + " not an item" );       
    }
    
    private int [ ] s;


    // Test main; all finds on same output line should be identical
    public static void main( String [ ] args )
    {
        int numElements = 128;
        int numInSameSet = 16;

        DisjointSetsSlow ds = new DisjointSetsSlow( numElements );
        int set1, set2;

        for( int k = 1; k < numInSameSet; k *= 2 )
        {
            for( int j = 0; j + k < numElements; j += 2 * k )
            {
                set1 = ds.find( j );
                set2 = ds.find( j + k );
                ds.union( set1, set2 );
            }
        }

        for( int i = 0; i < numElements; i++ )
        {
            System.out.print( ds.find( i )+ "*" );
            if( i % numInSameSet == numInSameSet - 1 )
                System.out.println( );
        }
        System.out.println( );
    }
}
