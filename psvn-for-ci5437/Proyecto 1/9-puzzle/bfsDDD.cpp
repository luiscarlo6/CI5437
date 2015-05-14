#include <vector>
#include "priority_queue.hpp"
#include <sys/time.h>

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
    while (1) {
        if ( fgets(raw_state, sizeof raw_state, stdin) == NULL ) {
            return 0; 
        }
        nchars = read_state( raw_state, &state );
        print_state( stdout, &state );
        printf("->");
        open.Add(0, 0, state );
        state_map_add( map, &state, 0 );
        d = 0;
        while( !open.Empty() ) {
            state = open.Top();
            open.Pop();

            if (is_goal(&state)){
                print_state( stdout, &state );
                printf("\n");
                open.Clear();
                destroy_state_map(map);
                map = new_state_map();
                break;
            }
            //printf("%i\n", d);
            init_fwd_iter( &iter, &state );
            while( ( ruleid = next_ruleid( &iter ) ) >= 0 ) {
                apply_fwd_rule( ruleid, &state, &child );
                const int *best_dist = state_map_get( map, &child );
                if (best_dist == NULL){
                    d++;
                    open.Add(d,0, child );
                    state_map_add( map, &child, d );
                }

            }

        }
    }
        //printf("%i\n", d);
    return 0;
}
