public class MinTest
{
    public static void main( String [ ] args )
    {
        int a = 3;
        int b = 7;

        System.out.println( min( a, b ) );
    }

    // Function definition
    public static int min( int x, int y )
    {
        return x < y ? x : y;
    }
}
