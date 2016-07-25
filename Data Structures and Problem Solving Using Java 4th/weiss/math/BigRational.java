package weiss.math;

import java.math.BigInteger;

public class BigRational
{
    public static final BigRational ZERO = new BigRational( );
    public static final BigRational ONE = new BigRational( "1" );

    public BigRational( String str )
    {
        if( str.length( ) == 0 )
            throw new IllegalArgumentException( "Zero-length string" );

        // Check for "/"
        int slashIndex = str.indexOf( '/' );
        if( slashIndex == -1 )
        {
            // no denominator... use 1
            den = BigInteger.ONE;
            num = new BigInteger( str.trim( ) );
        }
        else
        {
            den = new BigInteger( str.substring( slashIndex + 1 ).trim( ) );
            num = new BigInteger( str.substring( 0, slashIndex ).trim( ) );
            check00( ); fixSigns( ); reduce( );
        }
    }

    private void check00( )
    {
        if( num.equals( BigInteger.ZERO ) && den.equals( BigInteger.ZERO ) )
            throw new IllegalArgumentException( "0/0" );
    }

    // Ensure that the denominator is positive
    private void fixSigns( )
    {
        if( den.compareTo( BigInteger.ZERO ) < 0 )
        {
            num = num.negate( );
            den = den.negate( );
        }
    }

    // Divide num and den by their gcd
    private void reduce( )
    {
        BigInteger gcd = num.gcd( den );
        num = num.divide( gcd );
        den = den.divide( gcd );
    }

    public BigRational( BigInteger n, BigInteger d )
    {
        num = n;
        den = d;
        check00( ); fixSigns( ); reduce( );
    }

    public BigRational( BigInteger n )
    {
        this( n, BigInteger.ONE );
    }

    public BigRational( )
    {
        this( BigInteger.ZERO );
    }

    public BigRational abs( )
    {
        return new BigRational( num.abs( ), den );
    }

    public BigRational negate( )
    {
        return new BigRational( num.negate( ), den );
    }

    public BigRational add( BigRational other )
    {
        BigInteger newNumerator =
                          num.multiply( other.den ).add(
                          other.num.multiply( den ) );
        BigInteger newDenominator =
                            den.multiply( other.den );

        return new BigRational( newNumerator, newDenominator );
    }

    public BigRational subtract( BigRational other )
    {
        return add( other.negate( ) );
    }

    public BigRational multiply( BigRational other )
    {
        BigInteger newNumer = num.multiply( other.num );
        BigInteger newDenom = den.multiply( other.den );

        return new BigRational( newNumer, newDenom );
    }

    public BigRational divide( BigRational other )
    {
        if( other.num.equals( BigInteger.ZERO ) && num.equals( BigInteger.ZERO ) )
            throw new ArithmeticException( "ZERO DIVIDE BY ZERO" );

        BigInteger newNumer = num.multiply( other.den );
        BigInteger newDenom = den.multiply( other.num );

        return new BigRational( newNumer, newDenom );
    }

    public boolean equals( Object other )
    {
        if( ! ( other instanceof BigRational ) )
            return false;

        BigRational rhs = (BigRational) other;

        return num.equals( rhs.num ) && den.equals( rhs.den );
    }

    public String toString( )
    {
        if( den.equals( BigInteger.ZERO ) )
            if( num.compareTo( BigInteger.ZERO ) < 0 )
                return "-infinity";
            else
                return "infinity";

        if( den.equals( BigInteger.ONE ) )
            return num.toString( );
        else
            return num + "/" + den;
    }

    private BigInteger num;  // only this can be neg
    private BigInteger den;
}
