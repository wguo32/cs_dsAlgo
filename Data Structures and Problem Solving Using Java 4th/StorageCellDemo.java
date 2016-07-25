class StorageCell
{
    public Object get( )
    {
        return m.read( );
    }
    
    public void put( Object x )
    {
        m.write( x );
    }
    
    MemoryCell m = new MemoryCell( );
}

class StorageCellDemo
{
    public static void main( String [ ] args )
    {
        StorageCell m = new StorageCell( );
        m.put( "Hello" );
        System.out.println( m.get( ) );
    }
}
