#include <vector>
#include "priority_queue.hpp"

int main( int argc, char **argv )
{
    PriorityQueue<state_t> open;
    char raw_state[256];
    int64_t totalNodes, numAtD;  // counters
    state_t state, child;   // NOTE: "child" will be a predecessor of state, not a successor
    int d, ruleid;
    ruleid_iterator_t iter;
    ssize_t nchars; 

     // used for the states we have generated but not yet expanded (the OPEN list)
    FILE *file; // the final state_map is written to this file if it is provided (command line argument)
    if ( fgets(raw_state, sizeof raw_state, stdin) == NULL ) {
        printf("Error: empty input line.\n");
        return 0; 
    }
    nchars = read_state( raw_state, &state );
    if (nchars <= 0) {
        printf("Error: invalid state entered.\n");
        return 0; 
    }

    std::vector<int> v;
    v.push_back(&state);
    print_state(stdout,v.push_back());

    return 0;
}