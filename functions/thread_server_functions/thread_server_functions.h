#ifndef THREAD_SERVER_FUNCTIONS_H_   /* Include guard */
#define THREAD_SERVER_FUNCTIONS_H_

/*
-----------------------------------------------------------------------------------------------------------
Function prototypes
-----------------------------------------------------------------------------------------------------------
*/

void* total_connection_time_thread(void* parameters);
void* mainnode_timeout_thread(void* parameters);
void* check_if_consensus_node_is_offline_timer();
void* xcash_proof_of_stake_timer();
#endif