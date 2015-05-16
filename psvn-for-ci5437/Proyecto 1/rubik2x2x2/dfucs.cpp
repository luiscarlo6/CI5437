#include <vector>
#include "priority_queue.hpp"
#include <sys/time.h>

int visit(state_t* state, int64_t d, int64_t bound, int64_t* num_states, int64_t* dist){
    int64_t ruleid, t, new_bound;
    ruleid_iterator_t iter;
    state_t child;
    if (d > bound){
        //bound = d;
        return d;
    }

    if (is_goal(state)){
        return 0;
    }
    t = 9223372036854775808;
    init_fwd_iter( &iter, state );
    while( ( ruleid = next_ruleid( &iter ) ) >= 0 ) {
        apply_fwd_rule( ruleid, state, &child );
        *num_states += 1;
        new_bound = visit(&child, d + (int64_t)get_fwd_rule_cost(ruleid), bound, num_states, dist);
        if (new_bound==0){
            *state = child;
            *dist += 1;
            return 0;
        }
        if ((d + (int64_t)get_fwd_rule_cost(ruleid)) < t)
            t = d + (int64_t)get_fwd_rule_cost(ruleid);

    }
    //bound = t;
    
    return t;
}


int main( int argc, char **argv )
{
    PriorityQueue<state_t> open;
    char raw_state[256];
    int64_t totalNodes, numAtD;  // counters
    state_t state, child, result;   // NOTE: "child" will be a predecessor of state, not a successor
    int64_t d, ruleid, bound, num_states, dist, new_bound;
    ruleid_iterator_t iter;
    ssize_t nchars; 
    timeval t1, t2;
    double elapsedTime;
    state_map_t *map = new_state_map(); // contains the cost-to-goal for all states that have been generated
     // used for the states we have generated but not yet expanded (the OPEN list)
    FILE *file; // the final state_map is written to this file if it is provided (command line argument)
    while (1) {
        if ( fgets(raw_state, sizeof raw_state, stdin) == NULL ) {
            return 0; 
        }
        nchars = read_state( raw_state, &state );
        print_state( stdout, &state );
        printf(" : - ");
        gettimeofday(&t1, NULL);
        num_states = 0;
        dist = 0;
        bound = 0;
        d = 0;
        while (true){
            new_bound = visit(&state, d, bound, &num_states, &dist);
            //printf("%i\n", new_bound);
            if (new_bound ==0){
                gettimeofday(&t2, NULL);
                elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
                elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
                elapsedTime /= 1000;
                printf("%i %"PRId64" %f %f\n", dist, num_states, elapsedTime, num_states/elapsedTime);
                break;
            }
            bound = new_bound;
        }

    }
    return 0;
}