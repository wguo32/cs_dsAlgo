import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.TreeMap;
import java.util.Collection;
import java.util.Arrays;
import java.io.File;
import java.io.IOException;
import java.io.File;

public class DuplicateFinder
{
    public static void listDuplicates( List<String> coll )
    {
        Map<String,Integer> count = new TreeMap<String,Integer>( );

        for( String word : coll )
        {
            Integer occurs = count.get( word );
            if( occurs == null )
                count.put( word, 1 );
            else
                count.put( word, occurs + 1 );
        }

        for( Map.Entry<String,Integer> e : count.entrySet( ) )
            if( e.getValue( ) >= 2 )
                System.out.println( e.getKey( ) + " (" + e.getValue( ) + ")" );
    }


    public static void main( String [ ] args )
    {
        String [ ] arr = { "hello", "world", "hello", "if", "world" };
        List<String> lst = Arrays.asList( arr );

        listDuplicates( lst );
    }
}