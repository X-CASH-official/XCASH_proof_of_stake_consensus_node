#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <mongoc/mongoc.h>
#include <bson/bson.h>

#include "define_macro_functions.h"
#include "define_macros.h"
#include "variables.h"
#include "structures.h"

#include "define_macros_functions.h"
#include "database_functions.h"
#include "network_functions.h"
#include "network_security_functions.h"
#include "server_functions.h"
#include "thread_server_functions.h"

/*
-----------------------------------------------------------------------------------------------------------
Functions
-----------------------------------------------------------------------------------------------------------
*/

/*
-----------------------------------------------------------------------------------------------------------
Name: total_connection_time_thread
Description: Closes the forked process after a certain connection timeout
Parameters:
  parameters - A pointer to the total_connection_time_thread_parameters struct
  struct total_connection_time_thread_parameters
    process_id - The process id of the forked process
    client_address - The client's IP address for the forked process
    port - The client's connected port for the forked process
    data_received - 1 if data was received in the timeout time, otherwise 0
    message_settings - 1 to print the messages, otherwise 0. This is used for the testing flag to not print any success or error messages
Return: NULL
-----------------------------------------------------------------------------------------------------------
*/

void* total_connection_time_thread(void* parameters)
{ 
  // Variables
  char* string = (char*)calloc(BUFFER_SIZE,sizeof(char));
  struct total_connection_time_thread_parameters* data = parameters;
  int client_address_length = strnlen(data->client_address,BUFFER_SIZE);
  int data_port_length = strnlen(data->port,BUFFER_SIZE);

  // check if the memory needed was allocated on the heap successfully
  if (string == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  sleep(TOTAL_CONNECTION_TIME_SETTINGS);    
  if (data->message_settings == 1)
  {
    printf("Total connection time has been reached for %s on port %s\n", data->client_address,data->port); 
    if (data->data_received == 1)
    {
      memcpy(string,"Client at ",10);
      memcpy(string+10,data->client_address,client_address_length);
      memcpy(string+10+client_address_length," on port ",9);
      memcpy(string+19+client_address_length,data->port,data_port_length);
      memcpy(string+19+client_address_length+data_port_length," has sent data in the timeout time",34);
      color_print(string,"green");
    }
    else
    {
      memcpy(string,"Client at ",10);
      memcpy(string+10,data->client_address,client_address_length);
      memcpy(string+10+client_address_length," on port ",9);
      memcpy(string+19+client_address_length,data->port,data_port_length);
      memcpy(string+19+client_address_length+data_port_length," did not send any data in the timeout time",42);
      color_print(string,"red"); 
    }
  }
  pointer_reset(string);
  kill((intptr_t)data->process_id, SIGKILL);  
  pthread_exit((void *)(intptr_t)1);
}


/*
-----------------------------------------------------------------------------------------------------------
Name: mainnode_timeout_thread
Description: Closes the forked process after a certain connection timeout. This is so the node knows if it should send a message to the consensus node that the main node never sent any data, and if a round change should occur
Parameters:
  parameters - A pointer to the mainnode_timeout_thread_parameters struct
  struct mainnode_timeout_thread_parameters
    process_id - The process id of the forked process
    data_received - 1 if the node has received data from the main node, otherwise 0
    main_nodes_public_address - The public address of the main node for that part of the round
    current_round_part - The current round part (1-4).
    current_round_part_backup_node - The current main node in the current round part (0-5)
Return: NULL
-----------------------------------------------------------------------------------------------------------
*/

void* mainnode_timeout_thread(void* parameters)
{
  // Variables
  char* string = (char*)calloc(BUFFER_SIZE,sizeof(char));
  struct mainnode_timeout_thread_parameters* data = parameters;
  size_t main_node_length = strnlen(data->main_node,BUFFER_SIZE);

  // check if the memory needed was allocated on the heap successfully
  if (string == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  sleep(TOTAL_CONNECTION_TIME_SETTINGS_MAIN_NODE_TIMEOUT);  
  printf("Total connection time for the main node has been reached"); 
  if (data->data_received == 1)
  {
    memcpy(string,"Received data from main node, ",30);
    memcpy(string+30,data->main_node,main_node_length);
    memcpy(string+30+main_node_length," backup node number ",20);
    memcpy(string+50+main_node_length,data->current_round_part_backup_node,1);
    memcpy(string+51+main_node_length," in current round part ",23);
    memcpy(string+74+main_node_length,data->current_round_part,1);
    color_print(string,"green");
  }
  else
  {
    memcpy(string,"main node, ",11);
    memcpy(string+11,data->main_node,main_node_length);
    memcpy(string+11+main_node_length," backup node number ",20);
    memcpy(string+31+main_node_length,data->current_round_part_backup_node,1);
    memcpy(string+32+main_node_length," in current round part ",23);
    memcpy(string+55+main_node_length,data->current_round_part,1);
    memcpy(string+56+main_node_length," did not send any data before the timeout",41);
    color_print(string,"red");    
  }
  pointer_reset(string);
  kill((intptr_t)data->process_id, SIGTERM);
  pthread_exit((void *)(intptr_t)1);
}



/*
-----------------------------------------------------------------------------------------------------------
Name: receive_votes_from_nodes_timeout_thread
Description: Counts the votes.
Return: NULL
-----------------------------------------------------------------------------------------------------------
*/

void* receive_votes_from_nodes_timeout_thread()
{  
  // Variables
  size_t count;
  size_t count2;
  size_t counter;
  int settings = 0;
  int settings2 = 0;

  // define macros
  #define DATABASE_COLLECTION "current_round"
  #define MESSAGE "{\"username\":\"xcash\"}"

  #define RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR(settings) \
  color_print(settings,"red"); \
  return 0;

  for (;;)
  {  
  // wait for the BLOCK_VERIFIERS_TOTAL_VOTE_TIME
  sleep(BLOCK_VERIFIERS_TOTAL_VOTE_TIME);

  // read the current_round_part and current_round_part_backup_node from the database
  memset(current_round_part,0,strnlen(current_round_part,BUFFER_SIZE));
  memset(current_round_part_backup_node,0,strnlen(current_round_part_backup_node,BUFFER_SIZE));
  if (read_document_field_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,"current_round_part",current_round_part,0) == 0 || read_document_field_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,"current_round_part_backup_node",current_round_part_backup_node,0) == 0)
  {
     RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR("Could not read the current_round_part or the current_round_part_backup_node from the database\nFunction: receive_votes_from_nodes_timeout_thread");
  }

  // check if the trusted nodes for at least TRUSTED_BLOCK_VERIFIERS_AMOUNT have the same result and get the VRF from the trusted nodes


  // check the mainnode_timeout vote results
  if (mainnode_timeout.vote_round_change_timeout >= BLOCK_VERIFIERS_VALID_AMOUNT)
  {
    // check if at least TRUSTED_BLOCK_VERIFIERS_AMOUNT have voted for a round change due to a main node timeout
    for (count = 0, count2 = 0, counter = 0; count < mainnode_timeout.vote_round_change_timeout; count++)
    {
      for (count2 = 0; count2 < TRUSTED_BLOCK_VERIFIERS_TOTAL_AMOUNT; count2++)
      {
        if (memcmp(mainnode_timeout.block_verifiers_public_address[count],trusted_block_verifiers.trusted_block_verifiers_public_address[count2],XCASH_WALLET_LENGTH) == 0)
        {
          counter++;
        }
      }
    }

    if (counter >= TRUSTED_BLOCK_VERIFIERS_AMOUNT)
    {
      // The main node timeout is valid
      settings = 1;      
    }
    else
    {
      // The main node timeout is invalid
      settings = 2;
    }
  }



  // check if the the node_to_node_vote vote results are false
  if (mainnode_timeout.vote_round_change_timeout < BLOCK_VERIFIERS_VALID_AMOUNT && node_to_node_vote.vote_next_round_false >= BLOCK_VERIFIERS_VALID_AMOUNT)
  {
    // check if at least TRUSTED_BLOCK_VERIFIERS_AMOUNT have voted false
    for (count = 0, count2 = 0, counter = 0; count < node_to_node_vote.vote_next_round_false; count++)
    {
      for (count2 = 0; count2 < TRUSTED_BLOCK_VERIFIERS_TOTAL_AMOUNT; count2++)
      {
        if (memcmp(mainnode_timeout.block_verifiers_public_address[count],trusted_block_verifiers.trusted_block_verifiers_public_address[count2],XCASH_WALLET_LENGTH) == 0)
        {
          counter++;
        }
      }
    }

    // verify the VRF data for the current part of the round and set the result to settings2
    
    
    if (counter >= TRUSTED_BLOCK_VERIFIERS_AMOUNT && settings2 == 1)
    {
      // The vote for false is valid
      settings = 3;
    }
    else
    {
      // The vote for false is invalid
      settings = 4;
    }
  }



  // check if the the node_to_node_vote vote results are true
  if (mainnode_timeout.vote_round_change_timeout < BLOCK_VERIFIERS_VALID_AMOUNT && node_to_node_vote.vote_next_round_true >= BLOCK_VERIFIERS_VALID_AMOUNT)
  {
    // check if at least TRUSTED_BLOCK_VERIFIERS_AMOUNT have voted true
    for (count = 0, count2 = 0, counter = 0; count < node_to_node_vote.vote_next_round_true; count++)
    {
      for (count2 = 0; count2 < TRUSTED_BLOCK_VERIFIERS_TOTAL_AMOUNT; count2++)
      {
        if (memcmp(mainnode_timeout.block_verifiers_public_address[count],trusted_block_verifiers.trusted_block_verifiers_public_address[count2],XCASH_WALLET_LENGTH) == 0)
        {
          counter++;
        }
      }
    }

    // verify the VRF data for the current part of the round and set the result to settings2
    
    
    if (counter >= TRUSTED_BLOCK_VERIFIERS_AMOUNT && settings2 == 1)
    {
      // The vote for true is valid
      settings = 5;
    }
    else
    {
      // The vote for true is invalid
      settings = 6;
    }
  }



  // check if no vote result was greater than BLOCK_VERIFIERS_VALID_AMOUNT
  if (mainnode_timeout.vote_round_change_timeout < BLOCK_VERIFIERS_VALID_AMOUNT && node_to_node_vote.vote_next_round_false < BLOCK_VERIFIERS_VALID_AMOUNT && node_to_node_vote.vote_next_round_true < BLOCK_VERIFIERS_VALID_AMOUNT)
  {
    settings = 7;
  }



  // reset the mainnode_timeout struct
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    memset(mainnode_timeout.block_verifiers_public_address[count],0,strnlen(mainnode_timeout.block_verifiers_public_address[count],XCASH_WALLET_LENGTH+1));
  }
  mainnode_timeout.vote_round_change_timeout = 0;

  // reset the node_to_node_vote struct
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    memset(node_to_node_vote.block_verifiers_public_address_vote_next_round_true[count],0,strnlen(node_to_node_vote.block_verifiers_public_address_vote_next_round_true[count],XCASH_WALLET_LENGTH+1));
    memset(node_to_node_vote.block_verifiers_public_address_vote_next_round_false[count],0,strnlen(node_to_node_vote.block_verifiers_public_address_vote_next_round_false[count],XCASH_WALLET_LENGTH+1));
  }
  node_to_node_vote.vote_next_round_true = 0;
  node_to_node_vote.vote_next_round_false = 0;

  // reset the VRF_data and the trusted_block_verifiers_VRF_data if it is current_round_part 4
  if (memcmp(current_round_part,"4",1) == 0)
  {
    memset(VRF_data.vrf_public_key_round_part_1,0,strnlen(VRF_data.vrf_public_key_round_part_1,BUFFER_SIZE));
    memset(VRF_data.vrf_alpha_string_round_part_1,0,strnlen(VRF_data.vrf_alpha_string_round_part_1,BUFFER_SIZE));
    memset(VRF_data.vrf_proof_round_part_1,0,strnlen(VRF_data.vrf_proof_round_part_1,BUFFER_SIZE));
    memset(VRF_data.vrf_beta_string_round_part_1,0,strnlen(VRF_data.vrf_beta_string_round_part_1,BUFFER_SIZE));
    memset(VRF_data.vrf_public_key_round_part_2,0,strnlen(VRF_data.vrf_public_key_round_part_2,BUFFER_SIZE));
    memset(VRF_data.vrf_alpha_string_round_part_2,0,strnlen(VRF_data.vrf_alpha_string_round_part_2,BUFFER_SIZE));
    memset(VRF_data.vrf_proof_round_part_2,0,strnlen(VRF_data.vrf_proof_round_part_2,BUFFER_SIZE));
    memset(VRF_data.vrf_beta_string_round_part_2,0,strnlen(VRF_data.vrf_beta_string_round_part_2,BUFFER_SIZE));
    memset(VRF_data.vrf_public_key_round_part_3,0,strnlen(VRF_data.vrf_public_key_round_part_3,BUFFER_SIZE));
    memset(VRF_data.vrf_alpha_string_round_part_3,0,strnlen(VRF_data.vrf_alpha_string_round_part_3,BUFFER_SIZE));
    memset(VRF_data.vrf_proof_round_part_3,0,strnlen(VRF_data.vrf_proof_round_part_3,BUFFER_SIZE));
    memset(VRF_data.vrf_beta_string_round_part_3,0,strnlen(VRF_data.vrf_beta_string_round_part_3,BUFFER_SIZE)); 

    for (count = 0; count < TRUSTED_BLOCK_VERIFIERS_AMOUNT; count++)
    {
      memset(trusted_block_verifiers_VRF_data.public_address[count],0,strnlen(trusted_block_verifiers_VRF_data.public_address[count],XCASH_WALLET_LENGTH+1));
      memset(trusted_block_verifiers_VRF_data.vrf_public_key_round_part_1[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_public_key_round_part_1[count],BUFFER_SIZE));
      memset(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_1[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_1[count],BUFFER_SIZE));
      memset(trusted_block_verifiers_VRF_data.vrf_proof_round_part_1[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_proof_round_part_1[count],BUFFER_SIZE));
      memset(trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_1[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_1[count],BUFFER_SIZE));
      memset(trusted_block_verifiers_VRF_data.vrf_public_key_round_part_2[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_public_key_round_part_2[count],BUFFER_SIZE));
      memset(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_2[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_2[count],BUFFER_SIZE));
      memset(trusted_block_verifiers_VRF_data.vrf_proof_round_part_2[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_proof_round_part_2[count],BUFFER_SIZE));
      memset(trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_2[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_2[count],BUFFER_SIZE));
      memset(trusted_block_verifiers_VRF_data.vrf_public_key_round_part_3[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_public_key_round_part_3[count],BUFFER_SIZE));
      memset(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_3[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_3[count],BUFFER_SIZE));
      memset(trusted_block_verifiers_VRF_data.vrf_proof_round_part_3[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_proof_round_part_3[count],BUFFER_SIZE));
      memset(trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_3[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_3[count],BUFFER_SIZE));
    }
  }

  // run the code for the correct settings
  if (settings == 1)
  {
    // The main node timeout is valid

    // start the part of the round over again
    if (send_round_change() == 0)
    {
      // have the consensus node add a block to the network
      consensus_node_create_new_block();
    }
  }
  else if (settings == 2)
  {
    // The main node timeout is invalid

    // set all of the block verifiers block_producer_eligibility to false that voted for the invalid result
    update_block_producer_eligibility(0);

    // start the next round, and for this round have the consensus node add the block to the network
    if (start_next_round(1) == 0)
    {
      // have the consensus node add a block to the network
      consensus_node_create_new_block();
    }
  }
  else if (settings == 3)
  {
    // The vote for false is valid

    // startnew part of round
    if (start_new_part_of_round() == 0)
    {
      // have the consensus node add a block to the network
      consensus_node_create_new_block();
    }
  }
  else if (settings == 4)
  {
    // The vote for false is invalid

    // set all of the block verifiers block_producer_eligibility to false that voted for the invalid result
    update_block_producer_eligibility(1);

    // start the next round, and for this round have the consensus node add the block to the network
    if (start_next_round(1) == 0)
    {
      // have the consensus node add a block to the network
      consensus_node_create_new_block();
    }
  }
  else if (settings == 5)
  {
    // The vote for true is valid

    if (memcmp(current_round_part,"4",1) != 0)
    {
      // start new part of round
      if (start_new_part_of_round() == 0)
      {
        // have the consensus node add a block to the network
        consensus_node_create_new_block();
      }
    }
    else
    {
      // start the next round, and for this round have the block producer block added to the network
      if (start_next_round(0) == 0)
      {
        // have the consensus node add a block to the network
        consensus_node_create_new_block();
      }
    }

    // set the current_round_part and current_round_part_backup_node in the database
    if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,"{\"current_round_part\":\"0\"}",0) == 0 || update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,"{\"current_round_part_backup_node\":\"0\"}",0) == 0)
    {
      RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR("Could not update the current_round_part and current_round_part_backup_node in the database\nFunction: receive_votes_from_nodes_timeout_thread");
    }    
  }
  else if (settings == 6)
  {
    // The vote for true invalid

    // set all of the block verifiers block_producer_eligibility to false that voted for the invalid result
    update_block_producer_eligibility(2);

    // start the next round, and for this round have the consensus node add the block to the network
    if (start_next_round(1) == 0)
    {
      // have the consensus node add a block to the network
      consensus_node_create_new_block();
    }
  }
  else if (settings == 7)
  {
    // no vote result was greater than BLOCK_VERIFIERS_VALID_AMOUNT

    // start the next round, and for this round have the consensus node add the block to the network
    if (start_next_round(1) == 0)
    {
      // have the consensus node add a block to the network
      consensus_node_create_new_block();
    }
  }

  // set the server message
  memset(server_message,0,strnlen(server_message,BUFFER_SIZE));
}

  pthread_exit((void *)(intptr_t)1);

  #undef DATABASE_COLLECTION
  #undef MESSAGE
  #undef RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: check_if_consensus_node_is_offline_timer
