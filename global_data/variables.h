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
char* consensus_node_add_blocks_to_network; // 1 if the consensus node should add new blocks to the network, otherwise 0
char* block_validation_xcash_proof_of_stake_settings_node; // The IP address of the block validation node that the consensus node will check to see if it needs to add blocks to the network.
char* current_consensus_nodes_IP_address; // The current consensus nodes IP address
int current_consensus_node_settings; // 1 if the consensus node is the current consensus node, otherwise 0
char* main_nodes_public_address; // The current main nodes public address
pthread_t xcash_proof_of_stake_timer_thread_id; // The thread ID for the xcash_proof_of_stake_timer
pthread_t check_if_consensus_node_is_offline_timer_thread_id; // The thread ID for the check_if_consensus_node_is_offline_timer
int xcash_proof_of_stake_timer_settings; // 1 if the xcash_proof_of_stake_timer is running, otherwise 0
int check_if_consensus_node_is_offline_timer_settings; // 1 if the check_if_consensus_node_is_offline_timer is running, otherwise 0
char* server_message; // The message the server should run. It will ignore any other messages.
char* vote_round_change_timeout; // The amount of nodes that voted for a round change because the main node did not send any data
char* vote_next_round_true; // The amount of nodes that voted true for a part of a round
char* vote_next_round_false; // The amount of nodes that voted false for a part of a round
char* current_round_part; // The current round part (1-4)
char* current_round_part_backup_node; // The current main node in the current round part (0-5)
#endif