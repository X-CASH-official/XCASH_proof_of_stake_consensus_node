#ifndef SERVER_FUNCTIONS_H_   /* Include guard */
#define SERVER_FUNCTIONS_H_

/*
-----------------------------------------------------------------------------------------------------------
Function prototypes
-----------------------------------------------------------------------------------------------------------
*/

int get_current_consensus_node();
int get_block_verifiers_list();
int send_consensus_node_needs_to_add_a_block_to_the_network_message();
int consensus_node_create_new_block();
int calculate_main_nodes_role();
int mainode_consensus();
int send_data_socket_consensus_node_to_node();
int send_data_socket_consensus_node_to_mainnode();
int server_received_data_xcash_proof_of_stake_test_data(const int CLIENT_SOCKET, char* message);
int server_receive_data_socket_node_to_consensus_node_send_current_consensus_node_IP_address(const int CLIENT_SOCKET, char* message);
int create_server(const int MESSAGE_SETTINGS);
#endif