#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "string.h"
#include <netdb.h> 
#include "netinet/in.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <time.h> 
#include <mongoc/mongoc.h>
#include <bson/bson.h>

#include "define_macro_functions.h"
#include "define_macros.h"
#include "structures.h"
#include "variables.h"

#include "define_macros_functions.h"
#include "database_functions.h"
#include "file_functions.h"
#include "network_daemon_functions.h"
#include "network_functions.h"
#include "network_security_functions.h"
#include "network_wallet_functions.h"
#include "server_functions.h"
#include "string_functions.h"
#include "thread_functions.h"
#include "thread_server_functions.h"

#include "define_macros_test.h"
#include "variables_test.h"
#include "analysing_code_test.h"
#include "database_functions_test.h"
#include "file_functions_test.h"
#include "network_functions_test.h"
#include "string_functions_test.h"
#include "xcash_proof_of_stake_consensus_node_test.h"

/*
-----------------------------------------------------------------------------------------------------------
Main function
-----------------------------------------------------------------------------------------------------------
*/

int main(int parameters_count, char* parameters[])
{

  // iniltize the random number generator
  srand(time(0));

  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  size_t count = 0;

  // threads
  pthread_t thread_id;

  // define macros
  #define pointer_reset_all \
  free(data); \
  data = NULL; \
  free(xcash_wallet_public_address); \
  xcash_wallet_public_address = NULL; \
  free(consensus_node_add_blocks_to_network); \
  consensus_node_add_blocks_to_network = NULL; \
  free(current_consensus_nodes_IP_address); \
  current_consensus_nodes_IP_address = NULL; \
  free(server_message); \
  server_message = NULL; \
  free(current_round_part); \
  current_round_part = NULL; \
  free(current_round_part_backup_node); \
  current_round_part_backup_node = NULL;

  #define XCASH_PROOF_OF_STAKE_CONSENSUS_NODE_SERVER_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset_all; \
  mongoc_client_destroy(database_client); \
  mongoc_client_pool_destroy(database_client_thread_pool); \
  mongoc_uri_destroy(uri_thread_pool); \
  mongoc_cleanup(); \
  exit(0);


  // iniltize the global variables
  xcash_wallet_public_address = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  consensus_node_add_blocks_to_network = (char*)calloc(BUFFER_SIZE,sizeof(char));
  current_consensus_nodes_IP_address = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  main_nodes_public_address = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  server_message = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  current_round_part = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  current_round_part_backup_node = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL || xcash_wallet_public_address == NULL || consensus_node_add_blocks_to_network == NULL || current_consensus_nodes_IP_address == NULL || main_nodes_public_address == NULL || server_message == NULL || current_round_part == NULL || current_round_part_backup_node == NULL)
  {
    if (data != NULL)
    {
      pointer_reset(data);
    }
    if (xcash_wallet_public_address != NULL)
    {
      pointer_reset(xcash_wallet_public_address);
    }
    if (consensus_node_add_blocks_to_network != NULL)
    {
      pointer_reset(consensus_node_add_blocks_to_network);
    }
    if (current_consensus_nodes_IP_address != NULL)
    {
      pointer_reset(current_consensus_nodes_IP_address);
    }
    if (main_nodes_public_address != NULL)
    {
      pointer_reset(main_nodes_public_address);
    }
    if (server_message != NULL)
    {
      pointer_reset(server_message);
    }
    if (current_round_part != NULL)
    {
      pointer_reset(current_round_part);
    }
    if (current_round_part_backup_node != NULL)
    {
      pointer_reset(current_round_part_backup_node);
    }
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  } 

  // set the consensus_node_add_blocks_to_network to 0
  memcpy(consensus_node_add_blocks_to_network,"0",1);

  // initialize the block_verifiers_list struct 
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    block_verifiers_list.block_verifiers_name[count] = (char*)calloc(BLOCK_VERIFIERS_NAME_TOTAL_LENGTH+1,sizeof(char));
    block_verifiers_list.block_verifiers_public_address[count] = (char*)calloc(XCASH_WALLET_LENGTH+1,sizeof(char));
    block_verifiers_list.block_verifiers_IP_address[count] = (char*)calloc(BLOCK_VERIFIERS_IP_ADDRESS_TOTAL_LENGTH+1,sizeof(char));

    // check if the memory needed was allocated on the heap successfully
    if (block_verifiers_list.block_verifiers_name[count] == NULL || block_verifiers_list.block_verifiers_public_address[count] == NULL || block_verifiers_list.block_verifiers_IP_address[count] == NULL)
    {
      color_print("Could not allocate the memory needed on the heap","red");
      exit(0);
    }
  }

  // initialize the block_validation_nodes_list struct 
  for (count = 0; count < BLOCK_VALIDATION_NODES_AMOUNT; count++)
  {
    block_validation_nodes_list.block_validation_nodes_public_address[count] = (char*)calloc(XCASH_WALLET_LENGTH+1,sizeof(char));
    block_validation_nodes_list.block_validation_nodes_IP_address[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));

    // check if the memory needed was allocated on the heap successfully
    if (block_validation_nodes_list.block_validation_nodes_public_address[count] == NULL || block_validation_nodes_list.block_validation_nodes_IP_address[count] == NULL)
    {
      color_print("Could not allocate the memory needed on the heap","red");
      exit(0);
    }
  }  

  // initialize the trusted_block_verifiers struct 
  for (count = 0; count < TRUSTED_BLOCK_VERIFIERS_AMOUNT; count++)
  {
    trusted_block_verifiers.trusted_block_verifiers_public_address[count] = (char*)calloc(XCASH_WALLET_LENGTH+1,sizeof(char));

    // check if the memory needed was allocated on the heap successfully
    if (trusted_block_verifiers.trusted_block_verifiers_public_address[count] == NULL)
    {
      color_print("Could not allocate the memory needed on the heap","red");
      exit(0);
    }
  }

  // initialize the trusted_block_verifiers_VRF_data struct 
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    trusted_block_verifiers_VRF_data.public_address[count] = (char*)calloc(XCASH_WALLET_LENGTH+1,sizeof(char));
    trusted_block_verifiers_VRF_data.vrf_public_key_round_part_1[count] = (char*)calloc(VRF_PUBLIC_KEY_LENGTH+1,sizeof(char));
    trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_1[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    trusted_block_verifiers_VRF_data.vrf_proof_round_part_1[count] = (char*)calloc(VRF_PROOF_LENGTH+1,sizeof(char));
    trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_1[count] = (char*)calloc(VRF_BETA_LENGTH+1,sizeof(char));
    trusted_block_verifiers_VRF_data.vrf_public_key_round_part_2[count] = (char*)calloc(VRF_PUBLIC_KEY_LENGTH+1,sizeof(char));
    trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_2[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    trusted_block_verifiers_VRF_data.vrf_proof_round_part_2[count] = (char*)calloc(VRF_PROOF_LENGTH+1,sizeof(char));
    trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_2[count] = (char*)calloc(VRF_BETA_LENGTH+1,sizeof(char));
    trusted_block_verifiers_VRF_data.vrf_public_key_round_part_3[count] = (char*)calloc(VRF_PUBLIC_KEY_LENGTH+1,sizeof(char));
    trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_3[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    trusted_block_verifiers_VRF_data.vrf_proof_round_part_3[count] = (char*)calloc(VRF_PROOF_LENGTH+1,sizeof(char));
    trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_3[count] = (char*)calloc(VRF_BETA_LENGTH+1,sizeof(char));
    trusted_block_verifiers_VRF_data.block_blob[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    trusted_block_verifiers_VRF_data.data_hash[count] = (char*)calloc(DATA_HASH_LENGTH,sizeof(char));

    // check if the memory needed was allocated on the heap successfully
    if (trusted_block_verifiers_VRF_data.public_address[count] == NULL || trusted_block_verifiers_VRF_data.vrf_public_key_round_part_1[count] == NULL  || trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_1[count] == NULL  || trusted_block_verifiers_VRF_data.vrf_proof_round_part_1[count] == NULL  || trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_1[count] == NULL || trusted_block_verifiers_VRF_data.vrf_public_key_round_part_2[count] == NULL  || trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_2[count] == NULL  || trusted_block_verifiers_VRF_data.vrf_proof_round_part_2[count] == NULL  || trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_2[count] == NULL || trusted_block_verifiers_VRF_data.vrf_public_key_round_part_3[count] == NULL  || trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_3[count] == NULL  || trusted_block_verifiers_VRF_data.vrf_proof_round_part_3[count] == NULL  || trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_3[count] == NULL || trusted_block_verifiers_VRF_data.block_blob[count] == NULL)
    {
      color_print("Could not allocate the memory needed on the heap","red");
      exit(0);
    }
  }

  // initialize the VRF_data struct 
  VRF_data.vrf_public_key_round_part_1 = (char*)calloc(VRF_PUBLIC_KEY_LENGTH+1,sizeof(char));
  VRF_data.vrf_alpha_string_round_part_1 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  VRF_data.vrf_proof_round_part_1 = (char*)calloc(VRF_PROOF_LENGTH+1,sizeof(char));
  VRF_data.vrf_beta_string_round_part_1 = (char*)calloc(VRF_BETA_LENGTH+1,sizeof(char));
  VRF_data.vrf_public_key_round_part_2 = (char*)calloc(VRF_PUBLIC_KEY_LENGTH+1,sizeof(char));
  VRF_data.vrf_alpha_string_round_part_2 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  VRF_data.vrf_proof_round_part_2 = (char*)calloc(VRF_PROOF_LENGTH+1,sizeof(char));
  VRF_data.vrf_beta_string_round_part_2 = (char*)calloc(VRF_BETA_LENGTH+1,sizeof(char));
  VRF_data.vrf_public_key_round_part_3 = (char*)calloc(VRF_PUBLIC_KEY_LENGTH+1,sizeof(char));
  VRF_data.vrf_alpha_string_round_part_3 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  VRF_data.vrf_proof_round_part_3 = (char*)calloc(VRF_PROOF_LENGTH+1,sizeof(char));
  VRF_data.vrf_beta_string_round_part_3 = (char*)calloc(VRF_BETA_LENGTH+1,sizeof(char));
  VRF_data.block_blob = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // check if the memory needed was allocated on the heap successfully
  if (VRF_data.vrf_public_key_round_part_1 == NULL || VRF_data.vrf_alpha_string_round_part_1 == NULL || VRF_data.vrf_proof_round_part_1 == NULL || VRF_data.vrf_beta_string_round_part_1 == NULL || VRF_data.vrf_public_key_round_part_2 == NULL || VRF_data.vrf_alpha_string_round_part_2 == NULL || VRF_data.vrf_proof_round_part_2 == NULL || VRF_data.vrf_beta_string_round_part_2 == NULL || VRF_data.vrf_public_key_round_part_3 == NULL || VRF_data.vrf_alpha_string_round_part_3 == NULL || VRF_data.vrf_proof_round_part_3 == NULL || VRF_data.vrf_beta_string_round_part_3 == NULL || VRF_data.block_blob == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // initialize the blockchain_data struct 
  blockchain_data.network_version_data = (char*)calloc(BLOCKCHAIN_DATA_NETWORK_VERSION_DATA_SIZE,sizeof(char));
  blockchain_data.timestamp_data = (char*)calloc(BLOCKCHAIN_DATA_TIMESTAMP_DATA_SIZE,sizeof(char));
  blockchain_data.previous_block_hash_data = (char*)calloc(BLOCKCHAIN_DATA_PREVIOUS_BLOCK_HASH_DATA_SIZE,sizeof(char));
  blockchain_data.nonce_data = (char*)calloc(BLOCKCHAIN_DATA_NONCE_DATA_SIZE,sizeof(char));
  blockchain_data.block_reward_transaction_version_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCK_REWARD_TRANSACTION_VERSION_DATA_SIZE,sizeof(char));
  blockchain_data.unlock_block_data = (char*)calloc(BLOCKCHAIN_DATA_UNLOCK_BLOCK_DATA_SIZE,sizeof(char));
  blockchain_data.block_reward_input_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCK_REWARD_INPUT_DATA_SIZE,sizeof(char));
  blockchain_data.vin_type_data = (char*)calloc(BLOCKCHAIN_DATA_VIN_TYPE_DATA_SIZE,sizeof(char));
  blockchain_data.block_height_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCK_HEIGHT_DATA_SIZE,sizeof(char));
  blockchain_data.block_reward_output_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCK_REWARD_OUTPUT_DATA_SIZE,sizeof(char));
  blockchain_data.block_reward_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCK_REWARD_DATA_SIZE,sizeof(char));
  blockchain_data.stealth_address_output_tag_data = (char*)calloc(BLOCKCHAIN_DATA_STEALTH_ADDRESS_OUTPUT_TAG_DATA_SIZE,sizeof(char));
  blockchain_data.stealth_address_output_data = (char*)calloc(BLOCKCHAIN_DATA_STEALTH_ADDRESS_OUTPUT_DATA_SIZE,sizeof(char));
  blockchain_data.extra_bytes_size_data = (char*)calloc(BLOCKCHAIN_DATA_EXTRA_BYTES_SIZE_DATA_SIZE,sizeof(char));
  blockchain_data.transaction_public_key_tag_data = (char*)calloc(BLOCKCHAIN_DATA_TRANSACTION_PUBLIC_KEY_TAG_DATA_SIZE,sizeof(char));
  blockchain_data.transaction_public_key_data = (char*)calloc(BLOCKCHAIN_DATA_TRANSACTION_PUBLIC_KEY_DATA_SIZE,sizeof(char));
  blockchain_data.extra_nonce_tag_data = (char*)calloc(BLOCKCHAIN_DATA_EXTRA_NONCE_TAG_DATA_SIZE,sizeof(char));
  blockchain_data.reserve_bytes_size_data = (char*)calloc(BLOCKCHAIN_DATA_RESERVE_BYTES_SIZE_DATA_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.block_producer_delegates_name_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_DELEGATES_NAME_DATA_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.block_producer_delegates_name = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_DELEGATES_NAME_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.block_producer_public_address_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_PUBLIC_ADDRESS_DATA_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.block_producer_public_address = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_PUBLIC_ADDRESS_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.block_producer_node_backup_count_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_NODE_BACKUP_COUNT_DATA_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.block_producer_node_backup_count = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_NODE_BACKUP_COUNT_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.block_producer_backup_nodes_names_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_BACKUP_NODES_NAMES_DATA_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.block_producer_backup_nodes_names = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_BACKUP_NODES_NAMES_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_delegates_name_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_DELEGATES_NAME_DATA_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_delegates_name = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_DELEGATES_NAME_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_public_address_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_PUBLIC_ADDRESS_DATA_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_public_address = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_PUBLIC_ADDRESS_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_node_backup_count_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_NODE_BACKUP_COUNT_DATA_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_node_backup_count = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_NODE_BACKUP_COUNT_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_backup_nodes_names_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_BACKUP_NODES_NAMES_DATA_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_backup_nodes_names = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_BACKUP_NODES_NAMES_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_delegates_name_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_DELEGATES_NAME_DATA_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_delegates_name = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_DELEGATES_NAME_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_public_address_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_PUBLIC_ADDRESS_DATA_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_public_address = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_PUBLIC_ADDRESS_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_node_backup_count_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_NODE_BACKUP_COUNT_DATA_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_node_backup_count = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_NODE_BACKUP_COUNT_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_backup_nodes_names_data = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_BACKUP_NODES_NAMES_DATA_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_backup_nodes_names = (char*)calloc(BLOCKCHAIN_DATA_BLOCKCHAIN_RESERVE_BYTES_BLOCK_PRODUCER_BACKUP_NODES_NAMES_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_public_key_round_part_1 = (char*)calloc(VRF_PUBLIC_KEY_LENGTH,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_round_part_1 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_proof_round_part_1 = (char*)calloc(VRF_PROOF_LENGTH,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_beta_string_round_part_1 = (char*)calloc(VRF_BETA_LENGTH,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_data_round_part_1 = (char*)calloc(11,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_public_key_round_part_2 = (char*)calloc(VRF_PUBLIC_KEY_LENGTH,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_round_part_2 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_proof_round_part_2 = (char*)calloc(VRF_PROOF_LENGTH,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_beta_string_round_part_2 = (char*)calloc(VRF_BETA_LENGTH,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_data_round_part_2 = (char*)calloc(11,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_public_key_round_part_3 = (char*)calloc(VRF_PUBLIC_KEY_LENGTH,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_round_part_3 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_proof_round_part_3 = (char*)calloc(VRF_PROOF_LENGTH,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_beta_string_round_part_3 = (char*)calloc(VRF_BETA_LENGTH,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_data_round_part_3 = (char*)calloc(11,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.vrf_data = (char*)calloc(11,sizeof(char));
  blockchain_data.blockchain_reserve_bytes.previous_block_hash_data = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // check if the memory needed was allocated on the heap successfully
  if (blockchain_data.network_version_data == NULL || blockchain_data.timestamp_data == NULL || blockchain_data.previous_block_hash_data == NULL || blockchain_data.nonce_data == NULL || blockchain_data.block_reward_transaction_version_data == NULL || blockchain_data.unlock_block_data == NULL || blockchain_data.block_reward_input_data == NULL || blockchain_data.vin_type_data == NULL || blockchain_data.block_height_data == NULL || blockchain_data.block_reward_output_data == NULL || blockchain_data.block_reward_data == NULL || blockchain_data.stealth_address_output_tag_data == NULL || blockchain_data.stealth_address_output_data == NULL || blockchain_data.extra_bytes_size_data == NULL || blockchain_data.transaction_public_key_tag_data == NULL || blockchain_data.transaction_public_key_data == NULL || blockchain_data.extra_nonce_tag_data == NULL || blockchain_data.reserve_bytes_size_data == NULL || blockchain_data.blockchain_reserve_bytes.block_producer_delegates_name_data == NULL || blockchain_data.blockchain_reserve_bytes.block_producer_delegates_name == NULL || blockchain_data.blockchain_reserve_bytes.block_producer_public_address_data == NULL || blockchain_data.blockchain_reserve_bytes.block_producer_public_address == NULL || blockchain_data.blockchain_reserve_bytes.block_producer_node_backup_count_data == NULL || blockchain_data.blockchain_reserve_bytes.block_producer_backup_nodes_names_data == NULL || blockchain_data.blockchain_reserve_bytes.block_producer_backup_nodes_names == NULL || blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_delegates_name_data == NULL || blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_delegates_name == NULL || blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_public_address_data == NULL || blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_public_address == NULL || blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_node_backup_count_data == NULL || blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_backup_nodes_names_data == NULL || blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_backup_nodes_names == NULL || blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_delegates_name_data == NULL || blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_delegates_name == NULL || blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_public_address_data == NULL || blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_public_address == NULL || blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_node_backup_count_data == NULL || blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_backup_nodes_names_data == NULL || blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_backup_nodes_names == NULL || blockchain_data.blockchain_reserve_bytes.vrf_public_key_round_part_1 == NULL || blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_round_part_1 == NULL || blockchain_data.blockchain_reserve_bytes.vrf_proof_round_part_1 == NULL || blockchain_data.blockchain_reserve_bytes.vrf_beta_string_round_part_1 == NULL || blockchain_data.blockchain_reserve_bytes.vrf_public_key_round_part_2 == NULL || blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_round_part_2 == NULL || blockchain_data.blockchain_reserve_bytes.vrf_proof_round_part_2 == NULL || blockchain_data.blockchain_reserve_bytes.vrf_beta_string_round_part_2 == NULL || blockchain_data.blockchain_reserve_bytes.vrf_public_key_round_part_3 == NULL || blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_round_part_3 == NULL || blockchain_data.blockchain_reserve_bytes.vrf_proof_round_part_3 == NULL || blockchain_data.blockchain_reserve_bytes.vrf_beta_string_round_part_3 == NULL || blockchain_data.blockchain_reserve_bytes.previous_block_hash_data == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }
  for (count = 0; count < BLOCK_VALIDATION_NODES_AMOUNT; count++)
  {
    blockchain_data.blockchain_reserve_bytes.block_validation_node_signature_data[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    blockchain_data.blockchain_reserve_bytes.block_validation_node_signature[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));

    // check if the memory needed was allocated on the heap successfully
    if (blockchain_data.blockchain_reserve_bytes.block_validation_node_signature_data[count] == NULL || blockchain_data.blockchain_reserve_bytes.block_validation_node_signature[count] == NULL)
    {
      color_print("Could not allocate the memory needed on the heap","red");
      exit(0);
    }
  }
  blockchain_data.ringct_version_data = (char*)calloc(3,sizeof(char));
  blockchain_data.transaction_amount_data = (char*)calloc(5,sizeof(char));
  for (count = 0; count < 1000000; count++)
  {
    blockchain_data.transactions[count] = (char*)calloc(65,sizeof(char));

    // check if the memory needed was allocated on the heap successfully
    if (blockchain_data.transactions[count] == NULL)
    {
      color_print("Could not allocate the memory needed on the heap","red");
      exit(0);
    }
  }

  // initialize the reserve_proofs_list struct 
  for (count = 0; count < RESERVE_PROOFS_LIST_MAXIMUM_AMOUNT; count++)
  {
    reserve_proofs_list.public_address_created_reserve_proof[count] = (char*)calloc(XCASH_WALLET_LENGTH+1,sizeof(char));
    reserve_proofs_list.public_address_voted_for[count] = (char*)calloc(XCASH_WALLET_LENGTH+1,sizeof(char));
    reserve_proofs_list.reserve_proof[count] = (char*)calloc(10000+1,sizeof(char));
    reserve_proofs_list.amount[count] = 0;
    reserve_proofs_list.number[count] = 0;

    // check if the memory needed was allocated on the heap successfully
    if (reserve_proofs_list.public_address_created_reserve_proof[count] == NULL || reserve_proofs_list.public_address_voted_for[count] == NULL || reserve_proofs_list.reserve_proof[count] == NULL)
    {
      color_print("Could not allocate the memory needed on the heap","red");
      exit(0);
    }
  }
  reserve_proofs_list.count = 0;

  // initialize the mainnode_timeout struct 
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    mainnode_timeout.block_verifiers_public_address[count] = (char*)calloc(XCASH_WALLET_LENGTH+1,sizeof(char));

    // check if the memory needed was allocated on the heap successfully
    if (mainnode_timeout.block_verifiers_public_address[count] == NULL)
    {
      color_print("Could not allocate the memory needed on the heap","red");
      exit(0);
    }
  }
  mainnode_timeout.vote_round_change_timeout = 0;

  // initialize the mainnode_timeout struct 
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    node_to_node_vote.block_verifiers_public_address_vote_next_round_true[count] = (char*)calloc(XCASH_WALLET_LENGTH+1,sizeof(char));
    node_to_node_vote.block_verifiers_public_address_vote_next_round_false[count] = (char*)calloc(XCASH_WALLET_LENGTH+1,sizeof(char));

    // check if the memory needed was allocated on the heap successfully
    if (node_to_node_vote.block_verifiers_public_address_vote_next_round_true[count] == NULL || node_to_node_vote.block_verifiers_public_address_vote_next_round_false[count] == NULL)
    {
      color_print("Could not allocate the memory needed on the heap","red");
      exit(0);
    }
  }
  node_to_node_vote.vote_next_round_true = 0;
  node_to_node_vote.vote_next_round_false = 0;

  // Add each block validation nodes data to the block_validation_nodes_list struct

  // Add each block validation nodes data to the block_validation_nodes_list struct

  // initialize the database connection
  mongoc_init();

  // create a connection to the database
  if (create_database_connection() == 0)
  {
    color_print("Could not create a connection for the database\n","red");
    mongoc_cleanup();
    exit(0);
  }

  // create a pool of connections for the database
  mongoc_uri_t* uri_thread_pool;
  bson_error_t error;
  uri_thread_pool = mongoc_uri_new_with_error(DATABASE_CONNECTION, &error);
  if (!uri_thread_pool)
  {
    color_print("Could not create a pool of connections for the database\n","red");
    mongoc_client_destroy(database_client);
    mongoc_cleanup();
    exit(0);
  }
  database_client_thread_pool = mongoc_client_pool_new(uri_thread_pool);
  if (!database_client_thread_pool)
  {
    color_print("Could not create a thread pool for the database\n","red");
    mongoc_client_destroy(database_client);
    mongoc_uri_destroy(uri_thread_pool);
    mongoc_cleanup();
    exit(0);
  }

  // write the message
  color_print("X-CASH Proof Of Stake - Consensus Node, Version 1.0.0\n","green");

  // set the current_round_part, current_round_part_backup_node and server message, this way the node will start at the begining of a round
  memset(current_round_part,0,strnlen(current_round_part,BUFFER_SIZE));
  memset(current_round_part_backup_node,0,strnlen(current_round_part_backup_node,BUFFER_SIZE));
  memcpy(current_round_part,"1",1);
  memcpy(current_round_part_backup_node,"0",1);
  memset(server_message,0,strnlen(server_message,BUFFER_SIZE));
  memcpy(server_message,"",1);

  // get the wallets public address
  printf("Getting the public address\n\n");
  if (get_public_address(0) == 1)
  {  
    // print the public address
    memcpy(data,"Successfully received the public address:",41);
    memcpy(data+41,xcash_wallet_public_address,XCASH_WALLET_LENGTH);
    memcpy(data+41+XCASH_WALLET_LENGTH,"\n",1);
    color_print(data,"green");
  }
  else
  {
    XCASH_PROOF_OF_STAKE_CONSENSUS_NODE_SERVER_ERROR("Could not get the wallets public address");
  }
  
  // check if the program needs to run the test
  if (parameters_count == 2)
  {
    if (strncmp(parameters[1],"--test",BUFFER_SIZE) == 0)
    {
      test();
    }
    else
    {
      color_print("Invalid parameters\n","red");
      printf(INVALID_PARAMETERS_ERROR_MESSAGE);
    }
    mongoc_client_destroy(database_client);
    mongoc_client_pool_destroy(database_client_thread_pool);
    mongoc_uri_destroy(uri_thread_pool);
    mongoc_cleanup();
    pointer_reset_all;
    exit(0);
  }

  // get the block verifiers list
  if (get_block_verifiers_list() == 0)
  {
    XCASH_PROOF_OF_STAKE_CONSENSUS_NODE_SERVER_ERROR("Could not get the current block verifiers list");
  }

  // get the current consensus node
  current_consensus_node_settings = get_current_consensus_node();
  if (current_consensus_node_settings == 0)
  {
    // start the check_if_consensus_node_is_offline_timer
    check_if_consensus_node_is_offline_timer_settings.settings = 1;

    // stop the check_if_consensus_node_needs_to_add_a_block_to_the_network_timer
    check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_settings.settings = 0;

    // stop the update_block_verifiers_timer_settings
    update_block_verifiers_timer_settings.settings = 0;
  }
  else
  {  
    // stop the check_if_consensus_node_is_offline_timer
    check_if_consensus_node_is_offline_timer_settings.settings = 0;

    // start the check_if_consensus_node_needs_to_add_a_block_to_the_network_timer
    check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_settings.settings = 1;

    // start the update_block_verifiers_timer_settings
    update_block_verifiers_timer_settings.settings = 1;
  }

  // start the check_if_consensus_node_is_offline_timer
  if (pthread_create(&check_if_consensus_node_is_offline_timer_settings.thread_id, NULL, &check_if_consensus_node_is_offline_timer, NULL) != 0)
  {
    XCASH_PROOF_OF_STAKE_CONSENSUS_NODE_SERVER_ERROR("Could not start the check_if_consensus_node_is_offline_timer");
  }    
  if (pthread_detach(check_if_consensus_node_is_offline_timer_settings.thread_id) != 0)
  {
    XCASH_PROOF_OF_STAKE_CONSENSUS_NODE_SERVER_ERROR("Could not set the check_if_consensus_node_is_offline_timer in detach mode\n");
  } 

  // start the check_if_consensus_node_needs_to_add_a_block_to_the_network_timer
  if (pthread_create(&check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_settings.thread_id, NULL, &check_if_consensus_node_needs_to_add_a_block_to_the_network_timer, NULL) != 0)
  {
    XCASH_PROOF_OF_STAKE_CONSENSUS_NODE_SERVER_ERROR("Could not start the check_if_consensus_node_is_offline_timer");
  }    
  if (pthread_detach(check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_settings.thread_id) != 0)
  {
    XCASH_PROOF_OF_STAKE_CONSENSUS_NODE_SERVER_ERROR("Could not start the check_if_consensus_node_is_offline_timer");
  }

  // start the update_block_verifiers_timer
  if (pthread_create(&update_block_verifiers_timer_settings.thread_id, NULL, &update_block_verifiers_timer, NULL) != 0)
  {
    XCASH_PROOF_OF_STAKE_CONSENSUS_NODE_SERVER_ERROR("Could not start the check_if_consensus_node_is_offline_timer");
  }    
  if (pthread_detach(update_block_verifiers_timer_settings.thread_id) != 0)
  {
    XCASH_PROOF_OF_STAKE_CONSENSUS_NODE_SERVER_ERROR("Could not start the check_if_consensus_node_is_offline_timer");
  }

  if (current_consensus_node_settings == 1)
  {
    start:

    // start the new round by sending all of the block verifiers the CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS message and the main node the CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND message
    // calculate the current_round_part and current_round_part_backup_node 
    if (mainode_consensus() == 0)
    {
      XCASH_PROOF_OF_STAKE_CONSENSUS_NODE_SERVER_ERROR("Could not get the current_round_part and current_round_part_backup_node");
      // add another block to the network since the next round could not be started
      consensus_node_create_new_block();
      goto start;
    }

    // send the main nodes public address to the block verifiers
    if (send_data_socket_consensus_node_to_node() == 0)
    {
      XCASH_PROOF_OF_STAKE_CONSENSUS_NODE_SERVER_ERROR("Could not send the main nodes public address to the block verifiers");
      // add another block to the network since the next round could not be started
      consensus_node_create_new_block();
      goto start;
    }

    // let the main node know they are the main node and they need to start the part of the round
    if (send_data_socket_consensus_node_to_mainnode() == 0)
    {
      XCASH_PROOF_OF_STAKE_CONSENSUS_NODE_SERVER_ERROR("Could not send the main nodes public address to the block verifiers");
      // add another block to the network since the next round could not be started
      consensus_node_create_new_block();
      goto start;
    }

    // start the receive_votes_from_nodes_timeout
    if (pthread_create(&thread_id, NULL, &receive_votes_from_nodes_timeout_thread, NULL) != 0)
    {
      XCASH_PROOF_OF_STAKE_CONSENSUS_NODE_SERVER_ERROR("Could not start the receive_votes_from_nodes_timeout");
      // add another block to the network since the next round could not be started
      consensus_node_create_new_block();
      goto start;
    }
    // set the thread to detach once completed, since we do not need to use anything it will return
    if (pthread_detach(thread_id) != 0)
    {
      XCASH_PROOF_OF_STAKE_CONSENSUS_NODE_SERVER_ERROR("Could not start the receive_votes_from_nodes_timeout");
      // add another block to the network since the next round could not be started
      consensus_node_create_new_block();
      goto start;
    }

    // set the server message
    memset(server_message,0,strnlen(server_message,BUFFER_SIZE));
    memcpy(server_message,"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE|NODES_TO_CONSENSUS_NODE_VOTE_RESULTS",98);
  }

  // start the server
  if (create_server(1) == 0)
  {
    XCASH_PROOF_OF_STAKE_CONSENSUS_NODE_SERVER_ERROR("Could not start the server");
  }

  mongoc_client_destroy(database_client);
  mongoc_client_pool_destroy(database_client_thread_pool);
  mongoc_uri_destroy(uri_thread_pool);
  mongoc_cleanup();
  pointer_reset_all;
  return 0; 

  #undef pointer_reset_all
  #undef XCASH_PROOF_OF_STAKE_CONSENSUS_NODE_SERVER_ERROR
}