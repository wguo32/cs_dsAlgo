public class RSA
{
    /**
     * Sample of how RSA works.
     * Note that n * n should not overflow a long
     * This limits x*y to about 2^15.
     */
    public static void main( String [ ] args )
    {
        long x = 25000;
        long y = 30000;
        long message = 37373737;

        long p, q, n, nPrime, e, d;

        for( p = x; !Numerical.isPrime( p ); p++ )
            ;
        System.out.println( "p: " + p );
        for( q = y + 2; !Numerical.isPrime( q ); q++ )
            ;
        System.out.println( "q: " + q );

        n = p * q;
        System.out.println( "n: " + n );

        nPrime = ( p - 1 ) * ( q - 1 );
        System.out.println( "nPrime: " + nPrime );

        for( e = nPrime / 10; Numerical.gcd( e, nPrime ) != 1; e++ )
            ;
        System.out.println( "e: " + e );

        d = Numerical.inverse( e, nPrime );
        System.out.println( "d: " + d );

	    System.out.println( "Verify inverse: " + ( e * d % ( nPrime ) ) );

	    System.out.println( "message: " + message );
        long code = Numerical.power( message, e, n ); 
        long decode = Numerical.power( code, d, n );

        System.out.println( "Code: " + code );
        System.out.println( "Decode: " + decode );
        if( message != decode )
            System.out.println( "OOPS: " );
        else
	        System.out.println( "Success!!!!" );
    }
}
