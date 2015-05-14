#include <vector>
#include "priority_queue.hpp"

int main( int argc, char **argv )
{
    int64_t totalNodes, numAtD;  // counters
    state_t state, child;   // NOTE: "child" will be a predecessor of state, not a successor
    int d, ruleid;
    ruleid_iterator_t iter;

    PriorityQueue<state_t> open; // used for the states we have generated but not yet expanded (the OPEN list)
    state_map_t *map = new_state_map(); // contains the cost-to-goal for all states that have been generated
    FILE *file; // the final state_map is written to this file if it is provided (command line argument)

    /* add goal states */
    first_goal_state( &state, &d ); do {
        state_map_add( map, &state, 0 );
        open.Add(0, 0, state );
    } while( next_goal_state( &state, &d ) );


    return 0;
}