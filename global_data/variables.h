#ifndef VARIABLES_H_   /* Include guard */
#define VARIABLES_H_

#include <pthread.h>

#include "structures.h"

/*
-----------------------------------------------------------------------------------------------------------
Global Variables
-----------------------------------------------------------------------------------------------------------
*/

// database
mongoc_client_t* database_client;
mongoc_client_pool_t* database_client_thread_pool;

char* xcash_wallet_public_address; // Holds your wallets public address
struct block_verifiers_list block_verifiers_list; // The list of the enabled nodes name, public address and IP address
struct block_validation_nodes_list block_validation_nodes_list; // The list of block validation nodes public address
struct VRF_data_block_verifiers VRF_data_block_verifiers; // The list of all block verifiers received data from the main node
struct VRF_data VRF_data; // The list of all of the VRF data to send to the block producer.
struct blockchain_data blockchain_data; // The data for a new block to be added to the network.
struct mainnode_timeout mainnode_timeout; // The mainnode timeout vote count and the public addresses that voted.
struct node_to_node_vote node_to_node_vote; // will hold the vote count for true and false in a round and the public addresses that voted for true and false
char* consensus_node_add_blocks_to_network; // 1 if the consensus node should add new blocks to the network, otherwise 0
char* current_consensus_nodes_IP_address; // The current consensus nodes IP address
int current_consensus_node_settings; // 1 if the consensus node is the current consensus node, otherwise 0
char* main_nodes_public_address; // The current main nodes public address
pthread_t check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_thread_id; // The thread ID for the check_if_consensus_node_needs_to_add_a_block_to_the_network_timer
pthread_t check_if_consensus_node_is_offline_timer_thread_id; // The thread ID for the check_if_consensus_node_is_offline_timer
int check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_settings; // 1 if the check_if_consensus_node_needs_to_add_a_block_to_the_network_timer is running, otherwise 0
int check_if_consensus_node_is_offline_timer_settings; // 1 if the check_if_consensus_node_is_offline_timer is running, otherwise 0
char* server_message; // The message the server should run. It will ignore any other messages.
char* current_round_part; // The current round part (1-4)
char* current_round_part_backup_node; // The current main node in the current round part (0-5)
#endif