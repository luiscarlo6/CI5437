#include <vector>
#include "priority_queue.hpp"

int main( int argc, char **argv )
{
    PriorityQueue<state_t> open;
    char raw_state[256];
    int64_t totalNodes, numAtD;  // counters
    state_t state, child;   // NOTE: "child" will be a predecessor of state, not a successor
    int64_t d, ruleid;
    ruleid_iterator_t iter;
    ssize_t nchars; 
    state_map_t *map = new_state_map(); // contains the cost-to-goal for all states that have been generated

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
    open.Add(0, 0, state );
    //state_map_add( map, &state, 0 );
    d = 0;
    while( !open.Empty() ) {
        state = open.Top();
        open.Pop();

        if (is_goal(&state)){
            print_state( stdout, &state );
            printf("\n");
            return 0;
        }
        //printf("%i\n", d);
        init_fwd_iter( &iter, &state );
        while( ( ruleid = next_ruleid( &iter ) ) >= 0 ) {
            apply_fwd_rule( ruleid, &state, &child );
            d++;
            open.Add(d,0, child );
        }

    }

    return 0;
}