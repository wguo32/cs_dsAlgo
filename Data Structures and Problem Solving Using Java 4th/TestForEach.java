public class TestForEach
{
	public static void main( String [] args )
	{
		int [ ] arr = new int[ 10 ];
		
		for( int current : arr )
			current = 5;
		
		for( int current : arr )
			System.out.println( current );
	}
}	
