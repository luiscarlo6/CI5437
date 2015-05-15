#include <vector>
#include "priority_queue.hpp"
#include <sys/time.h>

int main( int argc, char **argv )
{
    PriorityQueue<state_t> open;
    char raw_state[256];
    int64_t totalNodes, numAtD;  // counters
    state_t state, child;   // NOTE: "child" will be a predecessor of state, not a successor
    int64_t d, ruleid, current_distance,num_states;
    int g, ng;
    ruleid_iterator_t iter;
    ssize_t nchars; 
    timeval t1, t2;
    double elapsedTime;
    state_map_t *map = new_state_map(); // contains the cost-to-goal for all states that have been generated
     // used for the states we have generated but not yet expanded (the OPEN list)
    FILE *file; // the final state_map is written to this file if it is provided (command line argument)
    while (true) {
        if ( fgets(raw_state, sizeof raw_state, stdin) == NULL ) {
            return 0; 
        }
        nchars = read_state( raw_state, &state );
        print_state( stdout, &state );
        printf(" : - ");
        gettimeofday(&t1, NULL);
        num_states = 0;
        state_map_add(map, &state, 0);
        open.Add(0, 0, state );
        
        while( !open.Empty() ) {
            ng = open.CurrentPriority();
            state = open.Top();
            open.Pop();

            if (is_goal(&state)){
                gettimeofday(&t2, NULL);
                elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
                elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
                elapsedTime /= 1000;
                const int *dist = state_map_get( map, &state );
                printf("%i %"PRId64" %f %f\n",*dist, num_states, elapsedTime, num_states/elapsedTime);
                open.Clear();
                destroy_state_map(map);
                map = new_state_map();
                break;
            }

            init_fwd_iter( &iter, &state );
            while( ( ruleid = next_ruleid( &iter ) ) >= 0 ) {
                num_states++;
                apply_fwd_rule( ruleid, &state, &child );
                g = ng + get_fwd_rule_cost(ruleid);

                const int * dist = state_map_get(map, &child);
                if (dist == NULL){
                    state_map_add(map, &child, g);
                    open.Add(g, g, child);
                }
                else if (g < *dist) {
                    state_map_add(map, &child, g);
                    open.Modify(g, g, 0, child);
                }
            }
        }
    }
        //printf("%i\n", d);
    return 0;
}
