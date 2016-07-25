class TestPrint
{
   public static void main( String [] args )
   {
      for( int i = 0; i < 20; i++ )
        System.out.println( (char)  ('0' + ( i % 10 ) ) );
   }
}
