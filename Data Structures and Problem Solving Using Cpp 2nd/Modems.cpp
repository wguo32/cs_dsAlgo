// ModemSim class interface: run a simulation
//
// CONSTRUCTION: with (a) three parameters: the number of
//     modems, the average connect time, and the
//     inter-arrival time.
//
// ******************PUBLIC OPERATIONS*********************
// void runSim( )       --> Run a simulation


#include <limits.h>
#include <time.h>
#include <stdlib.h>

#include "Random.h"

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;      // Borland 5.0 has a bug
    #endif
#endif
    
#ifndef SAFE_STL
    #include <vector>
    #include <queue>
    #include <functional>
    using namespace std;
#else
    #include "vector.h"
    #include "queue.h"
    #include "functional.h"
    #include "StartConv.h"
#endif



class Event
{
    enum { DIAL_IN = 1, HANGUP = 2 };
  public:
    Event( int name = 0, int tm = 0, int type = DIAL_IN )
      : time( tm ), who( name ), what( type ) { }

    bool operator> ( const Event & rhs ) const
      { return time > rhs.time; }

    friend class ModemSim;

  private:
    int who;        // the number of the user
    int time;       // when the event will occur
    int what;       // DIAL_IN or HANGUP
};

typedef priority_queue<Event,vector<Event>,greater<Event> > PQ;

class ModemSim
{
  public:
    ModemSim( int modems, double avgLen, int callIntrvl );

      // Add a call to eventSet at the current time,
      // and schedule one for delta in the future.
    void nextCall( int delta );

      // Run the simulation
    void runSim( int stoppingTime = INT_MAX );

  private:
    Random r;                       // A random source
    PQ eventSet;                    // Pending events

      // Basic parameters of the simulation
    int freeModems;                 // Number of modems unused
    const double avgCallLen;        // Length of a call
    const int freqOfCalls;          // Interval between calls
};

// Constructor for ModemSim.
ModemSim::ModemSim( int modems, double avgLen, int callIntrvl )
  : freeModems( modems ), avgCallLen( avgLen ),
    freqOfCalls( callIntrvl ), r( (int) time( 0 ) )
{
    nextCall( freqOfCalls );  // Schedule first call
}

// Place a new DIAL_IN event into the event queue.
// Then advance the time when next DIAL_IN event will occur.
// In practice, we would use a random number to set the time.
void ModemSim::nextCall( int delta )
{
    static int nextCallTime = 0;
    static int userNum = 0;

    eventSet.push( Event( userNum++, nextCallTime ) );
    nextCallTime += delta;
}

// Run the simulation until stopping time occurs.
// Print output as in Figure 14.4.
void ModemSim::runSim( int stoppingTime )
{
    static Event e;
    int howLong;

    while( !eventSet.empty( ) )
    {
        e = eventSet.top( );
        eventSet.pop( );
        if( e.time > stoppingTime )
            break;

        if( e.what == Event::HANGUP )    // HANGUP
        {
            freeModems++;
            cout << "User " << e.who << " hangs up at time "
                << e.time << endl;
        }
        else                             // DIAL_IN
        {
            cout << "User " << e.who << " dials in at time "
                << e.time << " ";
            if( freeModems > 0 )
            {
                freeModems--;
                howLong = r.poisson( avgCallLen );
                cout << "and connects for "
                    << howLong << " minutes" << endl;
                e.time += howLong;
                e.what = Event::HANGUP;
                eventSet.push( e );
            }
            else
                cout << "but gets busy signal" << endl;

            nextCall( freqOfCalls );
        }
    }
}


// Simple main to test ModemSim class.
int main( )
{
    int numModems;
    int totalTime;
    double avgConnectTime;
    int dialInFrequency;

    cout << "Enter number of modems, length of simulation,\n"
         << " average connect time, how often calls occur: ";

    cin >> numModems >> totalTime >>
                        avgConnectTime >> dialInFrequency;

    ModemSim s( numModems, avgConnectTime, dialInFrequency );
    s.runSim( totalTime );

    return 0;
}



#ifdef SAFE_STL
    #include "EndConv.h"
#endif
