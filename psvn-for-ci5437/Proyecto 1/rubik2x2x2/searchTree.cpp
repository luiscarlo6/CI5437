#include <vector>
#include "priority_queue.hpp"

int main( int argc, char **argv )
{
    int64_t totalNodes, numAtD;  // counters
    state_t state, child;   // NOTE: "child" will be a predecessor of state, not a successor
    int d, ruleid;
    ruleid_iterator_t iter;

    int hist, child_hist;
	hist = init_history;

    PriorityQueue<state_t> open; // used for the states we have generated but not yet expanded (the OPEN list)
    state_map_t *map = new_state_map(); // contains the cost-to-goal for all states that have been generated
    FILE *file; // the final state_map is written to this file if it is provided (command line argument)

    /* add goal states */
    first_goal_state( &state, &d ); do {
        //state_map_add( map, &state, 0 );
        open.Add(0, 0, state );
    } while( next_goal_state( &state, &d ) );

    totalNodes = 0;
    d = 0;
    numAtD = 0;
    while( !open.Empty() ) {

        /* get current distance from goal; since operator costs are
           non-negative this distance is monotonically increasing */
        if (open.CurrentPriority() > d) {
            printf( "%"PRId64" states at distance %d\n", numAtD, d );
            d = open.CurrentPriority();
            numAtD = 0;
        }

        /* get state */
        state = open.Top();
        open.Pop();
        numAtD++;
        totalNodes++;

        /* look at all predecessors of the state */
        init_bwd_iter( &iter, &state );
        while( ( ruleid = next_ruleid( &iter ) ) >= 0 ) {
            if (!bwd_rule_valid_for_history(hist,ruleid))
				continue;
			child_hist = next_bwd_history(hist,ruleid);
			apply_bwd_rule(ruleid,&state,&child);
        }
        //free(&state);
    }

    /* print last level */
    if (numAtD > 0) {
        printf( "%"PRId64" states at distance %d\n", numAtD, d);
    }
    
    printf( "%"PRIu64" states in total.\n", totalNodes );
    return 0;
}