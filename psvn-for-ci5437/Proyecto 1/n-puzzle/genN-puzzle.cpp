/*
 * Generates PSVN for the n-puzzle puzzle.
 * Uses the "standard" encoding of the puzzle, which has one state variable for
 * 	each tile order.
 * Supports two cost models:
 *	-- unifom (all operators cost the same)
 *	-- Vertical move on the blan tile cost 2, horizontal move cost 1.
 * originally written by Gabriel Freites and Luiscarlo Rivera
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
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
    int seed, h, v, cost;
    bool printcost;
    int currentpos, max, print;
    div_t divresult;


/******* EXTRACT COMMAND LINE ARGUMENTS ************/
    if ( (argc < 2) || (argc > 3) ) {
      cerr << "You must provide 1 or 2 integers on the command line." << endl;
      cerr << "The first integer is the length of the puzzle." << endl;
      cerr << "If there are no other integers, operator costs will all be 1." << endl;
      cerr << "If there is one other integer, if it's a the cost model is unitary." << endl;
      cerr << "If it's b the horizontal moves cost 1 and the vertical moves cost 2, " << endl;
      cerr << "just the blank tile movesasd." << endl;
      exit(0);
    }
    if( (!sscanf( argv[1], "%d", &N )) 
          || N <= 0 ) {
        cerr << "bad length of puzzle: " << argv[2] << endl;
        exit( -1 );
    }
    if (argc == 3) {
        if(strcmp(argv[2], "b") != 0){
            h = 1;
            v = 2;
        }else if(strcmp(argv[2],"a") != 0){
            h = v = 1;
        }else{
            cerr << "You must provide 1 or 2 integers on the command line." << endl;
            cerr << "The first integer is the length of the puzzle." << endl;
            cerr << "If there are no other integers, operator costs will all be 1." << endl;
            cerr << "If there is one other integer, if it's 1 the cost model is unitary." << endl;
            cerr << "If it's 2 the horizontal moves cost 1 and the vertical moves cost 2, " << endl;
            cerr << "just the blank tile moves asd." << endl;
            exit(0);
        }
    }else{
        h = v = 0;
    }

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


    cout << "\n# 1 state variable is the blank 'B' the others goes from 1 to " << max-1 << ".\n";
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
                            cost = v;
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
                            cost = h;
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
                            cost = v;
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
                            cost = h;
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
                    if(cost != 0)
                        cout << " COST " << convertInt(cost);
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
