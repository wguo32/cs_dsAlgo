#pragma warning (disable: 4786)
#pragma warning (disable: 4068)
#pragma warn -csu

#include <limits.h>
#include "Except.h"
#include "PairingHeap.h"

#ifdef USE_DOT_H
    #include <iostream.h>
    #include <fstream.h>
    #define USE_STR_DOT_H
#else
    #include <fstream>
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;
    #else
        #define USE_STR_DOT_H
    #endif
#endif


#ifndef SAFE_STL
    #include <map>
    #include <vector>
    #include <string>
    #include <queue>
    #include <functional>
    #include <list>
    using namespace std;
#else
    #include "map.h"
    #include "vector.h"
    #include "string.h"
    #include "queue.h"
    #include "functional.h"
    #include "list.h"
    #include "StartConv.h"
#endif


#ifdef __GNUC__
    #include <strstream.h>
    #define USE_STR_DOT_H
#else
#ifdef unix
    #include <strstream.h>
    #define USE_STR_DOT_H
#else
#ifdef USE_STR_DOT_H
    #include <strstrea.h>
    #include "getline.cpp"
#else
    #include <sstream>
    #include "getline.cpp"
#endif
#endif
#endif

struct Vertex;

// Basic item stored in adjacency list.
struct Edge
{
                     // First vertex in edge is implicit
    Vertex  *dest;   // Second vertex in edge
    double   cost;   // Edge cost

    Edge( Vertex *d = 0, double c = 0.0 )
      : dest( d ), cost( c ) { }
};


// Structure stored in priority queue for Dijkstra's algorithm.
struct Path
{
    Vertex *dest;   // w
    double  cost;   // d(w)

    Path( Vertex *d = 0, double c = 0.0 )
      : dest( d ), cost( c ) { }

    bool operator> ( const Path & rhs ) const
      { return cost > rhs.cost; }
    bool operator< ( const Path & rhs ) const
      { return cost < rhs.cost; }
};

static const int INFINITY = INT_MAX;

// Basic info for each vertex.
struct Vertex
{
    string        name;    // Vertex name
    vector<Edge>  adj;     // Adjacent vertices (and costs)
    double        dist;    // Cost
    Vertex       *prev;    // Previous vertex on shortest path
    int           scratch; // Extra variable used in algorithm

    Vertex( const string & nm ) : name( nm )
      { reset( ); }

    void reset( )
      { dist = INFINITY; prev = NULL; pos = NULL; scratch = 0; }

    PairingHeap<Path>::Position pos; // Used for disjktra2 (Chapter 23)
};


// Graph class interface: evaluate shortest paths.
//
// CONSTRUCTION: with no parameters.
//
// ******************PUBLIC OPERATIONS**********************
// void addEdge( string v, string w, double cvw )
//                              --> Add additional edge
// void printPath( string w )   --> Print path after alg is run
// void unweighted( string s )  --> Single-source unweighted
// void dijkstra( string s )    --> Single-source weighted
// void negative( string s )    --> Single-source negative weighted
// void acyclic( string s )     --> Single-source acyclic
// ******************ERRORS*********************************
// Some error checking is performed to make sure graph is ok,
// and to make sure graph satisfies properties needed by each
// algorithm.  GraphException is thrown if error is detected.

class Graph
{
  public:
    Graph( ) { }
    ~Graph( );
    void addEdge( const string & sourceName, const string & destName, double cost );
    void printPath( const string & destName ) const;
    void unweighted( const string & startName );
    void dijkstra( const string & startName );
    void dijkstra2( const string & startName );   // Chapter 23
    void negative( const string & startName );
    void acyclic( const string & startName );
      
  private:
    Vertex * getVertex( const string & vertexName );
    void printPath( const Vertex & dest ) const;
    void clearAll( );

    typedef map<string,Vertex *,less<string> > vmap;

      // Copy semantics are disabled; these make no sense.
    Graph( const Graph & rhs ) { }
    const Graph & operator= ( const Graph & rhs )
      { return *this; }

    vmap vertexMap;
};


// Add a new edge to the graph.
void Graph::addEdge( const string & sourceName, const string & destName, double cost )
{
    Vertex * v = getVertex( sourceName );
    Vertex * w = getVertex( destName );
    v->adj.push_back( Edge( w, cost ) );
}

// Driver routine to handle unreachables and print total cost.
// It calls recursive routine to print shortest path to
// destNode after a shortest path algorithm has run.
void Graph::printPath( const string & destName ) const
{
    vmap::const_iterator itr = vertexMap.find( destName );

    if( itr == vertexMap.end( ) )
        throw GraphException( "Destination vertex not found" );

    const Vertex & w = *(*itr).second;
    if( w.dist == INFINITY )
        cout << destName << " is unreachable";
    else
    {
        cout << "(Cost is: " << w.dist << ") ";
        printPath( w );
    }
    cout << endl;
}

