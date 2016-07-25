import java.io.File;

// Program that lists files in a directory,
// recursively processing subdirectories.
// It then outputs the total number of bytes used to
// store the directory.
public class FileSystem
{
      // Output file name with indentation
    public static void printName( String name, int depth )
    {
        for( int i = 0; i < depth; i++ )
            System.out.print( "   " );
        System.out.println( name );
    }

      // Public driver to list all files in directory
    public static void listAll( File dir )
    {
        listAll( dir, 0 );
    }

      // Recursive method to list all files in directory
    private static void listAll( File dir, int depth )
    {
        printName( dir.getName( ), depth );

        if( dir.isDirectory( ) )
            for( File child : dir.listFiles( ) )
                listAll( child, depth + 1 );
    }

    public static long size( File dir )
    {
        long totalSize = dir.length( );

        if( dir.isDirectory( ) )
            for( File child : dir.listFiles( ) )
                totalSize += size( child );

        return totalSize;
    }

      // Simple main to list all files in current directory
    public static void main( String [ ] args )
    {
        String dirName;

        if( args.length == 0 )
            dirName = ".";
        else
            dirName = args[ 0 ];

        File dir = new File( dirName );
        listAll( dir );
        System.out.println( "Total bytes: " + size( dir ) );
    }
}
