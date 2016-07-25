import java.io.Serializable;
import java.io.IOException;
import java.io.InputStream;
import java.io.FileInputStream;
import java.io.BufferedInputStream;
import java.util.zip.GZIPInputStream;
import java.io.ObjectInputStream;
import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.BufferedOutputStream;
import java.util.zip.GZIPOutputStream;
import java.io.ObjectOutputStream;


/**
 * The demo creates an array of Person, serializes it out to
 * a compressed file, closes the file, and then reads it back in
 * to prove that everything works.
 * Date and Person are static nested classes to avoid
 * any conflicts with other sample code. This does not
 * otherwise affect the code, so it was not shown this way
 * in the text.
 */
class DecoratorDemo
{
    /**
     * A simple Date class.
     */
    private static class Date implements Serializable
    {
        public Date( )
        {
            this( 1, 1, 2000 );
        }
    
        public Date( int m, int d, int y )
        {
            month = m;
            date = d;
            year = y;
        }
    
        public String toString( )
        {
            return month + "/" + date + "/" + year;
        }
    
        private int month;
        private int date;
        private int year;
    }

    /**
     * A simple Person class.
     */
    private static class Person implements Serializable
    {
        public Person( String n, Date b, Person mother, Person father )
        {
            name = n;
            birthDate = b;
            parents = new Person[ ] { mother, father };
        }
    
        public Person getFather( )
        {
            return parents[ 1 ];
        }
    
        public Person getMother( )
        {
            return parents[ 0 ];
        }
    
        public String getName( )
        {
            return name;
        }
    
        public Date getBirthDate( )
        {
            return birthDate;
        }
    
        public String toString( )
        {
            return "[" + name + " born on=" + birthDate
                    + "(mother=" + getMother( ).getName( )
                    + ") (father=" + getFather( ).getName( ) + ")" + "]";
        }
    
        public static final Person UNKNOWN = new Person( "????", new Date( ), null, null );
    
        private String name;
        private Date birthDate;
        private Person [ ] parents;
    }


    public static Person [ ] createArray( )
    {
        Person [ ] p = new Person[ 5 ];
        Date twinBday = new Date( 10, 2, 1950 );
        
        p[ 0 ] = new Person( "Joe", new Date( 3, 4, 1930 ), Person.UNKNOWN, Person.UNKNOWN );
        p[ 1 ] = new Person( "Sue", new Date( 5, 5, 1932 ), Person.UNKNOWN, Person.UNKNOWN );
        p[ 2 ] = new Person( "Bobby", twinBday, p[ 1 ], p[ 0 ] );
        p[ 3 ] = new Person( "Sue", twinBday, p[ 1 ], p[ 0 ] );
        p[ 4 ] = p[ 0 ];
        
        return p;
    }
    
    public static void printPersons( Person [ ] arr )
    {
        for( int i = 0; i < arr.length; i++ )
            System.out.println( arr[ i ] );
    }
    
    public static void main( String[ ] args )
    {
        // Write out some stuff
        ObjectOutputStream os = null;
        try
        {
            FileOutputStream fout = new FileOutputStream( "people.gzip" );
            BufferedOutputStream bout = new BufferedOutputStream( fout );
            GZIPOutputStream gout = new GZIPOutputStream( bout );
            os = new ObjectOutputStream( gout );
            Person [ ] people1 = createArray( );
            os.writeObject( people1 );
        }
        catch( IOException e )
        {
            System.err.println( "I/O problem: " + e );
            return;
        }
        finally
        {
            try
            {
                if( os != null )
                    os.close( );
            }   
            catch( IOException e )
            {
                System.err.println( "Can't close: " + e ); 
            } 
        }
        
        // Try to read it back in
        ObjectInputStream is = null;
        try
        {
            FileInputStream fin = new FileInputStream( "people.gzip" );
            BufferedInputStream bin = new BufferedInputStream( fin );
            GZIPInputStream gin = new GZIPInputStream( bin );
            is = new ObjectInputStream( gin );
            
            Person [ ] people2 = (Person [ ]) is.readObject( );
            printPersons( people2 );
            System.out.println( "Persons 0 and 4 same? "
                     + ( people2[ 0 ] == people2[ 4 ] ) );
            System.out.println( "Birthday 2 and 3 same? "
                     + ( people2[ 2 ].getBirthDate( ) == people2[ 3 ].getBirthDate( ) ) );
        }
        catch( ClassNotFoundException e )
        {
            System.err.println( "What's a Person? " + e );
        }
        catch( IOException e )
        {
            System.err.println( "I/O problem: " + e );
        }
        finally
        {
            try
            {
                if( is != null )
                    is.close( );
            }
            catch( IOException e )
            {
                System.err.println( "Can't close: " + e ); 
            }
        }    
    }
}
