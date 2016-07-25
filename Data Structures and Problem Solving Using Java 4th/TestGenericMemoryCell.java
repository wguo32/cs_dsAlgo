public class TestGenericMemoryCell
{
    public static void main( String [ ] args )
    {
        GenericMemoryCell<String> m = new GenericMemoryCell<String>( );

        m.write( "57" );
        String val = m.read( );
        System.out.println( "Contents are: " + val );
    }
}
