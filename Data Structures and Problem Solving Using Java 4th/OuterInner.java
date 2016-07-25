class Outer<AnyType>
{
    public static class Inner<AnyType>
    {
    }

    public static class OtherInner
    {
        // cannot use AnyType here
    }
}

class OuterInner
{
    public static void main( String [ ] args )
    {
        Outer.Inner<String> t1  = new Outer.Inner<String>( );
        Outer.OtherInner t2 = new Outer.OtherInner( );
    }
}