Description: Checks if the current conensus node is offline
Return: NULL
-----------------------------------------------------------------------------------------------------------
*/

void* check_if_consensus_node_is_offline_timer()
{ 
  // Constants
  const size_t CONSENSUS_NODES_IP_ADDRESS_LENGTH = strnlen(CONSENSUS_NODES_IP_ADDRESS,BUFFER_SIZE);

  // Variables
  char* message = (char*)calloc(BUFFER_SIZE,sizeof(char));
  int count = 0;

  // check if the memory needed was allocated on the heap successfully
  if (message == NULL)
  {   
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // define macros
  #define DATABASE_COLLECTION "consensus_node"
  #define MESSAGE "{\"username\":\"xcash\"}"

  #define CHECK_IF_CONSENSUS_NODE_IS_OFFLINE_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset(message); \
  return 0;

  for (;;)
  {
    sleep(60);

    while (check_if_consensus_node_is_offline_timer_settings == 1)
    {
      // check if the current consensus node is online
      if (send_data_socket(CONSENSUS_BACKUP_NODES_IP_ADDRESS,SEND_DATA_PORT,"","Check if the current consensus node is online",0) == 0)
      {
        count++;
      }
      else
      {
        count = 0;
      }

      if (count == 5)
      {
        // the current consensus node is offline, so change the consensus nodes
        // update the current consensus node in the database      
        memcpy(message,"{\"current_consensus_node_IP_address\":\"",38);
        memcpy(message+38,CONSENSUS_NODES_IP_ADDRESS,CONSENSUS_NODES_IP_ADDRESS_LENGTH);
        memcpy(message+38+CONSENSUS_NODES_IP_ADDRESS_LENGTH,"\"}",2);

        if (update_document_from_collection(DATABASE_NAME, DATABASE_COLLECTION, MESSAGE, message, 0) == 0)
        {
          CHECK_IF_CONSENSUS_NODE_IS_OFFLINE_ERROR("Could not update the consensus node in the database\nFunction: check_if_consensus_node_is_offline_timer\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE");
        }
        // create the message
        memset(message,0,strnlen(message,BUFFER_SIZE));
        memcpy(message,"{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE\",\r\n \"consensus_node_IP_address\": \"",120);
        memcpy(message+120,CONSENSUS_NODES_IP_ADDRESS,CONSENSUS_NODES_IP_ADDRESS_LENGTH);
        memcpy(message+120+CONSENSUS_NODES_IP_ADDRESS_LENGTH,"\",\r\n}",5);

        // sign the message
        if (sign_data(message,0) == 0)
        {
          CHECK_IF_CONSENSUS_NODE_IS_OFFLINE_ERROR("Could not sign_data\nFunction: check_if_consensus_node_is_offline_timer\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE");
        }

        // send the message to all block verifiers
        for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
        {   
          send_data_socket(block_verifiers_list.block_verifiers_IP_address[count],SEND_DATA_PORT,message,"sending CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE to the block verifiers",0);
        }
     
        // stop the check_if_consensus_node_is_offline_timer
        check_if_consensus_node_is_offline_timer_settings = 0;

        // start the check_if_consensus_node_needs_to_add_a_block_to_the_network_timer
        check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_settings = 1;
      }      
    }
  }

  pointer_reset(message);
  pthread_exit((void *)(intptr_t)1);

  #undef DATABASE_COLLECTION
  #undef MESSAGE
  #undef CHECK_IF_CONSENSUS_NODE_IS_OFFLINE_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: check_if_consensus_node_needs_to_add_a_block_to_the_network_timer
Description: Checks if the consensus node needs to add a block to the network
Return: NULL
-----------------------------------------------------------------------------------------------------------
*/

void* check_if_consensus_node_needs_to_add_a_block_to_the_network_timer()
{ 
  // Variables
  char* message = (char*)calloc(BUFFER_SIZE,sizeof(char));
  int count;

  // check if the memory needed was allocated on the heap successfully
  if (message == NULL)
  {   
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // define macros
  #define MESSAGE "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n}"

  #define CHECK_IF_CONSENSUS_NODE_NEEDS_TO_ADD_A_BLOCK_TO_THE_NETWORK_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset(message); \
  return 0;

  for (;;)
  {
    sleep(NETWORK_BLOCK_TIME);

    while (check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_settings == 1)
    {
      // create the message
      memcpy(message,MESSAGE,107);

      // sign the message
      if (sign_data(message,0) == 0)
      {
        CHECK_IF_CONSENSUS_NODE_NEEDS_TO_ADD_A_BLOCK_TO_THE_NETWORK_ERROR("Could not sign_data\nFunction: xcash_proof_of_stake_timer\nReceived Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS");
      }

      // send a message to any block validation node to check if it needs to add a block to the network
      memset(consensus_node_add_blocks_to_network,0,strnlen(consensus_node_add_blocks_to_network,BUFFER_SIZE));
      for (count = 0; count < BLOCK_VALIDATION_NODES_AMOUNT; count++)
      {
        if (send_and_receive_data_socket(consensus_node_add_blocks_to_network,block_validation_nodes_list.block_validation_nodes_IP_address[count],SEND_DATA_PORT,message,RECEIVE_DATA_TIMEOUT_SETTINGS,"Checking if the consensus node needs to add a block to the network",0) == 0)
        {
          CHECK_IF_CONSENSUS_NODE_NEEDS_TO_ADD_A_BLOCK_TO_THE_NETWORK_ERROR("Could not send or receive data\nFunction: xcash_proof_of_stake_timer\nReceived Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS");
        }
      }

      if (memcmp(consensus_node_add_blocks_to_network,"1",1) == 0)
      {
        // stop all of the running timers
        check_if_consensus_node_is_offline_timer_settings = 0;

        // let all of the block verifiers know that the consensus node will be adding the blocks to the network
        if (send_consensus_node_needs_to_add_a_block_to_the_network_message() == 0)
        {
          CHECK_IF_CONSENSUS_NODE_NEEDS_TO_ADD_A_BLOCK_TO_THE_NETWORK_ERROR("Could not send xcash proof of stake function\nFunction: xcash_proof_of_stake_timer\nReceived Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS");
        }

        // add a block to the network
        if (consensus_node_create_new_block() == 0)
        {
          CHECK_IF_CONSENSUS_NODE_NEEDS_TO_ADD_A_BLOCK_TO_THE_NETWORK_ERROR("The consensus node could not create a block\nFunction: xcash_proof_of_stake_timer\nReceived Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS");
        }      
      }
      else
      {
        // start all of the running timers
        check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_settings = 1;
      }
    }
  }

  pointer_reset(message);
  pthread_exit((void *)(intptr_t)1);

  #undef MESSAGE
  #undef CHECK_IF_CONSENSUS_NODE_NEEDS_TO_ADD_A_BLOCK_TO_THE_NETWORK
}