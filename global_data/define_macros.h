#ifndef DEFINE_MACROS_H_   /* Include guard */
#define DEFINE_MACROS_H_

/*
-----------------------------------------------------------------------------------------------------------
Using define statements instead of constants for increased efficiency
-----------------------------------------------------------------------------------------------------------
*/

#define SEND_DATA_PORT 8000 // The port that is used by all nodes to send and receive data
#define XCASH_WALLET_LENGTH 98 // The length of a XCA address
#define CONSENSUS_NODE_PUBLIC_ADDRESS "XCA" // The consensus nodes public address
#define CONSENSUS_BACKUP_NODE_PUBLIC_ADDRESS "XCA" // The consensus backup nodes public address
#define CONSENSUS_NODES_IP_ADDRESS "" // The consensus nodes IP address
#define CONSENSUS_BACKUP_NODES_IP_ADDRESS "" // The consensus backup nodes IP address
#define RANDOM_STRING_LENGTH 100 // The length of the random string
#define BUFFER_SIZE 64000
#define NODES_UPDATED_TIME_FILE_NAME "nodes_updated_time.txt" // The last time the node has updated the list of nodes from the consensus node
#define NODES_PUBLIC_ADDRESS_LIST_FILE_NAME "nodes_public_address_list.txt" // The current enabled nodes public address list
#define NODES_NAME_LIST_FILE_NAME "nodes_name_list.txt" // The current enabled nodes name list
#define NETWORK_BLOCK_TIME 300 // The network block time for the network in seconds (5 minutes)
#define UPDATE_BLOCK_VERIFIERS_TIME 120 // The time it takes the consensus node to update all of the block verifiers (2 minutes)
#define NETWORK_VERSION "0000" // the network version
#define BLOCK_PRODUCER_NETWORK_BLOCK_NONCE "00000000" // the network block nonce used when the block producer creates the block
#define CONSENSUS_NODE_NETWORK_BLOCK_NONCE "11111111" // the network block nonce used when the consensus node creates the block
#define RESERVE_PROOFS_LIST_MAXIMUM_AMOUNT 20000 // the maximum amount of reserve proofs (total_supply / xcash_proof_of_stake_minimum_amount)
#define XCASH_PROOF_OF_STAKE_MINIMUM_AMOUNT 5000000000000 // the minimum amount the reserve proof can be created for
#define BLOCK_VALIDATION_NODES_TOTAL_AMOUNT 100 // The total amount of block validation nodes
#define BLOCK_VALIDATION_NODES_AMOUNT 100 // The amount of block validation nodes needed to make the network block valid
#define BLOCK_VERIFIERS_AMOUNT 100 // The amount of block verifiers in a round
#define BLOCK_VERIFIERS_VALID_AMOUNT 67 // The amount of block verifiers that need to vote true for the part of the round to be valid.
#define TRUSTED_BLOCK_VERIFIERS_TOTAL_AMOUNT 100 // The total amount of trusted block verifiers
#define TRUSTED_BLOCK_VERIFIERS_AMOUNT 100 // The amount of trusted block verifiers needed to make the vote valid
#define BLOCK_VERIFIERS_NAME_TOTAL_LENGTH 100 // The maximum length of the block verifiers name
#define BLOCK_VERIFIERS_IP_ADDRESS_TOTAL_LENGTH 100 // The maximum length of the block verifiers IP address
#define DATABASE_CONNECTION "mongodb://localhost:27017" // the database connection string
#define DATABASE_NAME "XCASH_PROOF_OF_STAKE" // The name of the database
#define DATABASE_ARRAY_COUNT 100 // The maximum amount of parsed item and value from the database
#define BLOCK_VERIFIERS_TOTAL_VOTE_TIME 60 // The total amount of time for the block verifiers to send their votes to the consensus node
#define TOTAL_CONNECTION_TIME_SETTINGS 10 // The total time a client is given to connect to the server and send data
#define INVALID_PARAMETERS_ERROR_MESSAGE \
"Parameters\n" \
"--test - Run the test to make sure the program is compatible with your system\n"
#endif