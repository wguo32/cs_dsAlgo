import weiss.util.Comparator;

class CompareTestInner2
{
    public static <AnyType> AnyType findMax( AnyType [ ] a, Comparator<? super AnyType> cmp )
    {
        int maxIndex = 0;
        for( int i = 1; i < a.length; i++ )
            if( cmp.compare( a[ i ], a[ maxIndex ] ) > 0 )
                maxIndex = i;
        
        return a[ maxIndex ];
    }
    

    public static void main( String [ ] args )
    {
        SimpleRectangle [ ] rects = new SimpleRectangle[ 4 ];
        rects[ 0 ] = new SimpleRectangle( 1, 10 );
        rects[ 1 ] = new SimpleRectangle( 20, 1 );
        rects[ 2 ] = new SimpleRectangle( 4, 6 );
        rects[ 3 ] = new SimpleRectangle( 5, 5 );

    
        class OrderRectByWidth implements Comparator<SimpleRectangle>
        {
            public int compare( SimpleRectangle r1, SimpleRectangle r2 )
            {
                return r1.getWidth( ) - r2.getWidth( );
            }
        }

        class OrderRectByArea implements Comparator<SimpleRectangle>
        {
            public int compare( SimpleRectangle r1, SimpleRectangle r2 )
            {
                return r1.getWidth( ) * r1.getLength( ) -
                       r2.getWidth( ) * r2.getLength( );
            }
        }

    
        System.out.println( "MAX WIDTH: " + findMax( rects, new OrderRectByWidth( ) ) );
        System.out.println( "MAX AREA: " + findMax( rects, new OrderRectByArea( ) ) );
    }
}
