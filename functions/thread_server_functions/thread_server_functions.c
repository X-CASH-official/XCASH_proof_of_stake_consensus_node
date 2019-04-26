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
#include "network_wallet_functions.h"
#include "server_functions.h"
#include "thread_server_functions.h"
#include "vrf.h"
#include "crypto_vrf.h"
#include "VRF_functions.h"

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
Name: receive_votes_from_nodes_timeout_thread
Description: Counts the votes.
Return: NULL
-----------------------------------------------------------------------------------------------------------
*/

void* receive_votes_from_nodes_timeout_thread()
{  
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
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

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

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
  memset(data,0,strnlen(data,BUFFER_SIZE));
  memcpy(data,trusted_block_verifiers_VRF_data.data_hash[0],strnlen(trusted_block_verifiers_VRF_data.data_hash[0],DATA_HASH_LENGTH));
  for (count = 1, count2 = 0, settings = 0; count < trusted_block_verifiers_VRF_data.count; count++)
  {
    if (memcmp(trusted_block_verifiers_VRF_data.data_hash[count],data,DATA_HASH_LENGTH) == 0)
    {
      settings = count;
      count2++;
    }
    else
    {
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,trusted_block_verifiers_VRF_data.data_hash[count],strnlen(trusted_block_verifiers_VRF_data.data_hash[0],DATA_HASH_LENGTH));
    }
  }

  if (count2 >= TRUSTED_BLOCK_VERIFIERS_AMOUNT)
  {    
    // Add the VRF data for this part of the round to the VRF_data and the database
    if (memcmp(current_round_part,"1",1) == 0)
    {
      // verify the VRF data
      settings2 = crypto_vrf_verify((unsigned char*)trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_1[settings],(const unsigned char*)trusted_block_verifiers_VRF_data.vrf_public_key_round_part_1[settings],(const unsigned char*)trusted_block_verifiers_VRF_data.vrf_proof_round_part_1[settings],(const unsigned char*)trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_1[settings],(unsigned long long)strnlen(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_1[settings],BUFFER_SIZE));
      if (settings2 == 1)
      {
        // The vote for false is valid
        settings = 3;
        goto end;
      }
      memset(VRF_data.vrf_public_key_round_part_1,0,strnlen(VRF_data.vrf_public_key_round_part_1,VRF_PUBLIC_KEY_LENGTH));
      memset(VRF_data.vrf_alpha_string_round_part_1,0,strnlen(VRF_data.vrf_alpha_string_round_part_1,BUFFER_SIZE));
      memset(VRF_data.vrf_proof_round_part_1,0,strnlen(VRF_data.vrf_proof_round_part_1,VRF_PROOF_LENGTH));
      memset(VRF_data.vrf_beta_string_round_part_1,0,strnlen(VRF_data.vrf_beta_string_round_part_1,VRF_BETA_LENGTH));
      memcpy(VRF_data.vrf_public_key_round_part_1,trusted_block_verifiers_VRF_data.vrf_public_key_round_part_1[settings],strnlen(trusted_block_verifiers_VRF_data.vrf_public_key_round_part_1[settings],VRF_PUBLIC_KEY_LENGTH));
      memcpy(VRF_data.vrf_alpha_string_round_part_1,trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_1[settings],strnlen(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_1[settings],BUFFER_SIZE));
      memcpy(VRF_data.vrf_proof_round_part_1,trusted_block_verifiers_VRF_data.vrf_proof_round_part_1[settings],strnlen(trusted_block_verifiers_VRF_data.vrf_proof_round_part_1[settings],VRF_PROOF_LENGTH));
      memcpy(VRF_data.vrf_beta_string_round_part_1,trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_1[settings],strnlen(trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_1[settings],VRF_BETA_LENGTH));
      // create the message
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"vrf_public_key_round_part_1\":\"",32);
      memcpy(data+32,VRF_data.vrf_public_key_round_part_1,VRF_PUBLIC_KEY_LENGTH);
      memcpy(data+32+VRF_PUBLIC_KEY_LENGTH,"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,0) == 0)
      {
        RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR("Could not update the vrf_public_key_round_part_1 in the database\nFunction: receive_votes_from_nodes_timeout_thread");
      }
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"vrf_alpha_string_round_part_1\":\"",34);
      memcpy(data+34,VRF_data.vrf_alpha_string_round_part_1,strnlen(VRF_data.vrf_alpha_string_round_part_1,BUFFER_SIZE));
      memcpy(data+strnlen(VRF_data.vrf_alpha_string_round_part_1,BUFFER_SIZE),"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,0) == 0)
      {
        RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR("Could not update the vrf_alpha_string_round_part_1 in the database\nFunction: receive_votes_from_nodes_timeout_thread");
      }
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"vrf_proof_round_part_1\":\"",27);
      memcpy(data+27,VRF_data.vrf_proof_round_part_1,VRF_PROOF_LENGTH);
      memcpy(data+27,"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,0) == 0)
      {
        RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR("Could not update the vrf_proof_round_part_1 in the database\nFunction: receive_votes_from_nodes_timeout_thread");
      }
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"vrf_beta_string_round_part_1\":\"",33);
      memcpy(data+33,VRF_data.vrf_beta_string_round_part_1,VRF_BETA_LENGTH);
      memcpy(data+33+VRF_BETA_LENGTH,"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,0) == 0)
      {
        RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR("Could not update the vrf_beta_string_round_part_1 in the database\nFunction: receive_votes_from_nodes_timeout_thread");
      }
    } 
    else if (memcmp(current_round_part,"2",1) == 0)
    {
      // verify the VRF data
      settings2 = crypto_vrf_verify((unsigned char*)trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_2[settings],(const unsigned char*)trusted_block_verifiers_VRF_data.vrf_public_key_round_part_2[settings],(const unsigned char*)trusted_block_verifiers_VRF_data.vrf_proof_round_part_2[settings],(const unsigned char*)trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_2[settings],(unsigned long long)strnlen(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_2[settings],BUFFER_SIZE));
      if (settings2 == 1)
      {
        // The vote for false is valid
        settings = 3;
        goto end;
      }
      memset(VRF_data.vrf_public_key_round_part_2,0,strnlen(VRF_data.vrf_public_key_round_part_2,VRF_PUBLIC_KEY_LENGTH));
      memset(VRF_data.vrf_alpha_string_round_part_2,0,strnlen(VRF_data.vrf_alpha_string_round_part_2,BUFFER_SIZE));
      memset(VRF_data.vrf_proof_round_part_2,0,strnlen(VRF_data.vrf_proof_round_part_2,VRF_PROOF_LENGTH));
      memset(VRF_data.vrf_beta_string_round_part_2,0,strnlen(VRF_data.vrf_beta_string_round_part_2,VRF_BETA_LENGTH));
      memcpy(VRF_data.vrf_public_key_round_part_2,trusted_block_verifiers_VRF_data.vrf_public_key_round_part_2[settings],strnlen(trusted_block_verifiers_VRF_data.vrf_public_key_round_part_2[settings],VRF_PUBLIC_KEY_LENGTH));
      memcpy(VRF_data.vrf_alpha_string_round_part_2,trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_2[settings],strnlen(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_2[settings],BUFFER_SIZE));
      memcpy(VRF_data.vrf_proof_round_part_2,trusted_block_verifiers_VRF_data.vrf_proof_round_part_2[settings],strnlen(trusted_block_verifiers_VRF_data.vrf_proof_round_part_2[settings],VRF_PROOF_LENGTH));
      memcpy(VRF_data.vrf_beta_string_round_part_2,trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_2[settings],strnlen(trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_2[settings],VRF_BETA_LENGTH));
      // create the message
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"vrf_public_key_round_part_2\":\"",32);
      memcpy(data+32,VRF_data.vrf_public_key_round_part_2,VRF_PUBLIC_KEY_LENGTH);
      memcpy(data+32+VRF_PUBLIC_KEY_LENGTH,"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,0) == 0)
      {
        RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR("Could not update the vrf_public_key_round_part_2 in the database\nFunction: receive_votes_from_nodes_timeout_thread");
      }
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"vrf_alpha_string_round_part_2\":\"",34);
      memcpy(data+34,VRF_data.vrf_alpha_string_round_part_2,strnlen(VRF_data.vrf_alpha_string_round_part_1,BUFFER_SIZE));
      memcpy(data+strnlen(VRF_data.vrf_alpha_string_round_part_1,BUFFER_SIZE),"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,0) == 0)
      {
        RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR("Could not update the vrf_alpha_string_round_part_2 in the database\nFunction: receive_votes_from_nodes_timeout_thread");
      }
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"vrf_proof_round_part_2\":\"",27);
      memcpy(data+27,VRF_data.vrf_proof_round_part_2,VRF_PROOF_LENGTH);
      memcpy(data+27+VRF_PROOF_LENGTH,"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,0) == 0)
      {
        RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR("Could not update the vrf_proof_round_part_2 in the database\nFunction: receive_votes_from_nodes_timeout_thread");
      }
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"vrf_beta_string_round_part_2\":\"",33);
      memcpy(data+33,VRF_data.vrf_beta_string_round_part_2,VRF_BETA_LENGTH);
      memcpy(data+33+VRF_BETA_LENGTH,"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,0) == 0)
      {
        RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR("Could not update the vrf_beta_string_round_part_2 in the database\nFunction: receive_votes_from_nodes_timeout_thread");
      }
    }
    else if (memcmp(current_round_part,"3",1) == 0)
    {
      // verify the VRF data
      settings2 = crypto_vrf_verify((unsigned char*)trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_3[settings],(const unsigned char*)trusted_block_verifiers_VRF_data.vrf_public_key_round_part_3[settings],(const unsigned char*)trusted_block_verifiers_VRF_data.vrf_proof_round_part_3[settings],(const unsigned char*)trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_3[settings],(unsigned long long)strnlen(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_3[settings],BUFFER_SIZE));
      if (settings2 == 1)
      {
        // The vote for false is valid
        settings = 3;
        goto end;
      }
      memset(VRF_data.vrf_public_key_round_part_3,0,strnlen(VRF_data.vrf_public_key_round_part_3,VRF_PUBLIC_KEY_LENGTH));
      memset(VRF_data.vrf_alpha_string_round_part_3,0,strnlen(VRF_data.vrf_alpha_string_round_part_3,BUFFER_SIZE));
      memset(VRF_data.vrf_proof_round_part_3,0,strnlen(VRF_data.vrf_proof_round_part_3,VRF_PROOF_LENGTH));
      memset(VRF_data.vrf_beta_string_round_part_3,0,strnlen(VRF_data.vrf_beta_string_round_part_3,VRF_BETA_LENGTH));
      memcpy(VRF_data.vrf_public_key_round_part_3,trusted_block_verifiers_VRF_data.vrf_public_key_round_part_3[settings],strnlen(trusted_block_verifiers_VRF_data.vrf_public_key_round_part_3[settings],VRF_PUBLIC_KEY_LENGTH));
      memcpy(VRF_data.vrf_alpha_string_round_part_3,trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_3[settings],strnlen(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_3[settings],BUFFER_SIZE));
      memcpy(VRF_data.vrf_proof_round_part_3,trusted_block_verifiers_VRF_data.vrf_proof_round_part_3[settings],strnlen(trusted_block_verifiers_VRF_data.vrf_proof_round_part_3[settings],VRF_PROOF_LENGTH));
      memcpy(VRF_data.vrf_beta_string_round_part_3,trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_3[settings],strnlen(trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_3[settings],VRF_BETA_LENGTH));
      // create the message
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"vrf_public_key_round_part_3\":\"",32);
      memcpy(data+32,VRF_data.vrf_public_key_round_part_3,VRF_PUBLIC_KEY_LENGTH);
      memcpy(data+32+VRF_PUBLIC_KEY_LENGTH,"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,0) == 0)
      {
        RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR("Could not update the vrf_public_key_round_part_3 in the database\nFunction: receive_votes_from_nodes_timeout_thread");
      }
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"vrf_alpha_string_round_part_3\":\"",34);
      memcpy(data+34,VRF_data.vrf_alpha_string_round_part_3,strnlen(VRF_data.vrf_alpha_string_round_part_1,BUFFER_SIZE));
      memcpy(data+strnlen(VRF_data.vrf_alpha_string_round_part_1,BUFFER_SIZE),"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,0) == 0)
      {
        RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR("Could not update the vrf_alpha_string_round_part_3 in the database\nFunction: receive_votes_from_nodes_timeout_thread");
      }
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"vrf_proof_round_part_3\":\"",27);
      memcpy(data+27,VRF_data.vrf_proof_round_part_3,VRF_PROOF_LENGTH);
      memcpy(data+27+VRF_PROOF_LENGTH,"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,0) == 0)
      {
        RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR("Could not update the vrf_proof_round_part_3 in the database\nFunction: receive_votes_from_nodes_timeout_thread");
      }
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"vrf_beta_string_round_part_3\":\"",33);
      memcpy(data+33,VRF_data.vrf_beta_string_round_part_3,VRF_BETA_LENGTH);
      memcpy(data+33+VRF_BETA_LENGTH,"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,0) == 0)
      {
        RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR("Could not update the vrf_beta_string_round_part_3 in the database\nFunction: receive_votes_from_nodes_timeout_thread");
      }
    }
    else if (memcmp(current_round_part,"4",1) == 0)
    {
      settings2 = 0;
      memset(VRF_data.block_blob,0,strnlen(VRF_data.block_blob,BUFFER_SIZE));
      memcpy(VRF_data.block_blob,trusted_block_verifiers_VRF_data.block_blob[settings],strnlen(trusted_block_verifiers_VRF_data.block_blob[settings],BUFFER_SIZE));
      // create the message
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"block_blob\":\"",32);
      memcpy(data+32,VRF_data.block_blob,strnlen(VRF_data.block_blob,BUFFER_SIZE));
      memcpy(data+strnlen(VRF_data.block_blob,BUFFER_SIZE),"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,0) == 0)
      {
        RECEIVE_VOTES_FROM_NODES_TIMEOUT_THREAD_ERROR("Could not update the vrf_public_key_round_part_3 in the database\nFunction: receive_votes_from_nodes_timeout_thread");
      }
    }                      
  }
  else
  {
    // The vote is false is valid
    settings = 3;
    goto end;
  }
  settings = 0;

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
    
    if (counter >= TRUSTED_BLOCK_VERIFIERS_AMOUNT && settings2 == 0)
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
    
    if (counter >= TRUSTED_BLOCK_VERIFIERS_AMOUNT && settings2 == 0)
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

  end:



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
      memset(trusted_block_verifiers_VRF_data.vrf_public_key_round_part_1[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_public_key_round_part_1[count],VRF_PUBLIC_KEY_LENGTH));
      memset(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_1[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_1[count],BUFFER_SIZE));
      memset(trusted_block_verifiers_VRF_data.vrf_proof_round_part_1[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_proof_round_part_1[count],VRF_PROOF_LENGTH));
      memset(trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_1[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_1[count],VRF_BETA_LENGTH));
      memset(trusted_block_verifiers_VRF_data.vrf_public_key_round_part_2[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_public_key_round_part_2[count],VRF_PUBLIC_KEY_LENGTH));
      memset(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_2[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_2[count],BUFFER_SIZE));
      memset(trusted_block_verifiers_VRF_data.vrf_proof_round_part_2[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_proof_round_part_2[count],VRF_PROOF_LENGTH));
      memset(trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_2[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_2[count],VRF_BETA_LENGTH));
      memset(trusted_block_verifiers_VRF_data.vrf_public_key_round_part_3[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_public_key_round_part_3[count],VRF_PUBLIC_KEY_LENGTH));
      memset(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_3[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_alpha_string_round_part_3[count],BUFFER_SIZE));
      memset(trusted_block_verifiers_VRF_data.vrf_proof_round_part_3[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_proof_round_part_3[count],VRF_PROOF_LENGTH));
      memset(trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_3[count],0,strnlen(trusted_block_verifiers_VRF_data.vrf_beta_string_round_part_3[count],VRF_BETA_LENGTH));
      memset(trusted_block_verifiers_VRF_data.block_blob[count],0,strnlen(trusted_block_verifiers_VRF_data.block_blob[count],BUFFER_SIZE));
      memset(trusted_block_verifiers_VRF_data.data_hash[count],0,strnlen(trusted_block_verifiers_VRF_data.data_hash[count],DATA_HASH_LENGTH));
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

    if (check_if_consensus_node_is_offline_timer_settings.settings == 1)
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
        check_if_consensus_node_is_offline_timer_settings.settings = 0;

        // start the check_if_consensus_node_needs_to_add_a_block_to_the_network_timer
        check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_settings.settings = 1;

        // start the update_block_verifiers_timer_settings
        update_block_verifiers_timer_settings.settings = 1;
      }      
    }
    else
    {
      // check to make sure the consensus node is still the current consensus node
      if (get_current_consensus_node() == 0)
      {
        // the consensus node is not the current consensus node

        // start the check_if_consensus_node_is_offline_timer
        check_if_consensus_node_is_offline_timer_settings.settings = 1;

        // stop the check_if_consensus_node_needs_to_add_a_block_to_the_network_timer
        check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_settings.settings = 0;

        // stop the update_block_verifiers_timer_settings
        update_block_verifiers_timer_settings.settings = 0;

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

    while (check_if_consensus_node_needs_to_add_a_block_to_the_network_timer_settings.settings == 1)
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
    }
  }

  pointer_reset(message);
  pthread_exit((void *)(intptr_t)1);

  #undef MESSAGE
  #undef CHECK_IF_CONSENSUS_NODE_NEEDS_TO_ADD_A_BLOCK_TO_THE_NETWORK
}



