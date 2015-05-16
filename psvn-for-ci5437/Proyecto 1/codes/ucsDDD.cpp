#include <vector>
#include "priority_queue.hpp"
#include <sys/time.h>

int ucs(state_t state){
    PriorityQueue<state_t> open;
    char raw_state[256];
    int64_t totalNodes, numAtD, num_states;  // counters
    state_t child;   // NOTE: "child" will be a predecessor of state, not a successor
    int64_t d, ruleid;
    ruleid_iterator_t iter;
    ssize_t nchars; 
    timeval t1, t2;
    double elapsedTime;
    state_map_t *map = new_state_map();

    print_state( stdout, &state );
    printf(" : - ");
    gettimeofday(&t1, NULL);
    open.Add(0, 0, state);
    state_map_add( map, &state, 0 );
    d = 0;
    num_states = 0;
    while( !open.Empty() ) {
        /* get current distance from goal */
        d = open.CurrentPriority();
        state = open.Top();
        open.Pop();

        const int *best_dist = state_map_get( map, &state );
        if (best_dist != NULL || d < *best_dist){
            state_map_add(map, &state, d);
            if (is_goal(&state)){
                gettimeofday(&t2, NULL);
                elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
                elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
                elapsedTime /= 1000;
                const int *dist = state_map_get( map, &state );
                printf("%i %"PRId64" %f %f\n",*dist, num_states, elapsedTime, num_states/elapsedTime);
                open.Clear();
                destroy_state_map(map);
                return 0;
            }   

             //printf("%i\n", d);
            init_fwd_iter( &iter, &state );
            while( ( ruleid = next_ruleid( &iter ) ) >= 0 ) {
                apply_fwd_rule( ruleid, &state, &child );
                state_map_add(map, &child, d + get_fwd_rule_cost(ruleid) );
                open.Add(d + get_fwd_rule_cost(ruleid ),0,child);
                num_states++;
            }
        }   
    }
    return -1;
}


int main( int argc, char **argv )
{
    char raw_state[256];
    state_t state;
    ssize_t nchars; 
    while (( fgets(raw_state, sizeof raw_state, stdin) != NULL )) {
        nchars = read_state( raw_state, &state );
        if (nchars <= 0) {
            printf("Error: invalid state entered.\n");
            continue;
        }
        ucs(state);
    }
    return 0;
}