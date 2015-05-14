#include <vector>
#include "priority_queue.hpp"
#include <sys/time.h>

int visit(state_t* state, int64_t d, int64_t bound){
    int64_t ruleid,t,p;
    ruleid_iterator_t iter;
    state_t child;
    if (d > bound){
        return d;
    }

    if (is_goal(state)){
        return -1;
    }
    t = 9223372036854775;
    init_fwd_iter( &iter, state );
    while( ( ruleid = next_ruleid( &iter ) ) >= 0 ) {
        apply_fwd_rule( ruleid, state, &child );
    //printf("bound %"PRId64" , distance %"PRId64"  state ", bound,d );
    //print_state(stdout,&child);
    //printf("\n");
        p = visit(&child, get_fwd_rule_cost(ruleid), bound);
        if (p == -1){
            *state = child;
            return -1;
        }
        if (t>p) t=p;
    }
    return t;
}


int main( int argc, char **argv )
{
    PriorityQueue<state_t> open;
    char raw_state[256];
    int64_t totalNodes, numAtD;  // counters
    state_t state, child, result;   // NOTE: "child" will be a predecessor of state, not a successor
    int64_t d, ruleid, bound;
    ruleid_iterator_t iter;
    ssize_t nchars; 
    state_map_t *map = new_state_map(); // contains the cost-to-goal for all states that have been generated
     // used for the states we have generated but not yet expanded (the OPEN list)
    FILE *file; // the final state_map is written to this file if it is provided (command line argument)
    while (1) {
        if ( fgets(raw_state, sizeof raw_state, stdin) == NULL ) {
            return 0; 
        }
        nchars = read_state( raw_state, &state );
        bound = 0;
        while (true){
            d = visit(&state, 0, bound);
            if (d==-1){
                print_state( stdout, &state );
                printf("\n");
                break;
            }
            bound = d;
        }

    }
    return 0;
}