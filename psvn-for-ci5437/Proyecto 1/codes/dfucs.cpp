#include <vector>
#include "priority_queue.hpp"
#include <sys/time.h>
#include <algorithm>    // std::min

int64_t visit(state_map_t* map, state_t* state, int64_t *bound){
    int64_t ruleid, child_cost, state_cost, old_bound;
    ruleid_iterator_t iter;
    state_t child;
    state_cost = *state_map_get(map, state);
    int *best_child_dist;
    if (state_cost > *bound){
        *bound = state_cost;
    }
    if (is_goal(state)){
        *bound = state_cost;
    }

    init_fwd_iter( &iter, state );
    while( ( ruleid = next_ruleid( &iter ) ) >= 0 ) {
        apply_fwd_rule( ruleid, state, &child );
        best_child_dist = state_map_get(map, &child);
        child_cost = *bound + (int64_t)get_fwd_rule_cost(ruleid);
        if(best_child_dist == NULL){
            state_map_add( map, &child, child_cost );
        }else if(*best_child_dist > child_cost){
            state_map_add( map, &child, child_cost );
        }else{
            continue;
        }

        //printf("bound %"PRId64" , distance %"PRId64"  state ", child_cost, *best_child_dist);
    //print_state(stdout,&child);
        printf("\n");
        if(child_cost > *bound)
            *bound = (int64_t)child_cost;
        old_bound = visit(map, state, bound);
    }
    return *bound;
}


int main( int argc, char **argv )
{
    PriorityQueue<state_t> open;
    char raw_state[256];
    int64_t totalNodes, numAtD, old_bound;  // counters
    state_t root, child, result;   // NOTE: "child" will be a predecessor of state, not a successor
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
        nchars = read_state( raw_state, &root );
        bound = 0;
        state_map_add( map, &root, bound );
        while (true){
            old_bound = visit(map, &root, &bound);
            if (old_bound !=-1 || old_bound == bound){
                print_state( stdout, &root );
                printf("\n");
                printf(" bound %"PRId64" \n", bound);
                break;
            }
        }

    }
    return 0;
}