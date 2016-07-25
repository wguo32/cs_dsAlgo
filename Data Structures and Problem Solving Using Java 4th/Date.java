// Minimal Date class that illustrates some Java features
// No error checks or javadoc comments

public class Date
{
        // Zero-parameter constructor
    public Date( )
    {
        month = 1;
        day = 1;
        year = 1998;
    }

        // Three-parameter constructor
    public Date( int theMonth, int theDay, int theYear )
    {
        month = theMonth;
        day   = theDay;
        year  = theYear;
    }

        // Return true if two equal values
    public boolean equals( Object rhs )
    {
        if( ! ( rhs instanceof Date ) )
            return false;
        Date rhDate = ( Date ) rhs;
        return rhDate.month == month && rhDate.day == day &&
               rhDate.year == year;
    }

        // Conversion to String
    public String toString( )
    {
        return month + "/" + day + "/" + year;
    }

        // Fields
    private int month;
    private int day;
    private int year;

    // Sample main
    public static void main( String [ ] args )
    {
        Date d1 = new Date( );
        Date d2 = new Date( 1, 1, 1998 );
        Date d3 = new Date( 1, 1, 1999 );

        System.out.println( "Date 1: " + d1 );
        System.out.println( "Date 2: " + d2 );
        System.out.println( "Date 3: " + d3 );
        System.out.println( "Date1==Date2?: " + d1.equals( d2 ) );
        System.out.println( "Date1==Date3?: " + d1.equals( d3 ) );
    }
}
