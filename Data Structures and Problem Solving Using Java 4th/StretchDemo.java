class StretchDemo
{
    public static void stretchAll( Stretchable [ ] arr, double factor )
    {
        for( Stretchable s : arr )
            s.stretch( factor );
    }

    public static void main( String [ ] args )
    {
        Rectangle [ ] arr = { new Rectangle( 3.0, 2.0 ), new Rectangle( 4.0, 6.0 ) };

        System.out.println( "Before: " + ShapeDemo.totalArea( arr ) );
        stretchAll( arr, 2.0 );
        System.out.println( "After: " + ShapeDemo.totalArea( arr ) );
    }
}