// If vertexName is not present, add it to vertexMap.
// In either case, return (a pointer to) the Vertex.
Vertex * Graph::getVertex( const string & vertexName )
{
    vmap::iterator itr = vertexMap.find( vertexName );

    if( itr == vertexMap.end( ) )
    {
        Vertex *newv = new Vertex( vertexName );
        vertexMap[ vertexName ] = newv;
        return newv;
    }
    return (*itr).second;
}

// Recursive routine to print shortest path to dest
// after running shortest path algorithm. The path
// is known to exist.
void Graph::printPath( const Vertex & dest ) const
{
    if( dest.prev != NULL )
    {
        printPath( *dest.prev );
        cout << " to ";
    }
    cout << dest.name;
}

// Initialize the vertex output info prior to running
// any shortest path algorithm.
void Graph::clearAll( )
{
    for( vmap::iterator itr = vertexMap.begin( ); itr != vertexMap.end( ); ++itr )
        (*itr).second->reset( );
}

// Destructor: cleans up the Vertex structs.
Graph::~Graph( )
{
    for( vmap::iterator itr = vertexMap.begin( ); itr != vertexMap.end( ); ++itr )
        delete (*itr).second;
}

// Single-source unweighted shortest-path algorithm.
void Graph::unweighted( const string & startName )
{
    vmap::iterator itr = vertexMap.find( startName );

    if( itr == vertexMap.end( ) )
        throw GraphException( startName + " is not a vertex in this graph" );

    clearAll( );
    Vertex *start = (*itr).second;
    list<Vertex *> q;
    q.push_back( start ); start->dist = 0;

    while( !q.empty( ) )
    {
        Vertex *v = q.front( ); q.pop_front( );

        for( int i = 0; i < v->adj.size( ); i++ )
        {
            Edge e = v->adj[ i ];
            Vertex *w = e.dest;
            if( w->dist == INFINITY )
            {
                w->dist = v->dist + 1;
                w->prev = v;
                q.push_back( w );
            }
        }
    }
}

// Single-source weighted shortest-path algorithm.
void Graph::dijkstra( const string & startName )
{
    priority_queue<Path, vector<Path>, greater<Path> > pq;
    Path vrec;     // Stores the result of a deleteMin

    vmap::iterator itr = vertexMap.find( startName );


    clearAll( );
    if( itr == vertexMap.end( ) )
        throw GraphException( startName + " is not a vertex in this graph" );

    Vertex *start = (*itr).second;
    pq.push( Path( start, 0 ) ); start->dist = 0;

    for( int nodesSeen = 0; nodesSeen < vertexMap.size( ); nodesSeen++ )
    {
        do    // Find an unvisited vertex
        {
            if( pq.empty( ) )
                return;
            vrec = pq.top( ); pq.pop( );
        } while( vrec.dest->scratch != 0 );

        Vertex *v = vrec.dest;
        v->scratch = 1;

        for( int i = 0; i < v->adj.size( ); i++ )
        {
            Edge e = v->adj[ i ];
            Vertex *w = e.dest;
            double cvw = e.cost;

            if( cvw < 0 )
                throw GraphException( "Graph has negative edges" );

            if( w->dist > v->dist + cvw )
            {
                w->dist = v->dist + cvw;
                w->prev = v;
                pq.push( Path( w, w->dist ) );
            }
        }
    }
}

// Single-source weighted shortest-path algorithm.
void Graph::dijkstra2( const string & startName )
{
    PairingHeap<Path> pq;
    Path vrec;     // Stores the result of a deleteMin

    vmap::iterator itr = vertexMap.find( startName );

    if( itr == vertexMap.end( ) )
        throw GraphException( startName + " is not a vertex in this graph" );

    clearAll( );
    Vertex *start = (*itr).second;
    start->dist = 0;
    start->pos = pq.insert( Path( start, 0 ) );

    while( !pq.isEmpty( ) )
    {
        pq.deleteMin( vrec );

        Vertex *v = vrec.dest;

        for( int i = 0; i < v->adj.size( ); i++ )
        {
            Edge e = v->adj[ i ];
            Vertex *w = e.dest;
            double cvw = e.cost;

            if( cvw < 0 )
                throw GraphException( "Graph has negative edges" );

            if( w->dist > v->dist + cvw )
            {
                w->dist = v->dist + cvw;
                w->prev = v;
                Path newVal( w, w->dist );

                if( w->pos == NULL )
                    w->pos = pq.insert( newVal );
                else
                    pq.decreaseKey( w->pos, newVal );
            }
        }
    }
}

