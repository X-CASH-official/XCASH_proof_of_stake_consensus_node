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
  size_t count = 0;

  // iniltize the global variables
  xcash_wallet_public_address = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  consensus_node_add_blocks_to_network = (char*)calloc(BUFFER_SIZE,sizeof(char));
  current_consensus_nodes_IP_address = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  main_nodes_public_address = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  server_message = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  vote_round_change_timeout = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  vote_next_round_true = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  vote_next_round_false = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  current_round_part = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  current_round_part_backup_node = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // check if the memory needed was allocated on the heap successfully
  if (xcash_wallet_public_address == NULL || consensus_node_add_blocks_to_network == NULL || current_consensus_nodes_IP_address == NULL || main_nodes_public_address == NULL || server_message == NULL || vote_round_change_timeout == NULL || vote_next_round_true == NULL || vote_next_round_false == NULL || current_round_part == NULL || current_round_part_backup_node == NULL)
  {
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
    if (vote_round_change_timeout != NULL)
    {
      pointer_reset(vote_round_change_timeout);
    }
    if (vote_next_round_true != NULL)
    {
      pointer_reset(vote_next_round_true);
    }
    if (vote_next_round_false != NULL)
    {
      pointer_reset(vote_next_round_false);
    }
    if (current_round_part != NULL)
    {
      pointer_reset(current_round_part);
    }
    if (current_round_part_backup_node != NULL)
    {
      pointer_reset(current_round_part_backup_node);
    }
    return 0;
  } 

  // set the check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_settings and the check_if_consensus_node_is_offline_timer_settings
  check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_settings = 0;
  check_if_consensus_node_is_offline_timer_settings = 0;

  // set the consensus_node_add_blocks_to_network to 0
  memcpy(consensus_node_add_blocks_to_network,"0",1);

  // initialize the block_verifiers_list struct 
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    block_verifiers_list.block_verifiers_name[count] = (char*)calloc(BLOCK_VERIFIERS_NAME_TOTAL_LENGTH+1,sizeof(char));
    block_verifiers_list.block_verifiers_public_address[count] = (char*)calloc(XCASH_WALLET_LENGTH+1,sizeof(char));
    block_verifiers_list.block_verifiers_IP_address[count] = (char*)calloc(BLOCK_VERIFIERS_IP_ADDRESS_TOTAL_LENGTH+1,sizeof(char));
  }

  // initialize the block_validation_nodes_list struct 
  for (count = 0; count < BLOCK_VALIDATION_NODES_AMOUNT; count++)
  {
    block_validation_nodes_list.block_validation_nodes_public_address[count] = (char*)calloc(XCASH_WALLET_LENGTH+1,sizeof(char));
    block_validation_nodes_list.block_validation_nodes_IP_address[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
  }

  // initialize the VRF_data_block_verifiers struct 
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    VRF_data_block_verifiers.public_address[count] = (char*)calloc(XCASH_WALLET_LENGTH+1,sizeof(char));
    VRF_data_block_verifiers.vrf_public_key_round_part_1[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    VRF_data_block_verifiers.vrf_alpha_string_round_part_1[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    VRF_data_block_verifiers.vrf_proof_round_part_1[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    VRF_data_block_verifiers.vrf_beta_string_round_part_1[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    VRF_data_block_verifiers.vrf_public_key_round_part_2[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    VRF_data_block_verifiers.vrf_alpha_string_round_part_2[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    VRF_data_block_verifiers.vrf_proof_round_part_2[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    VRF_data_block_verifiers.vrf_beta_string_round_part_2[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    VRF_data_block_verifiers.vrf_public_key_round_part_3[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    VRF_data_block_verifiers.vrf_alpha_string_round_part_3[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    VRF_data_block_verifiers.vrf_proof_round_part_3[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    VRF_data_block_verifiers.vrf_beta_string_round_part_3[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
  }

  // initialize the VRF_data struct 
  VRF_data.vrf_public_key_round_part_1 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  VRF_data.vrf_alpha_string_round_part_1 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  VRF_data.vrf_proof_round_part_1 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  VRF_data.vrf_beta_string_round_part_1 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  VRF_data.vrf_public_key_round_part_2 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  VRF_data.vrf_alpha_string_round_part_2 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  VRF_data.vrf_proof_round_part_2 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  VRF_data.vrf_beta_string_round_part_2 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  VRF_data.vrf_public_key_round_part_3 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  VRF_data.vrf_alpha_string_round_part_3 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  VRF_data.vrf_proof_round_part_3 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  VRF_data.vrf_beta_string_round_part_3 = (char*)calloc(BUFFER_SIZE,sizeof(char));

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

  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char)); 



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
    color_print("Could not get the wallets public address\n","red");
    mongoc_client_destroy(database_client);
    mongoc_client_pool_destroy(database_client_thread_pool);
    mongoc_uri_destroy(uri_thread_pool);
    mongoc_cleanup();
    exit(0);
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
    exit(0);
  }

  // get the block verifiers list
  if (get_block_verifiers_list() == 0)
  {
    color_print("Could not get the current block verifiers list\n","red");
    mongoc_client_destroy(database_client);
    mongoc_client_pool_destroy(database_client_thread_pool);
    mongoc_uri_destroy(uri_thread_pool);
    mongoc_cleanup();
    exit(0);
  }

  // get the current consensus node
  current_consensus_node_settings = get_current_consensus_node();
  if (current_consensus_node_settings == 0)
  {
    // start the check_if_consensus_node_is_offline_timer
    check_if_consensus_node_is_offline_timer_settings = 1;
    if (pthread_create(&check_if_consensus_node_is_offline_timer_thread_id, NULL, &check_if_consensus_node_is_offline_timer, NULL) != 0)
    {
      color_print("Could not start the check_if_consensus_node_is_offline_timer\n","red");
      mongoc_client_destroy(database_client);
      mongoc_client_pool_destroy(database_client_thread_pool);
      mongoc_uri_destroy(uri_thread_pool);
      mongoc_cleanup();
      exit(0);
    }    
    if (pthread_detach(check_if_consensus_node_is_offline_timer_thread_id) != 0)
    {
      color_print("Could not set the check_if_consensus_node_is_offline_timer in detach mode\n","red");
      mongoc_client_destroy(database_client);
      mongoc_client_pool_destroy(database_client_thread_pool);
      mongoc_uri_destroy(uri_thread_pool);
      mongoc_cleanup();
      exit(0);
    }
  }
  else
  {    
    // start the check_if_consensus_node_needs_to_add_a_block_to_the_network_timer
    check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_settings = 1;
    if (pthread_create(&check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_thread_id, NULL, &check_if_consensus_node_needs_to_add_a_block_to_the_network_timer, NULL) != 0)
    {
      color_print("Could not start the check_if_consensus_node_is_offline_timer\n","red");
      mongoc_client_destroy(database_client);
      mongoc_client_pool_destroy(database_client_thread_pool);
      mongoc_uri_destroy(uri_thread_pool);
      mongoc_cleanup();
      exit(0);
    }    
    if (pthread_detach(check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_thread_id) != 0)
    {
      color_print("Could not set the check_if_consensus_node_is_offline_timer in detach mode\n","red");
      mongoc_client_destroy(database_client);
      mongoc_client_pool_destroy(database_client_thread_pool);
      mongoc_uri_destroy(uri_thread_pool);
      mongoc_cleanup();
      exit(0);
    }
    // start the new round by sending all of the block verifiers the CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS message and the main node the CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND message
  }
  

  


  // start the server
  if (create_server(1) == 0)
  {
    color_print("Could not start the server","red");
    mongoc_client_destroy(database_client);
    mongoc_client_pool_destroy(database_client_thread_pool);
    mongoc_uri_destroy(uri_thread_pool);
    mongoc_cleanup();
    exit(0);
  }

  mongoc_client_destroy(database_client);
  mongoc_client_pool_destroy(database_client_thread_pool);
  mongoc_uri_destroy(uri_thread_pool);
  mongoc_cleanup();
  return 0;   
}