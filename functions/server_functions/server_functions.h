#ifndef SERVER_FUNCTIONS_H_   /* Include guard */
#define SERVER_FUNCTIONS_H_

/*
-----------------------------------------------------------------------------------------------------------
Function prototypes
-----------------------------------------------------------------------------------------------------------
*/

int server_received_data_xcash_proof_of_stake_test_data(const int CLIENT_SOCKET, char* message);
int server_receive_data_socket_consensus_node_to_node(const int CLIENT_SOCKET, pthread_t thread_id, char* message);
int get_current_consensus_node();
int get_block_verifiers_list();
int send_consensus_node_needs_to_add_a_block_to_the_network_message();
int consensus_node_create_new_block();
int calculate_main_nodes_role();
int create_server(const int MESSAGE_SETTINGS);
#endif