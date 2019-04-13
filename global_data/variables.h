#ifndef VARIABLES_H_   /* Include guard */
#define VARIABLES_H_

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
char* server_message; // The message the server should run. It will ignore any other messages.
char* current_consensus_nodes_IP_address; // The current consensus nodes IP address
char* main_nodes_public_address; // The current main nodes public address
char* current_round_part; // The current round part (1-4)
char* current_round_part_backup_node; // The current main node in the current round part (0-5)
char* server_message; // The message the server should run. It will ignore any other messages.
#endif