
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
    using namespace std;
#else
    #include "vector.h"
    #include "StartConv.h"
#endif

class Subject;

class Observer
{
  public:
    virtual ~Observer( ) { }
    virtual void update( Subject *observee ) = 0;
};


class Subject
{
  public:
    virtual ~Subject( ) { }

    virtual void addObserver( Observer *obs )
    { 
        observers.push_back( obs );
    }

    virtual void removeObserver( Observer *obs )
    {
        for( int i = 0; i < observers.size( ); i++ )
            if( observers[ i ] == obs )
            {
                observers[ i ] = observers.back( );
                observers.pop_back( );
                i--;
            }
    }

    virtual void notifyAll( )
    {
        for( int i = 0; i < observers.size( ); i++ )
            observers[ i ]->update( this );
    }

  private:
    vector<Observer *> observers;
};


// Timer class: tick method calls notify.
class Timer : public Subject
{
  public:
    void tick( )
      { notifyAll( ); }
};

// Echo class: this in an observer.
// It is constructed with a Timer object; when
// the Timer object ticks, update is
// automatically called.
class Echo : public Observer
{
  public:
    Echo( int id, Timer *t ) : myId( id ), observee( t )
      { observee->addObserver( this ); }

    ~Echo( )
      { observee->removeObserver( this ); }

    void update( Subject *s )
      { if( observee == s ) cout << myId << endl; }

  private:
    int myId;
    Subject *observee;
};


void testEcho12( Timer & t )
{
    Echo e1( 1, &t );
    Echo e2( 2, &t );

    cout << "Expecting 1 and 2 to respond." << endl;
    t.tick( );
    cout << "1 and 2 disappear." << endl;
}

int main( )
{
    Timer t;
    Timer other;

    testEcho12( t );   // 1 and 2 should respond

    Echo e3( 3, &t );
    Echo e4( 4, &t );
    Echo e5( 5, &other );  // registered with other, not t

    cout << "Only 3 and 4 are currently observable." << endl;
    cout << "Expecting 3 and 4 to respond." << endl;
    t.tick( );

    return 0;
}



#ifdef SAFE_STL
    #include "EndConv.h"
#endif
