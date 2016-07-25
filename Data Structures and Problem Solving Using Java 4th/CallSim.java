import weiss.util.Random;
import weiss.util.PriorityQueue;

// CallSim clas interface: run a simulation
//
// CONSTRUCTION: with three parameters: the number of
//     operators, the average connect time, and the
//     interarrival time
//
// ******************PUBLIC OPERATIONS*********************
// void runSim( )       --> Run a simulation

/**
 * The CallSim class.
 */
public class CallSim
{
    /**
     * The event class.
     * Implements the Comparable interface
     * to arrange events by time of occurrence.
     */
    private static class Event implements Comparable<Event>
    {
        static final int DIAL_IN = 1;
        static final int HANG_UP = 2;

        public Event( )
        {
            this( 0, 0, DIAL_IN );
        }

        public Event( int name, int tm, int type )
        {
            who  = name;
            time = tm;
            what = type;
        }

        public int compareTo( Event rhs )
        {
            return time - rhs.time;
        }
      
        int who;        // the number of the user
        int time;       // when the event will occur
        int what;       // DIAL_IN or HANG_UP
    }

    /**
     * Constructor.
     * @param operator number of operators.
     * @param avgLen averge length of a call.
     * @param callIntrvl the average time between calls.
     */
    public CallSim( int operators, double avgLen, int callIntrvl )
    {
        eventSet           = new PriorityQueue<Event>( );
        availableOperators = operators;
        avgCallLen         = avgLen;
        freqOfCalls        = callIntrvl;
        r                  = new Random( );
        nextCall( freqOfCalls );  // Schedule first call
    }

    private Random r;                       // A random source
    private PriorityQueue<Event> eventSet;  // Pending events

        // Basic parameters of the simulation
    private int availableOperators;   // Number of available operators
    private double avgCallLen;        // Length of a call
    private int freqOfCalls;          // Interval between calls

        // Used by nextCall only
    private int userNum = 0;
    private int nextCallTime = 0;

    /**
     * Place a new DIAL_IN event into the event queue.
     * Then advance the time when next DIAL_IN event will occur.
     * In practice, we would use a random number to set the time.
     */
    private void nextCall( int delta )
    {
        Event ev = new Event( userNum++, nextCallTime, Event.DIAL_IN );
        eventSet.add( ev );
        nextCallTime += delta;
    }


    /**
     * Run the simulation until stoppingTime occurs.
     * Print output as in Figure 13.4.
     */
    public void runSim( long stoppingTime )
    {
        Event e = null;
        int howLong;

        while( !eventSet.isEmpty( ) )
        {
            e = eventSet.remove( );

            if( e.time > stoppingTime )
                break;

            if( e.what == Event.HANG_UP )    // HANG_UP
            {
                availableOperators++;
                System.out.println( "User " + e.who +
                                    " hangs up at time " + e.time );
            }
            else                      // DIAL_IN
            {
                System.out.print(  "User " + e.who +
                                    " dials in at time " + e.time + " " );
                if( availableOperators > 0 )
                {
                    availableOperators--;
                    howLong = r.nextPoisson( avgCallLen );
                    System.out.println(  "and connects for "
                                         + howLong + " minutes" );
                    e.time += howLong;
                    e.what = Event.HANG_UP;
                    eventSet.add( e );
                }
                else
                    System.out.println( "but gets busy signal" );

                nextCall( freqOfCalls );
            }
        }
    }

    /**
     * Quickie main for testing purposes.
     */
    public static void main( String [ ] args )
    {
        CallSim s = new CallSim( 3, 5.0, 1 );
        s.runSim( 20 );
    }
}
