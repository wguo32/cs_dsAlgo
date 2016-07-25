
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
    using std::vector;
#else
    #include "vector.h"
    #include "StartConv.h"
#endif

// Dynamic programming algorithm to solve change-making problem.
// As a result, the coinsUsed array is filled with the
// minimum number of coins needed for change from 0->maxChange
// and lastCoin contains one of the coins needed to make the change.
void makeChange( const vector<int> & coins, int maxChange,
                       vector<int> & coinsUsed, vector<int> & lastCoin )
{
    int differentCoins = coins.size( );
    coinsUsed.resize( maxChange + 1 );
    lastCoin.resize( maxChange + 1 );

    coinsUsed[ 0 ] = 0; lastCoin[ 0 ] = 1;

    for( int cents = 1; cents <= maxChange; cents++ )
    {
        int minCoins = cents, newCoin = 1;

        for( int j = 0; j < differentCoins; j++ )
        {
            if( coins[ j ] > cents )   // Can't use coin j
                continue;
            if( coinsUsed[ cents - coins[ j ] ] + 1 < minCoins )
            {
                minCoins = coinsUsed[ cents - coins[ j ] ] + 1;
                newCoin  = coins[ j ];
            }
        }

        coinsUsed[ cents ] = minCoins;
        lastCoin[ cents ]  = newCoin;
    }
}


// Simple test program
int main( )
{
        // The coins and the total amount of change
    vector<int> coins;
    coins.push_back( 1 );
    coins.push_back( 5 );
    coins.push_back( 10 );
    coins.push_back( 21 );
    coins.push_back( 25 );

    vector<int> used;
    vector<int> last;

    for( int change = 4; change < 100; change += 3 )
    {
        makeChange( coins, change, used, last );

        cout << "Total cents: " << change << "; Best is " << used[ change ]  << ": ";

        for( int i = change; i > 0; i -= last[ i ] )
            cout << last[ i ] << " ";
        cout << endl;
    }

    return 0;
}


#ifdef SAFE_STL
    #include "EndConv.h"
#endif