/*
-----------------------------------------------------------------------------------------------------------
Name: update_block_verifiers_timer
Description: Updates the block verifiers total vote count
Return: NULL
-----------------------------------------------------------------------------------------------------------
*/

void* update_block_verifiers_timer()
{ 
  // Constants
  const bson_t* current_document;

  // Variables
  char* data = (char*)calloc(10485760,sizeof(char));
  char* data2 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data3 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* settings = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count;
  size_t count2;
  size_t counter;
  long long int amount;
  mongoc_collection_t* collection;
  mongoc_cursor_t* document_settings;
  bson_error_t error;
  bson_t* document = NULL;  
  char* message;
  char* message_copy1;
  char* message_copy2;
  time_t current_date_and_time;
  struct tm* current_UTC_date_and_time;  

  // define macros
  #define pointer_reset_all \
  free(data); \
  data = NULL; \
  free(data2); \
  data2 = NULL; \
  free(data3); \
  data3 = NULL; \
  free(settings); \
  settings = NULL; 

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL || data2 == NULL || data3 == NULL || settings == NULL)
  {   
    if (data != NULL)
    {
      pointer_reset(data);
    }
    if (data2 != NULL)
    {
      pointer_reset(data2);
    }
    if (data3 != NULL)
    {
      pointer_reset(data3);
    }
    if (settings != NULL)
    {
      pointer_reset(settings);
    }
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }  

  for (;;)
  {
    sleep(60);

    while (update_block_verifiers_timer_settings.settings == 1)
    {
      time(&current_date_and_time);
      current_UTC_date_and_time = gmtime(&current_date_and_time);
      if (current_UTC_date_and_time->tm_hour % 2 == 0 && current_UTC_date_and_time->tm_min == 0)
      {  
        // let the block verifiers know that the update_block_verifiers_timer is running 
        if (send_recalculating_votes_to_nodes_and_main_nodes() == 0)
        {
          color_print("Could not send the CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES message to the block verifiers\nFunction: update_block_verifiers_timer","red");
        }

        // reset the reserve_proofs_list struct
        for (count = 0; count < RESERVE_PROOFS_LIST_MAXIMUM_AMOUNT; count++)
        {
          memset(reserve_proofs_list.public_address_created_reserve_proof[count],0,strnlen(reserve_proofs_list.public_address_created_reserve_proof[count],BUFFER_SIZE));
          memset(reserve_proofs_list.public_address_voted_for[count],0,strnlen(reserve_proofs_list.public_address_voted_for[count],BUFFER_SIZE));
          memset(reserve_proofs_list.reserve_proof[count],0,strnlen(reserve_proofs_list.reserve_proof[count],BUFFER_SIZE));
          reserve_proofs_list.settings[count] = 0;
          reserve_proofs_list.amount[count] = 0;
          reserve_proofs_list.number[count] = 0;
        }
        reserve_proofs_list.count = 0;

        // update delegates collection     
        // set the collection
        collection = mongoc_client_get_collection(database_client, DATABASE_NAME, "delegates");
        document = bson_new(); 
        document_settings = mongoc_collection_find_with_opts(collection, document, NULL, NULL);
        while (mongoc_cursor_next(document_settings, &current_document))
        {
          // reset the variables
          memset(data,0,strnlen(data,10485760));
          memset(data2,0,strnlen(data2,BUFFER_SIZE));
          memset(data3,0,strnlen(data3,BUFFER_SIZE));
          memset(settings,0,strnlen(settings,BUFFER_SIZE));

          message = bson_as_canonical_extended_json(current_document, NULL);
          memcpy(data,message,strnlen(message,BUFFER_SIZE));
          bson_free(message);

          // get the public address
          memcpy(data2,", \"",3);
          memcpy(data2+3,"public_address",14);
          memcpy(data2+17,"\" : \"",5);

          message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
          message_copy2 = strstr(message_copy1,"\"");
          memcpy(data3,message_copy1,message_copy2 - message_copy1);

          // create the message
          memcpy(settings,"{\"public_address\":\"",20);
          memcpy(settings+20,data3,strnlen(data3,BUFFER_SIZE));
          memcpy(settings+20+strnlen(data3,BUFFER_SIZE),"\"}",2);

          // reset the variables
          memset(data2,0,strnlen(data2,BUFFER_SIZE));
          memset(data3,0,strnlen(data3,BUFFER_SIZE));

          // get the IP_address
          memcpy(data2,", \"",3);
          memcpy(data2+3,"IP_address",10);
          memcpy(data2+13,"\" : \"",5);

          message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
          message_copy2 = strstr(message_copy1,"\"");
          memcpy(data3,message_copy1,message_copy2 - message_copy1);

          // set the block_producer_eligibility to true for all delegates
          if (update_document_from_collection(DATABASE_NAME,"delegates",settings,"{\"block_producer_eligibility\":\"true\"}",0) == 0)
          {
            color_print("Could not update the block_producer_eligibility in the database\nFunction: update_block_verifiers_timer","red");
          }

          // get their online status and update the online status in the database
          if (send_data_socket(data3,SEND_DATA_PORT,"","check if delegate is online",0) == 0)
          {
            // the delegate is offline
            if (update_document_from_collection(DATABASE_NAME,"delegates",settings,"{\"online_status\":\"false\"}",0) == 0)
            {
              color_print("Could not update the online_status in the database\nFunction: update_block_verifiers_timer","red");
            }
          }
          else
          {
            // the delegate is offline
            if (update_document_from_collection(DATABASE_NAME,"delegates",settings,"{\"online_status\":\"true\"}",0) == 0)
            {
              color_print("Could not update the online_status in the database\nFunction: update_block_verifiers_timer","red");
            }
          }

          // set the total_vote_count to 0 for all of the delegates
          if (update_document_from_collection(DATABASE_NAME,"delegates",settings,"{\"total_vote_count\":\"0\"}",0) == 0)
          {
            color_print("Could not update the total_vote_count in the database\nFunction: update_block_verifiers_timer","red");
          }
        }

        // remove any duplicate votes or invalid votes
        // set the collection
        collection = mongoc_client_get_collection(database_client, DATABASE_NAME, "votes_list");
        document_settings = mongoc_collection_find_with_opts(collection, document, NULL, NULL);
        while (mongoc_cursor_next(document_settings, &current_document))
        {
          // reset the variables
          memset(data,0,strnlen(data,10485760));
          memset(data2,0,strnlen(data2,BUFFER_SIZE));
          memset(data3,0,strnlen(data3,BUFFER_SIZE));
          memset(settings,0,strnlen(settings,BUFFER_SIZE));

          message = bson_as_canonical_extended_json(current_document, NULL);
          memcpy(data,message,strnlen(message,BUFFER_SIZE));
          bson_free(message);

          // get the public_address_created_reserve_proof
          memcpy(data2,", \"",3);
          memcpy(data2+3,"public_address_created_reserve_proof",36);
          memcpy(data2+39,"\" : \"",5);

          message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
          message_copy2 = strstr(message_copy1,"\"");
          memcpy(data3,message_copy1,message_copy2 - message_copy1);

          // create the message
          memcpy(settings,"{\"public_address_created_reserve_proof\":\"",41);
          memcpy(settings+41,data3,strnlen(data3,BUFFER_SIZE));
          memcpy(settings+41+strnlen(data3,BUFFER_SIZE),"\"}",2);

          if (count_documents_in_collection(DATABASE_NAME, "votes_list", settings, 0) > 1 || strnlen(data3,BUFFER_SIZE) != XCASH_WALLET_LENGTH || memcmp(data3,XCASH_WALLET_PREFIX,3) != 0)
          {
            // delete the current document
            if (delete_document_from_collection(DATABASE_NAME, "votes_list", settings, 0) == 0)
            {
              color_print("Could not delete a double vote in the database\nFunction: update_block_verifiers_timer","red");
            }
            continue;
          }

          // get the public_address_voted_for
          memset(data2,0,strnlen(data2,BUFFER_SIZE));
          memset(data3,0,strnlen(data3,BUFFER_SIZE));
          memset(settings,0,strnlen(settings,BUFFER_SIZE));
          memcpy(data2,", \"",3);
          memcpy(data2+3,"public_address_voted_for",24);
          memcpy(data2+27,"\" : \"",5);

          message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
          message_copy2 = strstr(message_copy1,"\"");
          memcpy(data3,message_copy1,message_copy2 - message_copy1);

           // create the message
          memcpy(settings,"{\"public_address_voted_for\":\"",29);
          memcpy(settings+29,data3,strnlen(data3,BUFFER_SIZE));
          memcpy(settings+29+strnlen(data3,BUFFER_SIZE),"\"}",2);

          if (strnlen(data3,BUFFER_SIZE) != XCASH_WALLET_LENGTH || memcmp(data3,XCASH_WALLET_PREFIX,3) != 0)
          {
            // delete the current document
            if (delete_document_from_collection(DATABASE_NAME, "votes_list", settings, 0) == 0)
            {
              color_print("Could not delete a double vote in the database\nFunction: update_block_verifiers_timer","red");
            }
            continue;
          }

          // load all of the valid reserve proofs into the reserve_proofs_list struct so we can use the check_reserve_proofs
          // get the public_address_created_reserve_proof
          memcpy(data2,", \"",3);
          memcpy(data2+3,"public_address_created_reserve_proof",36);
          memcpy(data2+39,"\" : \"",5);

          message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
          message_copy2 = strstr(message_copy1,"\"");
          memcpy(data3,message_copy1,message_copy2 - message_copy1);

          memcpy(reserve_proofs_list.public_address_created_reserve_proof[count],data3,XCASH_WALLET_LENGTH);
          memset(data2,0,strnlen(data2,BUFFER_SIZE));
          memset(data3,0,strnlen(data3,BUFFER_SIZE));

          // get the public_address_voted_for
          memcpy(data2,", \"",3);
          memcpy(data2+3,"public_address_voted_for",24);
          memcpy(data2+27,"\" : \"",5);

          message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
          message_copy2 = strstr(message_copy1,"\"");
          memcpy(data3,message_copy1,message_copy2 - message_copy1);

          memcpy(reserve_proofs_list.public_address_voted_for[count],data3,XCASH_WALLET_LENGTH);
          memset(data2,0,strnlen(data2,BUFFER_SIZE));
          memset(data3,0,strnlen(data3,BUFFER_SIZE));

          // get the reserve_proof
          memcpy(data2,", \"",3);
          memcpy(data2+3,"reserve_proof",13);
          memcpy(data2+16,"\" : \"",5);

          message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
          message_copy2 = strstr(message_copy1,"\"");
          memcpy(data3,message_copy1,message_copy2 - message_copy1);

          memcpy(reserve_proofs_list.reserve_proof[count],data3,strnlen(data3,BUFFER_SIZE));
          memset(data2,0,strnlen(data2,BUFFER_SIZE));
          memset(data3,0,strnlen(data3,BUFFER_SIZE));

          reserve_proofs_list.settings[count] = 0;
          reserve_proofs_list.amount[count] = 0;
          reserve_proofs_list.number[count] = 0;

          reserve_proofs_list.count++;
        }  

        // reset the variables
        memset(data,0,strnlen(data,10485760));
        memset(data2,0,strnlen(data2,BUFFER_SIZE));
        memset(data3,0,strnlen(data3,BUFFER_SIZE));
        memset(settings,0,strnlen(settings,BUFFER_SIZE));

        // check the reserve proofs
        if (check_reserve_proofs(data,0) == 0)
        {
          color_print("Could not check the reserve proofs in the databse\nFunction: update_block_verifiers_timer","red");
        }

        // parse the data to check the status and spent amount for each reserve proof
        count = 0;
        counter = 0; 

        for (count = 0; count < reserve_proofs_list.count; count++)
        {
          message_copy1 = strstr(data+counter,"good") + 7; 
          counter += strnlen(data,10485760) - strnlen(message_copy1,10485760);
          if (memcmp(message_copy1,"true",4) == 0)
          {
            // the reserve proof is valid, now check if the spent amount is 0
            message_copy1 = strstr(data+counter,"spent") + 8;
            if (memcmp(message_copy1,"0,",2) == 0)
            {
              // the reserve proof is valid and the spent amount is 0. Get the total
              message_copy1 = strstr(data+counter,"total") + 8;
              // get the length of the total
              count2 = 0;
              while (memcmp(message_copy1+count2,"0",1) == 0 || memcmp(message_copy1+count2,"1",1) == 0 || memcmp(message_copy1+count2,"2",1) == 0 || memcmp(message_copy1+count2,"3",1) == 0 || memcmp(message_copy1+count2,"4",1) == 0 || memcmp(message_copy1+count2,"5",1) == 0 || memcmp(message_copy1+count2,"6",1) == 0 || memcmp(message_copy1+count2,"7",1) == 0 || memcmp(message_copy1+count2,"8",1) == 0 || memcmp(message_copy1+count2,"9",1) == 0)
              {
                count2++;
              }
              memset(data2,0,strnlen(data2,BUFFER_SIZE));
              memcpy(data2,message_copy1,count2);
              reserve_proofs_list.settings[count] = 1;
              sscanf(data2, "%lld", &reserve_proofs_list.amount[count]);
              if (reserve_proofs_list.amount[count] < XCASH_PROOF_OF_STAKE_MINIMUM_AMOUNT)
              {
                reserve_proofs_list.settings[count] = 0;
                reserve_proofs_list.amount[count] = 0;
              }
            }
          }
        }

        // remove any invalid or already spent reserve proofs from the database
        count = 0;
        // set the collection
        collection = mongoc_client_get_collection(database_client, DATABASE_NAME, "votes_list");
        document_settings = mongoc_collection_find_with_opts(collection, document, NULL, NULL);
        while (mongoc_cursor_next(document_settings, &current_document))
        {
          // reset the variables
          memset(data,0,strnlen(data,10485760));
          memset(data2,0,strnlen(data2,BUFFER_SIZE));
          memset(data3,0,strnlen(data3,BUFFER_SIZE));
          memset(settings,0,strnlen(settings,BUFFER_SIZE));

          message = bson_as_canonical_extended_json(current_document, NULL);
          memcpy(data,message,strnlen(message,BUFFER_SIZE));
          bson_free(message);

          // get the public_address_created_reserve_proof
          memcpy(data2,", \"",3);
          memcpy(data2+3,"public_address_created_reserve_proof",36);
          memcpy(data2+39,"\" : \"",5);

          message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
          message_copy2 = strstr(message_copy1,"\"");
          memcpy(data3,message_copy1,message_copy2 - message_copy1);

          // create the message
          memcpy(settings,"{\"public_address_created_reserve_proof\":\"",41);
          memcpy(settings+41,data3,strnlen(data3,BUFFER_SIZE));
          memcpy(settings+41+strnlen(data3,BUFFER_SIZE),"\"}",2);

          // get the status of the reserve proof from the reserve_proofs_list
          for (count2 = 0; count2 < reserve_proofs_list.count; count2++)
          {
            if (memcmp(reserve_proofs_list.public_address_created_reserve_proof[count2],data3,XCASH_WALLET_LENGTH) == 0)
            {
              if (reserve_proofs_list.settings[count2] == 0)
              {
                // delete the current document
                if (delete_document_from_collection(DATABASE_NAME, "votes_list", settings, 0) == 0)
                {
                  color_print("Could not delete a double vote in the database\nFunction: update_block_verifiers_timer","red");
                }
              }
            }            
          }
        }

          // reset the variables
          memset(data,0,strnlen(data,10485760));
          memset(data2,0,strnlen(data2,BUFFER_SIZE));
          memset(data3,0,strnlen(data3,BUFFER_SIZE));
          memset(settings,0,strnlen(settings,BUFFER_SIZE));

          // update the reserve proofs total and vote_status in the database
          for (count = 0; count < reserve_proofs_list.count; count++)
          {
            if (reserve_proofs_list.settings[count] == 2)
            {
              // create the message
              memcpy(data,"{\"public_address_created_reserve_proof\":\"",44);
              memcpy(data+44,reserve_proofs_list.public_address_created_reserve_proof[count],XCASH_WALLET_LENGTH);
              memcpy(data+142,"\"}",2);

              memcpy(data2,"{\"total\":\"",10);
              sprintf(data2+10,"%lld",reserve_proofs_list.amount[count]);
              memcpy(data2+strnlen(data2,BUFFER_SIZE),"\"}",2);

              // update the database
              if (update_document_from_collection(DATABASE_NAME,"votes_list",data,data2,0) == 0 || update_document_from_collection(DATABASE_NAME,"votes_list",data,"{\"vote_status\":\"enabled\"}",0) == 0)
              {
                color_print("Could not update a delgates reserve proof amount in the database\nFunction: update_block_verifiers_timer","red");
              }
            } 
          }

          // reset the variables
          memset(data,0,strnlen(data,10485760));
          memset(data2,0,strnlen(data2,BUFFER_SIZE));
          memset(data3,0,strnlen(data3,BUFFER_SIZE));
          memset(settings,0,strnlen(settings,BUFFER_SIZE));

          // update the delegates total_vote_count and current_vote_count         
          for (count = 0; count < reserve_proofs_list.count; count++)
          {
            // create the message
            memcpy(data,"{\"public_address_voted_for\":\"",29);
            memcpy(data+29,reserve_proofs_list.public_address_voted_for[count],XCASH_WALLET_LENGTH);
            memcpy(data+127,"\"}",2);

            // get the total for the public_address_voted_for
            for (count2 = 0, amount = 0; count2 < reserve_proofs_list.count; count2++)
            {
              if (memcmp(reserve_proofs_list.public_address_voted_for[count],reserve_proofs_list.public_address_voted_for[count2],XCASH_WALLET_LENGTH) == 0)
              {
                if (reserve_proofs_list.settings[count2] == 1)
                {
                  amount += reserve_proofs_list.amount[count2];
                }
              }
            }

            memcpy(data2,"{\"current_vote_count\":\"",23);
            sprintf(data2+23,"%lld",amount);
            memcpy(data2+strnlen(data2,BUFFER_SIZE),"\"}",2);

            memcpy(data3,"{\"total_vote_count\":\"",21);
            sprintf(data3+21,"%lld",amount);
            memcpy(data3+strnlen(data3,BUFFER_SIZE),"\"}",2);

            // update the database
            if (update_document_from_collection(DATABASE_NAME,"delegates",data,data2,0) == 0 || update_document_from_collection(DATABASE_NAME,"delegates",data,data3,0) == 0)
            {
              color_print("Could not update a delegates current_vote_count or total_vote_count in the database\nFunction: update_block_verifiers_timer","red");
            }
          }

          // reset the variables
          memset(data,0,strnlen(data,10485760));
          memset(data2,0,strnlen(data2,BUFFER_SIZE));
          memset(data3,0,strnlen(data3,BUFFER_SIZE));
          memset(settings,0,strnlen(settings,BUFFER_SIZE));       

          // update the total_coins_in_proof_of_stake in the database
          amount = 0;
          for (count = 0; count < reserve_proofs_list.count; count++)
          {
            amount += reserve_proofs_list.amount[count];
          }

          memcpy(data,"{\"total_coins_in_proof_of_stake\":\"",34);
          sprintf(data+34,"%lld",amount);
          memcpy(data+strnlen(data,BUFFER_SIZE),"\"}",2);

          // update the database
          if (update_document_from_collection(DATABASE_NAME,"statistics","{\"username\":\"xcash\"}",data,0) == 0)
          {
            color_print("Could not update the total_coins_in_proof_of_stake in the database\nFunction: update_block_verifiers_timer","red");
          }

          // update the numbers for the delegates
          amount = reserve_proofs_list.amount[0];
          for (count = 0; count < reserve_proofs_list.count; count++)
          {
            // loop through the first time and set the number to the current number. Only compare the delegates that have number 0 since they have dont have the correct number
            for (count2 = 0; count2 < reserve_proofs_list.count; count2++)
            {            
              if (reserve_proofs_list.amount[count2] > amount && reserve_proofs_list.number[count2] == 0)
              {
                reserve_proofs_list.number[count2] = count;
                amount = reserve_proofs_list.amount[count2];
              }
            } 
            // since their will be multiple delegates that have the same current number, loop through to only set the last one (since this one is the correct one) to the current number
            for (count2 = 0; count2 < reserve_proofs_list.count; count2++)
            {
              if (reserve_proofs_list.amount[count2] == amount && reserve_proofs_list.number[count2] == 1)
              {
                reserve_proofs_list.number[count2] = count;
              }
              else
              {
                reserve_proofs_list.number[count2] = 0;
              }
            }
          }

          // reset the variables
          memset(data,0,strnlen(data,10485760));
          memset(data2,0,strnlen(data2,BUFFER_SIZE));
          memset(data3,0,strnlen(data3,BUFFER_SIZE));
          memset(settings,0,strnlen(settings,BUFFER_SIZE)); 

          // update the number in the database for the delegates
          for (count = 0; count < reserve_proofs_list.count; count++)
          {
            if (reserve_proofs_list.number[count] > 0 && reserve_proofs_list.number[count] <= 100)
            {
              // create the message
              memcpy(data,"{\"public_address_created_reserve_proof\":\"",44);
              memcpy(data+44,reserve_proofs_list.public_address_created_reserve_proof[count],XCASH_WALLET_LENGTH);
              memcpy(data+142,"\"}",2);

              memcpy(data2,"{\"delegate_number\":\"",20);
              sprintf(data2+20,"%d",reserve_proofs_list.number[count]);
              memcpy(data2+strnlen(data2,BUFFER_SIZE),"\"}",2);

              // update the database
              if (update_document_from_collection(DATABASE_NAME,"delegates",data,data2,0) == 0)
              {
                color_print("Could not update a delegates delegate_number in the database\nFunction: update_block_verifiers_timer","red");
              }
            }            
          }

          // update the block_verifiers_list struct
          if (get_block_verifiers_list() == 0)
          {
            color_print("Could not update the block verifiers list\nFunction: update_block_verifiers_timer","red");
          }

          // send the updated list of block verifiers to the block verifiers
          if (send_vote_list_to_nodes() == 0)
          {
            color_print("Could not send the CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES message to the block verifiers\nFunction: update_block_verifiers_timer","red");
          }
      }
    }
  }

  pointer_reset_all;
  pthread_exit((void *)(intptr_t)1);

  #undef pointer_reset_all
}