// Single-source negative weighted shortest-path algorithm.
void Graph::negative( const string & startName )
{
    vmap::iterator itr = vertexMap.find( startName );

    if( itr == vertexMap.end( ) )
        throw GraphException( startName + " is not a vertex in this graph" );

    clearAll( );
    Vertex *start = (*itr).second;
    list<Vertex *> q;
    q.push_back( start ); start->dist = 0; start->scratch++;

    while( !q.empty( ) )
    {
        Vertex *v = q.front( ); q.pop_front( );
        if( v->scratch++ > 2 * vertexMap.size( ) )
            throw GraphException( "Negative cycle detected" );

        for( int i = 0; i < v->adj.size( ); i++ )
        {
            Edge e = v->adj[ i ];
            Vertex *w = e.dest;
            double cvw = e.cost;

            if( w->dist > v->dist + cvw )
            {
                w->dist = v->dist + cvw;
                w->prev = v;
                  // Enqueue only if not already on the queue
                if( w->scratch++ % 2 == 0 )
                    q.push_back( w );
                else
                    w->scratch--;   // undo the push
            }
        }
    }
}

// Single-source weighted shortest-path algorithm for acyclic graphs.
void Graph::acyclic( const string & startName )
{
    vmap::iterator itr = vertexMap.find( startName );

    if( itr == vertexMap.end( ) )
        throw GraphException( startName + " is not a vertex in this graph" );

    clearAll( );
    Vertex *start = (*itr).second;
    list<Vertex *> q;
    start->dist = 0;

      // Compute the indegrees
    for( itr = vertexMap.begin( ); itr != vertexMap.end( ); ++itr )
    {
        Vertex *v = (*itr).second;
        for( int i = 0; i < v->adj.size( ); i++ )
            v->adj[ i ].dest->scratch++;
    }

      // Enqueue vertices of indegree zero
    for( itr = vertexMap.begin( ); itr != vertexMap.end( ); ++itr )
    {
        Vertex *v = (*itr).second;
        if( v->scratch == 0 )
            q.push_back( v );
    }

    int iterations;
    for( iterations = 0; !q.empty( ); iterations++ )
    {
        Vertex *v = q.front( );	q.pop_front( );

        for( int i = 0; i < v->adj.size( ); i++ )
        {
            Edge e = v->adj[ i ];
            Vertex *w = e.dest;
            double cvw = e.cost;

            if( --w->scratch == 0 )
                q.push_back( w );

            if( v->dist == INFINITY )
                continue;

            if( w->dist > v->dist + cvw )
            {
                w->dist = v->dist + cvw;
                w->prev = v;
            }
        }
    }

    if( iterations != vertexMap.size( ) )
        throw GraphException( "Graph has a cycle!" );
}

// Process a request; return false if end of file.
bool processRequest( istream & in, Graph & g )
{
    string startName;
    string destName;
    char alg;

    cout << "Enter start node: ";
    if( !( in >> startName ) )
        return false;
    cout << "Enter destination node: ";
    if( !( in >> destName ) )
        return false;
    cout << "Enter algorithm (u, d, n, a): ";
    in >> alg;

    try
    {
        if( alg == 'u' )
            g.unweighted( startName );
        else if( alg == 'd' )
        {
            g.dijkstra( startName );
            g.printPath( destName );
            g.dijkstra2( startName );
        }
        else if( alg == 'n' )
            g.negative( startName );
        else if( alg == 'a' )
            g.acyclic( startName );
        g.printPath( destName );
    }
    catch( const GraphException & e )
    {
        cerr << e.toString( ) << endl;
    }
    return true;
}


// A simple main that reads the file given by argv[1]
// and then calls processRequest to compute shortest paths.
// Skimpy error checking in order to concentrate on the basics.
int main( int argc, char *argv[ ] )
{
    Graph g;

    if( argc != 2 )
    {
        cerr << "Usage: " << argv[ 0 ] << " graphfile" << endl;
        return 1;
    }

    ifstream inFile( argv[ 1 ] );
    if( !inFile )
    {
        cerr << "Cannot open " << argv[ 1 ] << endl;
        return 1;
    }

    cout << "Reading file... " << endl;

    string oneLine;

      // Read the edges; add them to g
    while( !getline( inFile, oneLine ).eof( ) )
    {
        string source, dest;
        double cost;

#ifndef USE_STR_DOT_H
        istringstream st( oneLine );
#else
        istrstream st( (char *) oneLine.c_str( ), oneLine.length( ) );
#endif

        st >> source; st >> dest; st >> cost;
        if( st.fail( ) )
            cerr << "Bad line: " << oneLine << endl;
        else
            g.addEdge( source, dest, cost );
    }

    cout << "File read" << endl << endl;
    while( processRequest( cin, g ) )
        ;

    return 0;
}


#ifdef SAFE_STL
    #include "EndConv.h"
#endif

