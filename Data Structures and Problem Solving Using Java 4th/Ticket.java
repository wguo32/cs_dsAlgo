class Ticket
{
    public Ticket( )
    {
        System.out.println( "Calling constructor" );
        serialNumber = ++ticketCount;
    }
    
    public int getSerial( )
    {
        return serialNumber;
    }
    
    public String toString( )
    {
        return "Ticket #" + getSerial( );
    }
    
    public static int getTicketCount( )
    {
        return ticketCount;
    }
    
    private int serialNumber;
    private static int ticketCount = 0;
}

class TestTicket
{
    public static void main( String [ ] args )
    {    
        Ticket t1;
        Ticket t2;
        
        System.out.println( "Ticket count is " + Ticket.getTicketCount( ) );
        
        t1 = new Ticket( );
        t2 = new Ticket( );
        
        System.out.println( "Ticket count is " + Ticket.getTicketCount( ) );
            
        System.out.println( t1.getSerial( ) );
        System.out.println( t2.getSerial( ) );
    }
}
