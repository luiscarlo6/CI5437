/*
 * Generates PSVN for the Arrow puzzle.
 * Uses the "standard" encoding of the puzzle, which has one binary state variable for
 * 	each arrow indicating if the arrow is pointing down (0) or up (1).
 * Supports two cost models:
 *	-- unifom (all operators cost the same)
 *	-- random (each operator's cost is generated uniformly at random in a user-specified range)
 * originally written by Meysam Bastani
 * Edited by Shahab Jabbari Arfaee
 * Edited by Rob Holte
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <assert.h>

using namespace std;
#define NUM_OP 4 //Number of max operations posible in any position.

string convertInt(int number)
{
   ostringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int main(int argc, char *argv[])
{
    int N; // the size of the puzle
    int seed, mincost, maxcost, range, cost;
    bool printcost;
    int currentpos, max, print;
    div_t divresult;


/******* EXTRACT COMMAND LINE ARGUMENTS ************/

    if ( (argc < 2) || (argc == 4) || (argc > 5) ) {
      cerr << "You must provide 1, 2, or 4 integers on the command line." << endl;
      cerr << "The first integer is the length of the puzzle." << endl;
      cerr << "If there are no other integers, operator costs will all be 1." << endl;
      cerr << "If there is one other integer, operator costs will all be that value." << endl;
      cerr << "If there are three additional integers, operator costs will be generated at random, and" << endl;
      cerr << "these three integers are: the minimum cost, the maximum cost, and the random number seed." << endl;
      exit(0);
    }

    if( (!sscanf( argv[1], "%d", &N )) 
          || N <= 0 ) {
        cerr << "bad length of puzzle: " << argv[1] << endl;
        exit( -1 );
    }
    if (argc == 2) {
        mincost = maxcost = 1;
    } else if (argc == 3) { // uniform costs of a specified value
        if( (!sscanf( argv[2], "%d", &mincost )) 
              || mincost < 0 ) {
            cerr << "bad operator cost: " << argv[2] << endl;
            exit( -1 );
        }
        maxcost = mincost;
    } else {
        assert(argc==5);  // randomly generated costs
        if( (!sscanf( argv[2], "%d", &mincost )) 
              || mincost < 0 ) {
            cerr << "bad minimum operator cost: " << argv[2] << endl;
            exit( -1 );
        }
        if( (!sscanf( argv[ 3 ], "%d", &maxcost )) 
              || maxcost < 0 ) {
            cerr << "bad maximum operator cost: " << argv[3] << endl;
            exit( -1 );
        }
        if( ( mincost > maxcost )) {
            cerr << "minimum cost must be less than maximum cost" << endl;
            exit( -1 );
        }
        if( (!sscanf( argv[4], "%d", &seed )) 
              || seed < 2 ) {
            cerr << "bad random seed (must be 2 or larger): " << argv[4] << endl;
            exit( -1 );
        }
    }

    range = maxcost-mincost+1;
    if (range == 1) {     // if range==1 we have uniform costs all equal to mincost
        cost = mincost;   
    } else {
        srand(seed);   // initialize the random number generator
    }
    printcost = (range > 1) || (mincost > 1) ;
    max = N*N;

/******* CREATE THE PSVN FILE ************/


    cout << "# This file was created by genN-puzzle.cpp with the following command line parameters:\n#";
    for (int i=1; i<argc; ++i) {
	cout << "  " << argv[i] ;
    }
    cout << "\n\nDOMAIN tile " << max << " B ";
    for (int i=1;i<max;i++)  { cout << i << " "; };
    cout << "  #The name of the domain \n";
    cout << "\n\n# number of state variables\n";
    cout << " " << max << "\n";


    cout << "\n# 1 state variable is the blank 'B' the others goes from 1 to "<<max-1>>".\n";
    for (int i=0;i<max;i++)
        cout << "tile ";
    cout << "\n\n";

    for (int i=0; i<N;i++) {  // create the rules for flipping bits i and i+1
        for(int j=0;j<N;j++){    // there will be 4 such rules (one for each binary combination
            currentpos = i*N + j;
            for(int k=0;k<NUM_OP;k++){
                string tstr="";       // the first i-1 variables are irrelevant
                string tstr2="";
                string label="";
                print = 0;
                for(int l=0; l<max; l++){
                    if(k == 0){     //We use 0 for the blank up move 
                        if(i == 0)
                            break;
                        if(l == currentpos - N){
                            tstr = tstr + "X ";
                            tstr2 = tstr2 + "B ";
                            label = " LABEL move" + convertInt(i) + convertInt(j) + "_up";
                            print = 1;
                            continue;
                        }
                    }else if(k == 1){ // We use 1 to indicate the blank moves to the right
                        if(j == N -1)
                            break;
                        if(l == currentpos + 1){
                            tstr = tstr + "X ";
                            tstr2 = tstr2 + "B ";
                            label = " LABEL move" + convertInt(i) + convertInt(j) + "_right";
                            print = 1;
                            continue;
                        }
                    }else if(k == 2){ // We use 2 to indicate the blank moves down
                        if(i == N)
                            break;
                        if(l == currentpos + N){
                            tstr = tstr + "X ";
                            tstr2 = tstr2 + "B ";
                            label = " LABEL move" + convertInt(i) + convertInt(j) + "_down";
                            print = 1;
                            continue;
                        }
                    }else if(k == 3){ // We use 3 to indicate the blank moves to the left
                        if(j == 0)
                            break;
                        if(l == currentpos - 1){
                            tstr = tstr + "X ";
                            tstr2 = tstr2 + "B ";
                            label = " LABEL move" + convertInt(i) + convertInt(j) + "_left";
                            print = 1;
                            continue;
                        }
                    }
                    if(l == currentpos){ // if the position of the str match the B position
                        tstr = tstr + "B ";
                        tstr2 = tstr2 + "X ";
                    }else{
                        tstr = tstr + "- ";
                        tstr2 = tstr2 + "- ";
                    }
                }
                if(print==1){
                    cout << tstr << "=> " << tstr2 << label;
                    //cout << "  LABEL Flip_"+convertInt(i+1) << "_" << convertInt(i+2);  // the arrows are numbered from 1, not 0
                    //if (printcost) { cout << " COST " << convertInt(cost); }
                    cout << endl ;
                }
            }
        }
    }
    cout << "\nGOAL B ";
    for (int i=1;i<max;i++)  { cout << i << " "; } // in the goal, all arrows point down
    cout << endl ;
    exit(0);
}
