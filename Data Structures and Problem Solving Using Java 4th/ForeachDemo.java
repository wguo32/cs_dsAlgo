import weiss.util.ArrayList;

public class ForeachDemo
{
	public static void main( String [ ] args )
	{
		String [ ] arr1 = { "Hello", "world" };

		ArrayList<String> arr2 = new ArrayList<String>( );
		arr2.add( "Hello" );
		arr2.add( "world" );

		for( String s : arr1 )
			System.out.println( s );
		
		for( String s : arr2 )
			System.out.println( s );
	}
}	