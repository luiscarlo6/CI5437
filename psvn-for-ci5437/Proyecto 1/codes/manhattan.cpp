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
#include <math.h>

using namespace std;

string convertInt(int number)
{
   ostringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int main( int argc, char **argv ){
    int nchars, cost, ini, end, num_vars, change;
    state_t state, goal;
    char raw_state[256];
    int n, c;

    if ( fgets(raw_state, sizeof raw_state, stdin) == NULL ) {
        return 0; 
    }
    nchars = read_state( raw_state, &state );
    char** clean_vars = new char* [nchars/2];

    for (int i = 0; i < nchars/ 2; ++i)
        clean_vars[i] = new char[3];
    
    ini = change = num_vars = 0;
    end = -1;
    for (int i = 0; i < nchars; i++){
        if(raw_state[i] != ' '){
            if(i - 1 > 0 || raw_state[i-1] == ' ')
                ini = i;
            change = 0;
            if(i + 1 == nchars-1){
                end = i;
                change = 1;
            }else{
                if(raw_state[i+1] == ' ')
                    end = i;
            }
        }else{
            change = 1;
        }
        if(end >= 0 && ini < nchars && end >= ini && change != 0){
            for(int j = 0; j <= ini - end + 1; j++){
                if(j <= ini - end )
                    clean_vars[num_vars][j] = raw_state[ini + j];
                else
                  clean_vars[num_vars][j] = '\0';
            }
        }
        if(end >= ini && change != 0)
            num_vars++;
    }
    char manhattan[num_vars];
    n = sqrt(num_vars);
    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (strcmp(clean_vars[i*n + j],"b") && strcmp(clean_vars[i*n + j],"B"))
                c = atoi(clean_vars[i*n + j]);
            else
                c = 0;
            manhattan[c] = abs(c/n - i) + abs(c%n - j);
        }
    }
    return 0;
}