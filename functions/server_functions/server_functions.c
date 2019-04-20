#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h> 
#include <signal.h>
#include <pthread.h>
#include <mongoc/mongoc.h>
#include <bson/bson.h>

#include "define_macro_functions.h"
#include "define_macros.h"
#include "structures.h"
#include "variables.h"

#include "define_macros_functions.h"
#include "blockchain_functions.h"
#include "database_functions.h"
#include "file_functions.h"
#include "network_daemon_functions.h"
#include "network_functions.h"
#include "network_security_functions.h"
#include "server_functions.h"
#include "string_functions.h"
#include "thread_server_functions.h"


/*
-----------------------------------------------------------------------------------------------------------
Functions
-----------------------------------------------------------------------------------------------------------
*/

/*
-----------------------------------------------------------------------------------------------------------
Name: get_current_consensus_node
Description: Checks if the consensus node is the current consensus node
Return: 1 if the consensus node is the current consensus node, otherwise 0.
-----------------------------------------------------------------------------------------------------------
*/

int get_current_consensus_node()
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // define macros
  #define DATABASE_COLLECTION "consensus_node"
  #define MESSAGE "{\"username\":\"xcash\"}"

  #define GET_CURRENT_CONSENSUS_NODE_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset(data); \
  return 0;


  // check if the memory needed was allocated on the heap successfully
  if (data == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // read the current_consensus_node_IP_address from the consensus_node collection
  if (read_document_field_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,"current_consensus_node_IP_address",data,0) == 0)
  {
    GET_CURRENT_CONSENSUS_NODE_ERROR("Could not get the current consensus node from the database\nFunction: get_current_consensus_node");
  }

  // check if the current_consensus_node_IP_address matches the CONSENSUS_NODES_IP_ADDRESS
  if (strncmp(data,CONSENSUS_NODES_IP_ADDRESS,BUFFER_SIZE) != 0)
  {
    return 0;
  }

  return 1;

  #undef DATABASE_COLLECTION
  #undef MESSAGE
  #undef GET_CURRENT_CONSENSUS_NODE_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: get_block_verifiers_list
Description: Gets the top 100 delegates (the block verifiers) from the database
Return: Returns 1 if successfull, otherwise 0
-----------------------------------------------------------------------------------------------------------
*/

int get_block_verifiers_list()
{
  // Constants
  const bson_t* current_document;

  // Variables
  mongoc_client_t* database_client_thread;
  mongoc_collection_t* collection;
  mongoc_cursor_t* document_settings;
  bson_t* document = NULL;  
  char* message;
  char* message_copy1;
  char* message_copy2;
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* settings = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count = 0;
  size_t field_name_length;

  // define macros
  #define DATABASE_COLLECTION "delegates"

  #define pointer_reset_all \
  free(data); \
  data = NULL; \
  free(settings); \
  settings = NULL; 

  #define GET_BLOCK_VERIFIERS_LIST_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset_all; \
  bson_destroy(document); \
  mongoc_cursor_destroy(document_settings); \
  mongoc_collection_destroy(collection); \
  return 0;


  // check if the memory needed was allocated on the heap successfully
  if (data == NULL || settings == NULL)
  {
    if (data != NULL)
    {
      pointer_reset(data);
    }
    if (settings != NULL)
    {
      pointer_reset(settings);
    }
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }  
  
  // set the collection
  collection = mongoc_client_get_collection(database_client, DATABASE_NAME, DATABASE_COLLECTION);

  document = bson_new();
  if (!document)
  {
    GET_BLOCK_VERIFIERS_LIST_ERROR("Could not create the document for the database\nFunction: get_block_verifiers_list");
  }

  // reset the block_verifiers_list struct
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    memset(block_verifiers_list.block_verifiers_name[count],0,strnlen(block_verifiers_list.block_verifiers_name[count],BLOCK_VERIFIERS_NAME_TOTAL_LENGTH+1));
    memset(block_verifiers_list.block_verifiers_public_address[count],0,strnlen(block_verifiers_list.block_verifiers_public_address[count],XCASH_WALLET_LENGTH+1));
    memset(block_verifiers_list.block_verifiers_IP_address[count],0,strnlen(block_verifiers_list.block_verifiers_IP_address[count],BLOCK_VERIFIERS_IP_ADDRESS_TOTAL_LENGTH+1));
  }

  document_settings = mongoc_collection_find_with_opts(collection, document, NULL, NULL);
  while (mongoc_cursor_next(document_settings, &current_document))
  {    
      message = bson_as_canonical_extended_json(current_document, NULL);
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,message,strnlen(message,BUFFER_SIZE));
      bson_free(message); 

      if (strstr(data,"\"delegate_number\" : \"1\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"2\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"3\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"4\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"5\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"6\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"7\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"8\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"9\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"10\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"11\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"12\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"13\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"14\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"15\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"16\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"17\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"18\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"19\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"20\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"21\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"22\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"23\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"24\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"25\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"26\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"27\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"28\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"29\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"30\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"31\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"32\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"33\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"34\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"35\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"36\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"37\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"38\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"39\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"40\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"41\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"42\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"43\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"44\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"45\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"46\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"47\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"48\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"49\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"50\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"51\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"52\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"53\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"54\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"55\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"56\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"57\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"58\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"59\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"60\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"61\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"62\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"63\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"64\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"65\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"66\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"67\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"68\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"69\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"70\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"71\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"72\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"73\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"74\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"75\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"76\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"77\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"78\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"79\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"80\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"81\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"82\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"83\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"84\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"85\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"86\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"87\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"88\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"89\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"90\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"91\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"92\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"93\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"94\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"95\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"96\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"97\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"98\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"99\"") != NULL ||
          strstr(data,"\"delegate_number\" : \"100\"") != NULL)
      {        
        // parse the delegate_name
        memset(settings,0,strnlen(settings,BUFFER_SIZE));
        memcpy(settings,", \"delegate_name\" : \"",21);
        message_copy1 = strstr(data,settings) + 21;
        message_copy2 = strstr(message_copy1,"\"");
        memcpy(block_verifiers_list.block_verifiers_name[count],message_copy1,message_copy2 - message_copy1);
        // parse the public_address
        memset(settings,0,strnlen(settings,BUFFER_SIZE));
        memcpy(settings,", \"public_address\" : \"",22);
        message_copy1 = strstr(data,settings) + 22;
        message_copy2 = strstr(message_copy1,"\"");
        memcpy(block_verifiers_list.block_verifiers_public_address[count],message_copy1,message_copy2 - message_copy1);
        // parse the IP_address
        memset(settings,0,strnlen(settings,BUFFER_SIZE));
        memcpy(settings,", \"IP_address\" : \"",18);
        message_copy1 = strstr(data,settings) + 18;
        message_copy2 = strstr(message_copy1,"\"");
        memcpy(block_verifiers_list.block_verifiers_IP_address[count],message_copy1,message_copy2 - message_copy1);
        count++;
      }
      // check if that is the total amount of documents to read
      if (count == BLOCK_VERIFIERS_AMOUNT)
      {
        break;
      }   
  }

  // check to make sure all of the block verifiers were read from the database
  if (count != BLOCK_VERIFIERS_AMOUNT)
  {
    GET_BLOCK_VERIFIERS_LIST_ERROR("Could not get all of the block verifiers from the database\nFunction: get_block_verifiers_list");
  }

  return 1;

  #undef DATABASE_COLLECTION
  #undef pointer_reset_all
  #undef GET_BLOCK_VERIFIERS_LIST_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: send_consensus_node_needs_to_add_a_block_to_the_network_message
Description: sends the CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CREATE_NEW_BLOCK_MESSAGE message to the nodes and main node
Return: 1 if the consensus node is the current consensus node, otherwise 0.
-----------------------------------------------------------------------------------------------------------
*/

int send_consensus_node_needs_to_add_a_block_to_the_network_message()
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count;

  // define macros
  #define SEND_CONSENSUS_NODE_NEEDS_TO_ADD_A_BLOCK_TO_THE_NETWORK_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset(data); \
  return 0;


  // check if the memory needed was allocated on the heap successfully
  if (data == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // create the message
  memcpy(data,"{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CREATE_NEW_BLOCK_MESSAGE\",\r\n}",108);

  // sign_data
  if (sign_data(data,0) == 0)
  { 
    SEND_CONSENSUS_NODE_NEEDS_TO_ADD_A_BLOCK_TO_THE_NETWORK_ERROR("Could not sign_data\nFunction: send_consensus_node_needs_to_add_a_block_to_the_network_message\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CREATE_NEW_BLOCK_MESSAGE");
  }

  // send the CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CREATE_NEW_BLOCK_MESSAGE message to the nodes and main node
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    send_data_socket(block_verifiers_list.block_verifiers_IP_address[count],SEND_DATA_PORT,data,"sending CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CREATE_NEW_BLOCK_MESSAGE message to the nodes and main node",0);
  }

  return 1;

  #undef SEND_CONSENSUS_NODE_NEEDS_TO_ADD_A_BLOCK_TO_THE_NETWORK_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: consensus_node_create_new_block
Description: The consensus node will add a new block to the network
Return: 1 if successfull, otherwise 0.
-----------------------------------------------------------------------------------------------------------
*/

int consensus_node_create_new_block()
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data2 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* message = (char*)calloc(BUFFER_SIZE,sizeof(char));
  time_t current_date_and_time;
  struct tm* current_UTC_date_and_time;  
  size_t count;
  size_t count2;
  size_t counter;
  size_t data_length;

  // threads
  pthread_t thread_id;

  // define macros
  #define pointer_reset_all \
  free(data); \
  data = NULL; \
  free(data2); \
  data2 = NULL; \
  free(message); \
  message = NULL;

  #define CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset_all; \
  return 0;


  // check if the memory needed was allocated on the heap successfully
  if (data == NULL || data2 == NULL || message == NULL)
  {
    if (data != NULL)
    {
      pointer_reset(data);
    }
    if (data2 != NULL)
    {
      pointer_reset(data2);
    }
    if (message != NULL)
    {
      pointer_reset(message);
    }
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  start:

  // reset the variables
  memset(data,0,strnlen(data,BUFFER_SIZE));
  memset(data2,0,strnlen(data2,BUFFER_SIZE));
  memset(message,0,strnlen(message,BUFFER_SIZE));

  // get a block template with 2110 reserve bytes
  if (get_block_template(data,"2110",0) == 0)
  {
    CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR("Could not get a block template\nFunction: consensus_node_create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK");
  }

  // convert the network_block_string to blockchain_data
  if (network_block_string_to_blockchain_data(data) == 0)
  {
    CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR("Could not convert the network_block_string to blockchain_data\nFunction: consensus_node_create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK");
  }

  // change the nonce to the CONSENSUS_NODE_NETWORK_BLOCK_NONCE
  memset(blockchain_data.nonce_data,0,strnlen(blockchain_data.nonce_data,9));
  memcpy(blockchain_data.nonce_data,CONSENSUS_NODE_NETWORK_BLOCK_NONCE,8);

  // convert the blockchain_data to a network_block_string
  memset(data,0,strnlen(data,BUFFER_SIZE));
  if (blockchain_data_to_network_block_string(data) == 0)
  {
    CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR("Could not convert the blockchain_data to a network_block_string\nFunction: consensus_node_create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK");
  }

  // create the message
  data_length = strnlen(data,BUFFER_SIZE);
  memcpy(message,"{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"block_blob\": \"",116);
  memcpy(message+116,data,data_length);
  memcpy(message+116+data_length,"\",\r\n}",5);

  // sign_data
  if (sign_data(message,0) == 0)
  { 
    CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR("Could not sign_data\nFunction: consensus_node_create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK");
  }

  // add the block_validation_node_signature_data_length to the blockchain_data
  blockchain_data.blockchain_reserve_bytes.block_validation_node_signature_data_length = 196;

  // send the network_block_string to the block validation nodes
  memset(data,0,strnlen(data,BUFFER_SIZE));
  for (count = 0; count < BLOCK_VALIDATION_NODES_AMOUNT; count++)
  {
    if (send_and_receive_data_socket(data,block_validation_nodes_list.block_validation_nodes_IP_address[count],SEND_DATA_PORT,message,TOTAL_CONNECTION_TIME_SETTINGS,"sending the network_block_string to the block validation nodes",0) == 1)
    {
      // convert the block validation signature to hexadecimal
      memset(data2,0,strnlen(data2,BUFFER_SIZE));
      for (count2 = 0, counter = 0; count2 < XCASH_SIGN_DATA_LENGTH; count2++, counter += 2)
      {
        sprintf(data2+counter,"%02x",data[count2] & 0xFF);
      }

      // add the block validation signature to the blockchain_data
      memcpy(blockchain_data.blockchain_reserve_bytes.block_validation_node_signature_data[count],data2,196);
      memcpy(blockchain_data.blockchain_reserve_bytes.block_validation_node_signature[count],data,XCASH_SIGN_DATA_LENGTH);
    }
  }

  // verify the blockchain_data
  if (verify_network_block_data(1) == 0)
  {
    CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR("Could not verify the blockchain_data\nFunction: consensus_node_create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK");
  }

  // convert the blockchain_data to a network_block_string
  memset(data,0,strnlen(data,BUFFER_SIZE));
  if (blockchain_data_to_network_block_string(data) == 0)
  {
    CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR("Could not convert the blockchain_data to a network_block_string\nFunction: consensus_node_create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK");
  }

  // wait until the NETWORK_BLOCK_TIME to submit the block to the network
  time(&current_date_and_time);
  current_UTC_date_and_time = gmtime(&current_date_and_time);
  while(current_UTC_date_and_time->tm_min % NETWORK_BLOCK_TIME != 0 && current_UTC_date_and_time->tm_sec == 0)
  {
    // wait for 100 milliseconds this way blocks are always submitted towards the begining of a minute for a constant block time
    usleep(100000);
  }

  // add the network block
  if (submit_block_template(data,0) == 0)
  {
    CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR("Could not submit the block to the network\nFunction: consensus_node_create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK");
  }

  // check if it should wait if the update_block_verifiers_timer is running
  time(&current_date_and_time);
  current_UTC_date_and_time = gmtime(&current_date_and_time);
  if (current_UTC_date_and_time->tm_hour % 2 == 0 && current_UTC_date_and_time->tm_min == 0)
  {  
    sleep(UPDATE_BLOCK_VERIFIERS_TIME);
  }

  // calculate the new main nodes roles from the previous network block
  if (calculate_main_nodes_role() == 0)
  {
    CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR("Could not calculate main nodes role\nFunction: consensus_node_create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK");
    // add another block to the network since the next round could not be started
    goto start;
  }

  start_current_round_part:

  // calculate the current_round_part and current_round_part_backup_node 
  if (mainode_consensus() == 0)
  {
    CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR("Could not get the current_round_part and current_round_part_backup_node\nFunction: consensus_node_create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK");
    // add another block to the network since the next round could not be started
    goto start;
  }

  // send the main nodes public address to the block verifiers
  if (send_data_socket_consensus_node_to_node() == 0)
  {
    CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR("Could not send the main nodes public address to the block verifiers\nFunction: consensus_node_create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK");
    // add another block to the network since the next round could not be started
    goto start;
  }

  // let the main node know they are the main node and they need to start the part of the round
  if (send_data_socket_consensus_node_to_mainnode() == 0)
  {
    CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR("Could not send the main nodes public address to the block verifiers\nFunction: consensus_node_create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK");
    // add another block to the network since the next round could not be started
    goto start_current_round_part;
  }

  // start the receive_votes_from_nodes_timeout
  if (pthread_create(&thread_id, NULL, &receive_votes_from_nodes_timeout_thread, NULL) != 0)
  {
    CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR("Could not start the receive_votes_from_nodes_timeout\nFunction: consensus_node_create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK");
    // add another block to the network since the next round could not be started
    goto start_current_round_part;
  }
  // set the thread to detach once completed, since we do not need to use anything it will return
  if (pthread_detach(thread_id) != 0)
  {
    CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR("Could not start the receive_votes_from_nodes_timeout\nFunction: consensus_node_create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK");
    // add another block to the network since the next round could not be started
    goto start_current_round_part;
  }

  // set the server message
  memset(server_message,0,strnlen(server_message,BUFFER_SIZE));
  memcpy(server_message,"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE|NODES_TO_CONSENSUS_NODE_VOTE_RESULTS",98);

  return 1;

  #undef pointer_reset_all
  #undef CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: calculate_main_nodes_role
Description: Calculate the new main nodes roles from the previous network block
Return: 1 if successfull, otherwise 0.
-----------------------------------------------------------------------------------------------------------
*/

int calculate_main_nodes_role()
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count;

  // define macros
  #define DATABASE_COLLECTION "nodes"
  #define MESSAGE "{\"username\":\"xcash\"}"

  #define pointer_reset_all \
  free(data); \
  data = NULL; \
  free(settings); \
  settings = NULL; 

  #define CALCULATE_MAIN_NODES_ROLE_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset(data); \
  return 0;


  // check if the memory needed was allocated on the heap successfully
  if (data == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // get the previous block template
  if (get_previous_block_template(data,0) == 0)
  {
    CALCULATE_MAIN_NODES_ROLE_ERROR("Could not get the previous block template\nFunction: calculate_main_nodes_role");
  }

  // convert the network_block_string to blockchain_data
  if (network_block_string_to_blockchain_data(data) == 0)
  {
    CALCULATE_MAIN_NODES_ROLE_ERROR("Could not convert the network_block_string to blockchain_data\nFunction: calculate_main_nodes_role");
  }

  // read the VRF beta string for round part 3 and calculate the main nodes role


  // update the main nodes role in the database
  

  // set the current_round_part and current_round_part_backup_node
  memset(current_round_part,0,strnlen(current_round_part,BUFFER_SIZE));
  memset(current_round_part_backup_node,0,strnlen(current_round_part_backup_node,BUFFER_SIZE));
  memcpy(current_round_part,"1",1);
  memcpy(current_round_part_backup_node,"0",1);

  // set the current_round_part and current_round_part_backup_node in the database
  if (update_document_from_collection(DATABASE_NAME,"current_round",MESSAGE,"{\"current_round_part\":\"1\"}",0) == 0 || update_document_from_collection(DATABASE_NAME,"current_round",MESSAGE,"{\"current_round_part_backup_node\":\"0\"}",0) == 0)
  {
    CALCULATE_MAIN_NODES_ROLE_ERROR("Could not update the current_round_part and current_round_part_backup_node in the database\nFunction: calculate_main_nodes_role");
  }

  return 1;

  #undef DATABASE_COLLECTION
  #undef MESSAGE
  #undef pointer_reset_all
  #undef CALCULATE_MAIN_NODES_ROLE_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: mainode_consensus
Description: Calculate the current_round_part and current_round_part_backup_node
Return: 1 if successfull, otherwise 0.
-----------------------------------------------------------------------------------------------------------
*/

int mainode_consensus()
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data2 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count;

  // define macros
  #define DATABASE_COLLECTION "nodes"
  #define MESSAGE "{\"username\":\"xcash\"}"

  #define pointer_reset_all \
  free(data); \
  data = NULL; \
  free(data2); \
  data2 = NULL;

  #define MAINNODE_CONSENSUS_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset_all; \
  return 0;


  // check if the memory needed was allocated on the heap successfully
  if (data == NULL || data2 == NULL)
  {
    if (data != NULL)
    {
      pointer_reset(data);
    }
    if (data2 != NULL)
    {
      pointer_reset(data2);
    }
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // read the current_round_part and current_round_part_backup_node from the database
  memset(current_round_part,0,strnlen(current_round_part,BUFFER_SIZE));
  memset(current_round_part_backup_node,0,strnlen(current_round_part_backup_node,BUFFER_SIZE));
  if (read_document_field_from_collection(DATABASE_NAME,"current_round",MESSAGE,"current_round_part",current_round_part,0) == 0 || read_document_field_from_collection(DATABASE_NAME,"current_round",MESSAGE,"current_round_part_backup_node",current_round_part_backup_node,0) == 0)
  {
     MAINNODE_CONSENSUS_ERROR("Could not read the current_round_part or the current_round_part_backup_node from the database\nFunction: mainode_consensus");
  }

  start:

  // reset the variables
  memset(data,0,strnlen(data,BUFFER_SIZE));
  memset(data2,0,strnlen(data2,BUFFER_SIZE));

  if (memcmp(current_round_part,"1",1) == 0 || memcmp(current_round_part,"3",1) == 0)
  {
    memcpy(data,"vrf_public_and_secret_key_IP_address_",37);
  }
  else if (memcmp(current_round_part,"2",1) == 0)
  {
    memcpy(data,"vrf_random_data_IP_address_",27);
  }
  else if (memcmp(current_round_part,"4",1) == 0)
  {
    memcpy(data,"block_producer_IP_address_",26);
  }
  memcpy(data+strnlen(data,BUFFER_SIZE),current_round_part_backup_node,1);

  // get the main nodes IP address and check if it is online  
  if (read_document_field_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,data2,0) == 0)
  {
    MAINNODE_CONSENSUS_ERROR("Could not read the main nodes IP address from the database\nFunction: mainode_consensus");
  }

  // check if the main node is online
  if (send_data_socket(data2,SEND_DATA_PORT,"","check if main node is online",0) == 0)
  {
    if (memcmp(current_round_part_backup_node,"0",1) == 0)
    {
      memcpy(current_round_part_backup_node,"1",1);
    }
    else if (memcmp(current_round_part_backup_node,"1",1) == 0)
    {
      memcpy(current_round_part_backup_node,"2",1);
    }
    else if (memcmp(current_round_part_backup_node,"2",1) == 0)
    {
      memcpy(current_round_part_backup_node,"3",1);
    }
    else if (memcmp(current_round_part_backup_node,"3",1) == 0)
    {
      memcpy(current_round_part_backup_node,"4",1);
    }
    else if (memcmp(current_round_part_backup_node,"4",1) == 0)
    {
      memcpy(current_round_part_backup_node,"5",1);
    }
    else if (memcmp(current_round_part_backup_node,"5",1) == 0)
    {
      pointer_reset_all;
      return 0;
    }
    memset(data,0,strnlen(data,BUFFER_SIZE));
    memcpy(data,"The main node is offline, so switching to the next backup main node.\ncurrent_round_part = ",90);
    memcpy(data+90,current_round_part,1);
    memcpy(data+91,"\ncurrent_round_part_backup_node = ",34);
    memcpy(data+125,current_round_part_backup_node,1);
    color_print(data,"red");
    goto start;
  }

  // set the current_round_part and current_round_part_backup_node in the database
  memset(data,0,strnlen(data,BUFFER_SIZE));
  memset(data2,0,strnlen(data2,BUFFER_SIZE));
  memcpy(data,"{\"current_round_part\":\"",23);
  memcpy(data,current_round_part,1);
  memcpy(data,"\"}",2);
  memcpy(data2,"{\"current_round_part_backup_node\":\"",38);
  memcpy(data2,current_round_part_backup_node,1);
  memcpy(data2,"\"}",2);
  if (update_document_from_collection(DATABASE_NAME,"current_round",MESSAGE,data,0) == 0 || update_document_from_collection(DATABASE_NAME,"current_round",MESSAGE,data2,0) == 0)
  {
    MAINNODE_CONSENSUS_ERROR("Could not update the current_round_part and current_round_part_backup_node in the database\nFunction: mainode_consensus");
  }

  pointer_reset_all;
  return 1;

  #undef DATABASE_COLLECTION
  #undef MESSAGE
  #undef pointer_reset_all
  #undef MAINNODE_CONSENSUS_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: send_data_socket_consensus_node_to_node
Description: Sends the CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS message to the block verifiers to let them know the main nodes public address for the current part of the round
Return: 1 if successfull, otherwise 0.
-----------------------------------------------------------------------------------------------------------
*/

int send_data_socket_consensus_node_to_node()
{
  // Variables
  char* message = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data2 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data3 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count;

  // define macros
  #define MESSAGE "{\"username\":\"xcash\"}"

  #define pointer_reset_all \
  free(message); \
  message = NULL; \
  free(data); \
  data = NULL; \
  free(data2); \
  data2 = NULL; \
  free(data3); \
  data3 = NULL;

  #define SEND_DATA_SOCKET_CONSENSUS_NODE_TO_NODE_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset_all; \
  return 0;

  // check if the memory needed was allocated on the heap successfully
  if (message == NULL || data == NULL || data2 == NULL || data3 == NULL)
  {
    if (message != NULL)
    {
      pointer_reset(message);
    }
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
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // read the current_round_part and current_round_part_backup_node from the database
  memset(current_round_part,0,strnlen(current_round_part,BUFFER_SIZE));
  memset(current_round_part_backup_node,0,strnlen(current_round_part_backup_node,BUFFER_SIZE));
  if (read_document_field_from_collection(DATABASE_NAME,"current_round",MESSAGE,"current_round_part",current_round_part,0) == 0 || read_document_field_from_collection(DATABASE_NAME,"current_round",MESSAGE,"current_round_part_backup_node",current_round_part_backup_node,0) == 0)
  {
     SEND_DATA_SOCKET_CONSENSUS_NODE_TO_NODE_ERROR("Could not read the current_round_part or the current_round_part_backup_node from the database\nFunction: send_data_socket_consensus_node_to_node\nSend Message: CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS");
  }

  if (memcmp(current_round_part,"1",1) == 0 || memcmp(current_round_part,"3",1) == 0)
  {
    memcpy(data,"vrf_public_and_secret_key_public_address_",41);
  }
  else if (memcmp(current_round_part,"2",1) == 0)
  {
    memcpy(data,"vrf_random_data_public_address_",31);
  }
  else if (memcmp(current_round_part,"4",1) == 0)
  {
    memcpy(data,"block_producer_public_address_",30);
  }
  memcpy(data+strnlen(data,BUFFER_SIZE),current_round_part_backup_node,1);

  // get the main nodes public address from the database 
  if (read_document_field_from_collection(DATABASE_NAME,"nodes",MESSAGE,data,data2,0) == 0)
  {
    SEND_DATA_SOCKET_CONSENSUS_NODE_TO_NODE_ERROR("Could not read the main nodes data from the database\nFunction: send_data_socket_consensus_node_to_node\nSend Message: CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS");
  }

  memset(data,0,strnlen(data,BUFFER_SIZE));
  if (memcmp(current_round_part,"1",1) == 0 || memcmp(current_round_part,"3",1) == 0)
  {
    memcpy(data,"vrf_public_and_secret_key_IP_address_",37);
  }
  else if (memcmp(current_round_part,"2",1) == 0)
  {
    memcpy(data,"vrf_random_data_IP_address_",27);
  }
  else if (memcmp(current_round_part,"4",1) == 0)
  {
    memcpy(data,"block_producer_IP_address_",26);
  }
  memcpy(data+strnlen(data,BUFFER_SIZE),current_round_part_backup_node,1);

  // get the main nodes IP address from the database 
  if (read_document_field_from_collection(DATABASE_NAME,"nodes",MESSAGE,data,data3,0) == 0)
  {
    SEND_DATA_SOCKET_CONSENSUS_NODE_TO_NODE_ERROR("Could not read the main nodes data from the database\nFunction: send_data_socket_consensus_node_to_node\nSend Message: CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS");
  }

  // create the message
  memcpy(message,"{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS\",\r\n \"main_nodes_public_address\": \"",108);
  memcpy(message+108,data2,XCASH_WALLET_LENGTH);
  memcpy(message+108+XCASH_WALLET_LENGTH,"\",\r\n}",5);

  // sign_data
  if (sign_data(message,0) == 0)
  { 
    SEND_DATA_SOCKET_CONSENSUS_NODE_TO_NODE_ERROR("Could not sign_data\nFunction: send_data_socket_consensus_node_to_node\nSend Message: CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS");
  }

  // send the message to all block verifiers
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    send_data_socket(data3,SEND_DATA_PORT,message,"sending CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS to the block verifiers",0);
  }

  // save the main nodes public address in the database
  memset(message,0,strnlen(message,BUFFER_SIZE)); 
  if (memcmp(current_round_part,"1",1) == 0 || memcmp(current_round_part,"3",1) == 0)
  {
    memcpy(message,"{\"vrf_node_public_and_private_key_public_address\":\"",51); 
    count = 51;   
  }
  else if (memcmp(current_round_part,"2",1) == 0)
  {
    memcpy(message,"{\"vrf_node_random_data_public_address\":\"",43); 
    count = 51; 
  }
  else if (memcmp(current_round_part,"4",1) == 0)
  {
    memcpy(message,"{\"block_producer_public_address\":\"",34); 
    count = 51; 
  }

  memcpy(message+count,data2,XCASH_WALLET_LENGTH);
  memcpy(message+count+XCASH_WALLET_LENGTH,"\"}",2);
  if (update_document_from_collection(DATABASE_NAME,"current_round",MESSAGE,message,0) == 0)
  {
    SEND_DATA_SOCKET_CONSENSUS_NODE_TO_NODE_ERROR("Could not update the current main nodes public address in the database\nFunction: send_round_change\nFunction: send_data_socket_consensus_node_to_node\nSend Message: CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS");
  }

  pointer_reset_all;
  return 1;

  #undef MESSAGE
  #undef pointer_reset_all
  #undef SEND_DATA_SOCKET_CONSENSUS_NODE_TO_NODE_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: send_data_socket_consensus_node_to_mainnode
Description: Sends the CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND message to the main node to let the main node know to start the part of the round
Return: 1 if successfull, otherwise 0.
-----------------------------------------------------------------------------------------------------------
*/

int send_data_socket_consensus_node_to_mainnode()
{
  // Variables
  char* message = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data2 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data3 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count;

  // define macros
  #define MESSAGE "{\"username\":\"xcash\"}"

  #define pointer_reset_all \
  free(message); \
  message = NULL; \
  free(data); \
  data = NULL; \
  free(data2); \
  data2 = NULL; \
  free(data3); \
  data3 = NULL;

  #define SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset_all; \
  return 0;

  // check if the memory needed was allocated on the heap successfully
  if (message == NULL || data == NULL || data2 == NULL || data3 == NULL)
  {
    if (message != NULL)
    {
      pointer_reset(message);
    }
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
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // read the current_round_part and current_round_part_backup_node from the database
  memset(current_round_part,0,strnlen(current_round_part,BUFFER_SIZE));
  memset(current_round_part_backup_node,0,strnlen(current_round_part_backup_node,BUFFER_SIZE));
  if (read_document_field_from_collection(DATABASE_NAME,"current_round",MESSAGE,"current_round_part",current_round_part,0) == 0 || read_document_field_from_collection(DATABASE_NAME,"current_round",MESSAGE,"current_round_part_backup_node",current_round_part_backup_node,0) == 0)
  {
     SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR("Could not read the current_round_part or the current_round_part_backup_node from the database\nFunction: send_data_socket_consensus_node_to_mainnode\nSend Message: CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND");
  }

  if (memcmp(current_round_part,"1",1) == 0 || memcmp(current_round_part,"3",1) == 0)
  {
    memcpy(data,"vrf_public_and_secret_key_IP_address_",37);
  }
  else if (memcmp(current_round_part,"2",1) == 0)
  {
    memcpy(data,"vrf_random_data_IP_address_",27);
  }
  else if (memcmp(current_round_part,"4",1) == 0)
  {
    memcpy(data,"block_producer_IP_address_",26);
  }
  memcpy(data+strnlen(data,BUFFER_SIZE),current_round_part_backup_node,1);

  // get the main nodes IP address from the database 
  if (read_document_field_from_collection(DATABASE_NAME,"nodes",MESSAGE,data,data2,0) == 0)
  {
    SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR("Could not read the main nodes data from the database\nFunction: send_data_socket_consensus_node_to_mainnode\nSend Message: CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND");
  }

  if (memcmp(current_round_part,"4",1) == 0)
  {
    // read all of the VRF data from the database
    memset(data,0,strnlen(data,BUFFER_SIZE));
    count = 0;
    if (read_document_field_from_collection(DATABASE_NAME,"nodes",MESSAGE,"vrf_public_key_round_part_1",data,0) == 0)
    {
      SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR("Could not read the VRF data from the database\nFunction: send_data_socket_consensus_node_to_mainnode\nSend Message: CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND");
    }
    memcpy(data3+count,data,strnlen(data,BUFFER_SIZE));
    count += strnlen(data,BUFFER_SIZE);

    memset(data,0,strnlen(data,BUFFER_SIZE));
    if (read_document_field_from_collection(DATABASE_NAME,"nodes",MESSAGE,"vrf_alpha_string_round_part_1",data,0) == 0)
    {
      SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR("Could not read the VRF data from the database\nFunction: send_data_socket_consensus_node_to_mainnode\nSend Message: CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND");
    }
    memcpy(data3+count,data,strnlen(data,BUFFER_SIZE));
    count += strnlen(data,BUFFER_SIZE);

    memset(data,0,strnlen(data,BUFFER_SIZE));
    if (read_document_field_from_collection(DATABASE_NAME,"nodes",MESSAGE,"vrf_proof_round_part_1",data,0) == 0)
    {
      SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR("Could not read the VRF data from the database\nFunction: send_data_socket_consensus_node_to_mainnode\nSend Message: CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND");
    }
    memcpy(data3+count,data,strnlen(data,BUFFER_SIZE));
    count += strnlen(data,BUFFER_SIZE);
    
    memset(data,0,strnlen(data,BUFFER_SIZE));
    if (read_document_field_from_collection(DATABASE_NAME,"nodes",MESSAGE,"vrf_beta_string_round_part_1",data,0) == 0)
    {
      SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR("Could not read the VRF data from the database\nFunction: send_data_socket_consensus_node_to_mainnode\nSend Message: CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND");
    }
    memcpy(data3+count,data,strnlen(data,BUFFER_SIZE));
    count += strnlen(data,BUFFER_SIZE);

    memset(data,0,strnlen(data,BUFFER_SIZE));
    if (read_document_field_from_collection(DATABASE_NAME,"nodes",MESSAGE,"vrf_public_key_round_part_2",data,0) == 0)
    {
      SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR("Could not read the VRF data from the database\nFunction: send_data_socket_consensus_node_to_mainnode\nSend Message: CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND");
    }
    memcpy(data3+count,data,strnlen(data,BUFFER_SIZE));
    count += strnlen(data,BUFFER_SIZE);

    memset(data,0,strnlen(data,BUFFER_SIZE));
    if (read_document_field_from_collection(DATABASE_NAME,"nodes",MESSAGE,"vrf_alpha_string_round_part_2",data,0) == 0)
    {
      SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR("Could not read the VRF data from the database\nFunction: send_data_socket_consensus_node_to_mainnode\nSend Message: CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND");
    }
    memcpy(data3+count,data,strnlen(data,BUFFER_SIZE));
    count += strnlen(data,BUFFER_SIZE);

    memset(data,0,strnlen(data,BUFFER_SIZE));
    if (read_document_field_from_collection(DATABASE_NAME,"nodes",MESSAGE,"vrf_proof_round_part_2",data,0) == 0)
    {
      SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR("Could not read the VRF data from the database\nFunction: send_data_socket_consensus_node_to_mainnode\nSend Message: CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND");
    }
    memcpy(data3+count,data,strnlen(data,BUFFER_SIZE));
    count += strnlen(data,BUFFER_SIZE);
    
    memset(data,0,strnlen(data,BUFFER_SIZE));
    if (read_document_field_from_collection(DATABASE_NAME,"nodes",MESSAGE,"vrf_beta_string_round_part_2",data,0) == 0)
    {
      SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR("Could not read the VRF data from the database\nFunction: send_data_socket_consensus_node_to_mainnode\nSend Message: CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND");
    }
    memcpy(data3+count,data,strnlen(data,BUFFER_SIZE));
    count += strnlen(data,BUFFER_SIZE);

    memset(data,0,strnlen(data,BUFFER_SIZE));
    if (read_document_field_from_collection(DATABASE_NAME,"nodes",MESSAGE,"vrf_public_key_round_part_3",data,0) == 0)
    {
      SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR("Could not read the VRF data from the database\nFunction: send_data_socket_consensus_node_to_mainnode\nSend Message: CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND");
    }
    memcpy(data3+count,data,strnlen(data,BUFFER_SIZE));
    count += strnlen(data,BUFFER_SIZE);

    memset(data,0,strnlen(data,BUFFER_SIZE));
    if (read_document_field_from_collection(DATABASE_NAME,"nodes",MESSAGE,"vrf_alpha_string_round_part_3",data,0) == 0)
    {
      SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR("Could not read the VRF data from the database\nFunction: send_data_socket_consensus_node_to_mainnode\nSend Message: CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND");
    }
    memcpy(data3+count,data,strnlen(data,BUFFER_SIZE));
    count += strnlen(data,BUFFER_SIZE);

    memset(data,0,strnlen(data,BUFFER_SIZE));
    if (read_document_field_from_collection(DATABASE_NAME,"nodes",MESSAGE,"vrf_proof_round_part_3",data,0) == 0)
    {
      SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR("Could not read the VRF data from the database\nFunction: send_data_socket_consensus_node_to_mainnode\nSend Message: CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND");
    }
    memcpy(data3+count,data,strnlen(data,BUFFER_SIZE));
    count += strnlen(data,BUFFER_SIZE);
    
    memset(data,0,strnlen(data,BUFFER_SIZE));
    if (read_document_field_from_collection(DATABASE_NAME,"nodes",MESSAGE,"vrf_beta_string_round_part_3",data,0) == 0)
    {
      SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR("Could not read the VRF data from the database\nFunction: send_data_socket_consensus_node_to_mainnode\nSend Message: CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND");
    }
    memcpy(data3+count,data,strnlen(data,BUFFER_SIZE));
    count += strnlen(data,BUFFER_SIZE);

    // create the message
    memcpy(message,"{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND\",\r\n \"message\": \"",90);
    memcpy(message+90,current_round_part,1);
    memcpy(message+91,"\",\r\n \"VRF_block_blob\": \"",24);
    memcpy(message+115,data3,strnlen(data3,BUFFER_SIZE));
    memcpy(message+115+strnlen(data3,BUFFER_SIZE),"\",\r\n}",5);
  }
  else
  {
    // create the message
    memcpy(message,"{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND\",\r\n \"message\": \"4\",\r\n \"VRF_block_blob\": \"\",\r\n}",120);
  }

  // sign_data
  if (sign_data(message,0) == 0)
  { 
    SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR("Could not sign_data\nFunction: send_data_socket_consensus_node_to_mainnode\nSend Message: CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND");
  }

  // send the message to the main node
  send_data_socket(data2,SEND_DATA_PORT,message,"sending CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND to the block verifiers",0);
  
  pointer_reset_all;
  return 1;

  #undef MESSAGE
  #undef pointer_reset_all
  #undef SEND_DATA_SOCKET_CONSENSUS_NODE_TO_MAINNODE_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: server_received_data_xcash_proof_of_stake_test_data
Description: Runs the code when the server receives the xcash_proof_of_stake_test_data message
Parameters:
  CLIENT_SOCKET - The socket to send data to
  message - The message
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int server_received_data_xcash_proof_of_stake_test_data(const int CLIENT_SOCKET, char* MESSAGE)
{
  // verify the message
  if (verify_data(MESSAGE,0,1,1) == 0)
  {   
    return 0;
  }
  else
  {
    if (send_data(CLIENT_SOCKET,MESSAGE,1) == 1)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }  
}


/*
-----------------------------------------------------------------------------------------------------------
Name: server_receive_data_socket_node_to_consensus_node_send_current_consensus_node_IP_address
Description: Runs the code when the server receives the NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS message
Parameters:
  CLIENT_SOCKET - The socket to send data to
  message - The message
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int server_receive_data_socket_node_to_consensus_node_send_current_consensus_node_IP_address(const int CLIENT_SOCKET, char* message)
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data2 = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // define macros
  #define MESSAGE "{\"username\":\"xcash\"}"

  #define pointer_reset_all \
  free(data); \
  data = NULL; \
  free(data2); \
  data2 = NULL;

  #define SERVER_RECEIVE_DATA_SOCKET_NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset_all; \
  return 0;

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL || data2 == NULL)
  {
    if (data != NULL)
    {
      pointer_reset(data);
    }
    if (data2 != NULL)
    {
      pointer_reset(data2);
    }
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // read the current_round_part and current_round_part_backup_node from the database
  memset(current_round_part,0,strnlen(current_round_part,BUFFER_SIZE));
  memset(current_round_part_backup_node,0,strnlen(current_round_part_backup_node,BUFFER_SIZE));
  if (read_document_field_from_collection(DATABASE_NAME,"current_round",MESSAGE,"current_round_part",current_round_part,0) == 0 || read_document_field_from_collection(DATABASE_NAME,"current_round",MESSAGE,"current_round_part_backup_node",current_round_part_backup_node,0) == 0)
  {
     SERVER_RECEIVE_DATA_SOCKET_NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS_ERROR("Could not read the current_round_part or the current_round_part_backup_node from the database\nFunction: server_receive_data_socket_node_to_consensus_node_send_current_consensus_node_IP_address\nReceive Message: NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS\nSend Message: CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS");
  }

  // verify the data
  if (verify_data(message,0,1,1) == 0)
  {
    SERVER_RECEIVE_DATA_SOCKET_NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS_ERROR("Could not sign_data\nFunction: server_receive_data_socket_node_to_consensus_node_send_current_consensus_node_IP_address\nReceive Message: NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS\nSend Message: CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS");
    return 0;
  }

  // read the current_consensus_node_IP_address from the consensus_node collection
  if (read_document_field_from_collection(DATABASE_NAME,"consensus_node",MESSAGE,"current_consensus_node_IP_address",data,0) == 0)
  {
    SERVER_RECEIVE_DATA_SOCKET_NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS_ERROR("Could not get the current consensus node from the database\nFunction: server_receive_data_socket_node_to_consensus_node_send_current_consensus_node_IP_address\nReceive Message: NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS\nSend Message: CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS");
  }

  // create the message
  memcpy(data2,"{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n \"current_consensus_node_IP_address\": \"",132);
  memcpy(data2+132,data,XCASH_WALLET_LENGTH);
  memcpy(data2+132+XCASH_WALLET_LENGTH,"\",\r\n}",5);

  // sign_data
  if (sign_data(data2,0) == 0)
  { 
    SERVER_RECEIVE_DATA_SOCKET_NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS_ERROR("Could not sign data\nFunction: server_receive_data_socket_node_to_consensus_node_send_current_consensus_node_IP_address\nReceive Message: NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS\nSend Message: CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS");
  }

  // send the data back to the main node on the client socket, since it used the send_and_receive_data_socket
  if (send_data(CLIENT_SOCKET,data2,1) == 0)
  {
    SERVER_RECEIVE_DATA_SOCKET_NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS_ERROR("Could not send the CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS message to the block verifier\nFunction: server_receive_data_socket_node_to_consensus_node_send_current_consensus_node_IP_address\nReceive Message: NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS\nSend Message: CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS");
  }
  
  pointer_reset_all;
  return 1;

  #undef MESSAGE
  #undef pointer_reset_all
  #undef SERVER_RECEIVE_DATA_SOCKET_NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: server_receive_data_socket_node_to_consensus_node_send_updated_node_list
Description: Runs the code when the server receives the NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST message
Parameters:
  CLIENT_SOCKET - The socket to send data to
  message - The message
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int server_receive_data_socket_node_to_consensus_node_send_updated_node_list(const int CLIENT_SOCKET, char* message)
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data2 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* nodes_name_list = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* nodes_public_address_list = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* nodes_IP_address_list = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count;
  size_t count2;

  // define macros
  #define MESSAGE "{\"username\":\"xcash\"}"

  #define pointer_reset_all \
  free(data); \
  data = NULL; \
  free(data2); \
  data2 = NULL; \
  free(nodes_name_list); \
  nodes_name_list = NULL; \
  free(nodes_public_address_list); \
  nodes_public_address_list = NULL; \
  free(nodes_IP_address_list); \
  nodes_IP_address_list = NULL;

  #define SERVER_RECEIVE_DATA_SOCKET_NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset_all; \
  return 0;

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL || data2 == NULL || nodes_name_list == NULL || nodes_public_address_list == NULL || nodes_IP_address_list == NULL)
  {
    if (data != NULL)
    {
      pointer_reset(data);
    }
    if (data2 != NULL)
    {
      pointer_reset(data2);
    }
    if (nodes_name_list != NULL)
    {
      pointer_reset(nodes_name_list);
    }
    if (nodes_public_address_list != NULL)
    {
      pointer_reset(nodes_public_address_list);
    }
    if (nodes_IP_address_list != NULL)
    {
      pointer_reset(nodes_IP_address_list);
    }
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // read the current_round_part and current_round_part_backup_node from the database
  memset(current_round_part,0,strnlen(current_round_part,BUFFER_SIZE));
  memset(current_round_part_backup_node,0,strnlen(current_round_part_backup_node,BUFFER_SIZE));
  if (read_document_field_from_collection(DATABASE_NAME,"current_round",MESSAGE,"current_round_part",current_round_part,0) == 0 || read_document_field_from_collection(DATABASE_NAME,"current_round",MESSAGE,"current_round_part_backup_node",current_round_part_backup_node,0) == 0)
  {
     SERVER_RECEIVE_DATA_SOCKET_NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST_ERROR("Could not read the current_round_part or the current_round_part_backup_node from the database\nFunction: server_receive_data_socket_node_to_consensus_node_send_updated_node_list\nReceive Message: NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST\nSend Message: CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST");
  }

  // verify the data
  if (verify_data(message,0,1,1) == 0)
  {
    SERVER_RECEIVE_DATA_SOCKET_NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST_ERROR("Could not sign_data\nFunction: server_receive_data_socket_node_to_consensus_node_send_updated_node_list\nReceive Message: NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST\nSend Message: CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST");
    return 0;
  }

  // parse the message
  if (parse_json_data(message,"message",data) == 0)
  {
    SERVER_RECEIVE_DATA_SOCKET_NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST_ERROR("Could not parse data\nFunction: server_receive_data_socket_node_to_consensus_node_send_updated_node_list\nReceive Message: NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST\nSend Message: CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST");
  }

  // read the nodes_updated_time from the consensus_node collection
  if (read_document_field_from_collection(DATABASE_NAME,"consensus_node",MESSAGE,"nodes_updated_time",data2,0) == 0)
  {
    SERVER_RECEIVE_DATA_SOCKET_NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST_ERROR("Could not get the current consensus node from the database\nFunction: server_receive_data_socket_node_to_consensus_node_send_updated_node_list\nReceive Message: NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST\nSend Message: CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST");
  }

  // check if the block verifier needs to have an updated block verifiers list
  sscanf(data, "%zu", &count);
  sscanf(data2, "%zu", &count2);
  if (count < count2)
  {
    memset(data,0,strnlen(data,BUFFER_SIZE));
    memset(data2,0,strnlen(data2,BUFFER_SIZE));

    // create the nodes_name_list
    memcpy(nodes_name_list,"{",1);
    count2 = 0;
    for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
    {
      memcpy(nodes_name_list+count2,"\r\n \\\"node",9);
      count2 += 9;
      sprintf(nodes_name_list+count2,"%zu",count);
      if (count < 10)
      {
        count2++;
      }
      else
      {
        count2 += 2;
      }
      memcpy(nodes_name_list+count2,"\\\": \\\"",6);
      count2 += 6;
      memcpy(nodes_name_list+count2,block_verifiers_list.block_verifiers_name[count],strnlen(block_verifiers_list.block_verifiers_name[count],BLOCK_VERIFIERS_NAME_TOTAL_LENGTH+1));
      count2 += strnlen(block_verifiers_list.block_verifiers_name[count],BLOCK_VERIFIERS_NAME_TOTAL_LENGTH+1);
      memcpy(nodes_name_list+count2,"\\\",",3);
      count2 += 3;
    }
    memcpy(nodes_name_list+count2,"\r\n}",3);

    // create the nodes_public_address_list
    memcpy(nodes_public_address_list,"{",1);
    count2 = 0;
    for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
    {
      memcpy(nodes_public_address_list+count2,"\r\n \\\"node",9);
      count2 += 9;
      sprintf(nodes_public_address_list+count2,"%zu",count);
      if (count < 10)
      {
        count2++;
      }
      else
      {
        count2 += 2;
      }
      memcpy(nodes_public_address_list+count2,"\\\": \\\"",6);
      count2 += 6;
      memcpy(nodes_public_address_list+count2,block_verifiers_list.block_verifiers_public_address[count],strnlen(block_verifiers_list.block_verifiers_name[count],XCASH_WALLET_LENGTH+1));
      count2 += strnlen(block_verifiers_list.block_verifiers_public_address[count],XCASH_WALLET_LENGTH+1);
      memcpy(nodes_public_address_list+count2,"\\\",",3);
      count2 += 3;
    }
    memcpy(nodes_public_address_list+count2,"\r\n}",3);

    // create the nodes_IP_address_list
    memcpy(nodes_IP_address_list,"{",1);
    count2 = 0;
    for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
    {
      memcpy(nodes_IP_address_list+count2,"\r\n \\\"node",9);
      count2 += 9;
      sprintf(nodes_IP_address_list+count2,"%zu",count);
      if (count < 10)
      {
        count2++;
      }
      else
      {
        count2 += 2;
      }
      memcpy(nodes_IP_address_list+count2,"\\\": \\\"",6);
      count2 += 6;
      memcpy(nodes_IP_address_list+count2,block_verifiers_list.block_verifiers_IP_address[count],strnlen(block_verifiers_list.block_verifiers_name[count],BLOCK_VERIFIERS_IP_ADDRESS_TOTAL_LENGTH+1));
      count2 += strnlen(block_verifiers_list.block_verifiers_IP_address[count],BLOCK_VERIFIERS_IP_ADDRESS_TOTAL_LENGTH+1);
      memcpy(nodes_IP_address_list+count2,"\\\",",3);
      count2 += 3;
    }
    memcpy(nodes_IP_address_list+count2,"\r\n}",3);

    // create the message
    memcpy(data,"{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST\",\r\n \"nodes_name_list\": \"",98);
    count = 98;
    memcpy(data+count,nodes_name_list,strnlen(nodes_name_list,BUFFER_SIZE));
    count += strnlen(nodes_name_list,BUFFER_SIZE);
    memcpy(data+count,"\",\r\n \"nodes_public_address_list\": \"",35);
    count += 35;
    memcpy(data+count,nodes_public_address_list,strnlen(nodes_public_address_list,BUFFER_SIZE));
    count += strnlen(nodes_public_address_list,BUFFER_SIZE);
    memcpy(data+count,"\",\r\n \"nodes_IP_address_list\": \"",31);
    count += 31;
    memcpy(data+count,nodes_IP_address_list,strnlen(nodes_IP_address_list,BUFFER_SIZE));
    count += strnlen(nodes_IP_address_list,BUFFER_SIZE);
    memcpy(data+count,"\",\r\n}",5);
  }
  else
  {
    // create the message
    memcpy(data,"{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST\",\r\n \"nodes_name_list\": \"UPDATED_NODE_LIST\",\r\n \"nodes_public_address_list\": \"UPDATED_NODE_LIST\",\r\n \"nodes_IP_address_list\": \"UPDATED_NODE_LIST\",\r\n}",220);
  }

  // sign_data
  if (sign_data(data,0) == 0)
  { 
    SERVER_RECEIVE_DATA_SOCKET_NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST_ERROR("Could not sign data\nFunction: server_receive_data_socket_node_to_consensus_node_send_updated_node_list\nReceive Message: NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST\nSend Message: CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST");
  }

  // send the data back to the main node on the client socket, since it used the send_and_receive_data_socket
  if (send_data(CLIENT_SOCKET,data2,1) == 0)
  {
    SERVER_RECEIVE_DATA_SOCKET_NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST_ERROR("Could not send the CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS message to the block verifier\nFunction: server_receive_data_socket_node_to_consensus_node_send_updated_node_list\nReceive Message: NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST\nSend Message: CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST");
  }
 
  pointer_reset_all;
  return 1;

  #undef pointer_reset_all
  #undef SERVER_RECEIVE_DATA_SOCKET_NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: verify_block_verifier_vote
Description: Checks if the public address that voted is in the current block_verifiers_list, and checks if the block verifier has already voted
Parameters:
  public_address - The public address
Return: 0 if the vote is not verified or an error has occured, 1 if the vote is verified
-----------------------------------------------------------------------------------------------------------
*/

int verify_block_verifier_vote(char* public_address)
{
  // Variables
  size_t count;
  int settings = 0;

  // check if the public address that voted is in the current block_verifiers_list
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    if (memcmp(block_verifiers_list.block_verifiers_public_address[count],public_address,XCASH_WALLET_LENGTH) == 0)
    {
      settings = 1;
    }
  }

  if (settings == 0)
  {
    return 0;
  }

  // check if the vote is verified and if the block verifier has already voted
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    if (memcmp(mainnode_timeout.block_verifiers_public_address[count],public_address,XCASH_WALLET_LENGTH) == 0 || memcmp(node_to_node_vote.block_verifiers_public_address_vote_next_round_true[count],public_address,XCASH_WALLET_LENGTH) == 0 || memcmp(node_to_node_vote.block_verifiers_public_address_vote_next_round_false[count],public_address,XCASH_WALLET_LENGTH) == 0)
    {
      settings = 0;
    }
  }

  return settings; 
}



/*
-----------------------------------------------------------------------------------------------------------
Name: server_receive_data_socket_main_node_timeout_from_node
Description: Runs the code when the server receives the NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE message
Parameters:
  CLIENT_SOCKET - The socket to send data to
  message - The message
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int server_receive_data_socket_main_node_timeout_from_node(char* message)
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data2 = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // define macros
  #define pointer_reset_all \
  free(data); \
  data = NULL; \
  free(data2); \
  data2 = NULL;

  #define SERVER_RECEIVE_DATA_SOCKET_MAIN_NODE_TIMEOUT_FROM_NODE_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset_all; \
  return 0;

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL || data2 == NULL)
  {
    if (data != NULL)
    {
      pointer_reset(data);
    }
    if (data2 != NULL)
    {
      pointer_reset(data2);
    }
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // read the current_round_part and current_round_part_backup_node from the database
  memset(current_round_part,0,strnlen(current_round_part,BUFFER_SIZE));
  memset(current_round_part_backup_node,0,strnlen(current_round_part_backup_node,BUFFER_SIZE));
  if (read_document_field_from_collection(DATABASE_NAME,"current_round",MESSAGE,"current_round_part",current_round_part,0) == 0 || read_document_field_from_collection(DATABASE_NAME,"current_round",MESSAGE,"current_round_part_backup_node",current_round_part_backup_node,0) == 0)
  {
     SERVER_RECEIVE_DATA_SOCKET_MAIN_NODE_TIMEOUT_FROM_NODE_ERROR("Could not read the current_round_part or the current_round_part_backup_node from the database\nFunction: server_receive_data_socket_main_node_timeout_from_node\nReceive Message: NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE");
  }

  // verify the data
  if (verify_data(message,0,1,1) == 0)
  {
    SERVER_RECEIVE_DATA_SOCKET_MAIN_NODE_TIMEOUT_FROM_NODE_ERROR("Could not sign_data\nFunction: server_receive_data_socket_main_node_timeout_from_node\nReceive Message: NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE");
    return 0;
  }

  // parse the message
  if (parse_json_data(message,"public_address",data) == 0)
  {
    SERVER_RECEIVE_DATA_SOCKET_MAIN_NODE_TIMEOUT_FROM_NODE_ERROR("Could not parse data\nFunction: server_receive_data_socket_main_node_timeout_from_node\nReceive Message: NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE");
  }

  // check if the block verifier has already voted
  if (verify_block_verifier_vote(data) == 0)
  {
    memcpy(data2,"The vote is not valid from public address ",42);
    memcpy(data2+42,data,strnlen(data,BUFFER_SIZE));
    memcpy(data2+42+strnlen(data,BUFFER_SIZE),"\nFunction: server_receive_data_socket_main_node_timeout_from_node\nReceive Message: NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE",144);
    SERVER_RECEIVE_DATA_SOCKET_MAIN_NODE_TIMEOUT_FROM_NODE_ERROR(data2);
  }

  // add one vote and the public address to the mainnode_timeout struct
  memcpy(mainnode_timeout.block_verifiers_public_address[mainnode_timeout.vote_round_change_timeout],data,XCASH_WALLET_LENGTH);
  mainnode_timeout.vote_round_change_timeout++;

  return 1;

  #undef pointer_reset_all
  #undef SERVER_RECEIVE_DATA_SOCKET_MAIN_NODE_TIMEOUT_FROM_NODE_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: server_receive_data_socket_node_to_node_vote
Description: Runs the code when the server receives the NODES_TO_CONSENSUS_NODE_VOTE_RESULTS message
Parameters:
  CLIENT_SOCKET - The socket to send data to
  message - The message
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int server_receive_data_socket_node_to_node_vote(char* message)
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data2 = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // define macros
  #define pointer_reset_all \
  free(data); \
  data = NULL; \
  free(data2); \
  data2 = NULL;

  #define SERVER_RECEIVE_DATA_SOCKET_NOTE_TO_NODE_VOTE_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset_all; \
  return 0;

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL || data2 == NULL)
  {
    if (data != NULL)
    {
      pointer_reset(data);
    }
    if (data2 != NULL)
    {
      pointer_reset(data2);
    }
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // read the current_round_part and current_round_part_backup_node from the database
  memset(current_round_part,0,strnlen(current_round_part,BUFFER_SIZE));
  memset(current_round_part_backup_node,0,strnlen(current_round_part_backup_node,BUFFER_SIZE));
  if (read_document_field_from_collection(DATABASE_NAME,"current_round",MESSAGE,"current_round_part",current_round_part,0) == 0 || read_document_field_from_collection(DATABASE_NAME,"current_round",MESSAGE,"current_round_part_backup_node",current_round_part_backup_node,0) == 0)
  {
     SERVER_RECEIVE_DATA_SOCKET_NOTE_TO_NODE_VOTE_ERROR("Could not read the current_round_part or the current_round_part_backup_node from the database\nFunction: server_receive_data_socket_node_to_node_vote\nReceive Message: NODES_TO_CONSENSUS_NODE_VOTE_RESULTS");
  }

  // verify the data
  if (verify_data(message,0,1,1) == 0)
  {
    SERVER_RECEIVE_DATA_SOCKET_NOTE_TO_NODE_VOTE_ERROR("Could not sign_data\nFunction: server_receive_data_socket_node_to_node_vote\nReceive Message: NODES_TO_CONSENSUS_NODE_VOTE_RESULTS");
    return 0;
  }

  // parse the message
  if (parse_json_data(message,"public_address",data) == 0 || parse_json_data(message,"vote_result",data2) == 0)
  {
    SERVER_RECEIVE_DATA_SOCKET_NOTE_TO_NODE_VOTE_ERROR("Could not parse data\nFunction: server_receive_data_socket_node_to_node_vote\nReceive Message: NODES_TO_CONSENSUS_NODE_VOTE_RESULTS");
  }

  // check if the block verifier has already voted
  if (verify_block_verifier_vote(data) == 0)
  {
    memset(data2,0,strnlen(data2,BUFFER_SIZE));
    memcpy(data2,"The vote is not valid from public address ",42);
    memcpy(data2+42,data,strnlen(data,BUFFER_SIZE));
    memcpy(data2+42+strnlen(data,BUFFER_SIZE),"\nFunction: server_receive_data_socket_node_to_node_vote\nReceive Message: NODES_TO_CONSENSUS_NODE_VOTE_RESULTS",144);
    SERVER_RECEIVE_DATA_SOCKET_NOTE_TO_NODE_VOTE_ERROR(data2);
  }

  // add one vote and the public address to the node_to_node_vote struct
  if (memcmp(data2,"TRUE",4) == 0)
  {
    memcpy(node_to_node_vote.block_verifiers_public_address_vote_next_round_true[node_to_node_vote.vote_next_round_true],data,XCASH_WALLET_LENGTH);
    node_to_node_vote.vote_next_round_true++;
  }
  else if (memcmp(data2,"FALSE",5) == 0)
  {
    memcpy(node_to_node_vote.block_verifiers_public_address_vote_next_round_false[node_to_node_vote.vote_next_round_false],data,XCASH_WALLET_LENGTH);
    node_to_node_vote.vote_next_round_false++;
  }

  // if the block verifiers public address is a trusted block verifier, add the VRF data to the trusted_block_verifiers_VRF_data
  

  return 1;

  #undef pointer_reset_all
  #undef SERVER_RECEIVE_DATA_SOCKET_NOTE_TO_NODE_VOTE_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: send_round_change
Description: sends the CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE message to each block verifier
-----------------------------------------------------------------------------------------------------------
*/

int send_round_change()
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count;

  // define macros
  #define DATABASE_COLLECTION "current_round"
  #define MESSAGE "{\"username\":\"xcash\"}"

  #define SEND_ROUND_CHANGE_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset(data); \
  return 0;

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // create the message
  memcpy(data,"{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND\",\r\n}",79);

  // sign_data
  if (sign_data(data,0) == 0)
  { 
    SEND_ROUND_CHANGE_ERROR("Could not sign_data\nFunction: send_round_change\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE");
  }

  // send the CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND message to the nodes and main node
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    send_data_socket(block_verifiers_list.block_verifiers_IP_address[count],SEND_DATA_PORT,data,"sending CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE message to the nodes and main node",0);
  }

  // update the current_round_part and current_round_part_backup_node in the database
  if (memcmp(current_round_part_backup_node,"0",1) == 0)
  {
    memcpy(data,"{\"current_round_part_backup_node\":\"1\"}",26);
  }
  else if (memcmp(current_round_part_backup_node,"1",1) == 0)
  {
    memcpy(data,"{\"current_round_part_backup_node\":\"2\"}",26);
  }
  else if (memcmp(current_round_part_backup_node,"2",1) == 0)
  {
    memcpy(data,"{\"current_round_part_backup_node\":\"3\"}",26);
  }
  else if (memcmp(current_round_part_backup_node,"3",1) == 0)
  {
    memcpy(data,"{\"current_round_part_backup_node\":\"4\"}",26);
  }
  else if (memcmp(current_round_part_backup_node,"4",1) == 0)
  {
    memcpy(data,"{\"current_round_part_backup_node\":\"5\"}",26);
  }
  else if (memcmp(current_round_part_backup_node,"5",1) == 0)
  {
    SEND_ROUND_CHANGE_ERROR("The current_round_part_backup_node has no more backup nodes to select\nFunction: send_round_change\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE");
  }
 
  // set the current_round_part and current_round_part_backup_node in the database
  if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,0) == 0)
  {
    SEND_ROUND_CHANGE_ERROR("Could not update the current_round_part and current_round_part_backup_node in the database\nFunction: send_round_change\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE");
  }

  // send the main nodes public address to the block verifiers
  if (send_data_socket_consensus_node_to_node() == 0)
  {
    SEND_ROUND_CHANGE_ERROR("Could not send the main nodes public address to the block verifiers\nFunction: send_round_change\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE");
  }

  // let the main node know they are the main node and they need to start the part of the round
  if (send_data_socket_consensus_node_to_mainnode() == 0)
  {
    SEND_ROUND_CHANGE_ERROR("Could not send the main nodes public address to the block verifiers\nFunction: send_round_change\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE");
  }

  return 1;

  #undef DATABASE_COLLECTION
  #undef MESSAGE
  #undef SEND_ROUND_CHANGE_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: start_new_part_of_round
Description: Starts the new part of the round
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int start_new_part_of_round()
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count;

  // define macros
  #define DATABASE_COLLECTION "current_round"
  #define MESSAGE "{\"username\":\"xcash\"}"

  #define START_NEW_PART_OF_ROUND_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset(data); \
  return 0;

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // create the message
  memcpy(data,"{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND\",\r\n}",86);

  // sign_data
  if (sign_data(data,0) == 0)
  { 
    START_NEW_PART_OF_ROUND_ERROR("Could not sign_data\nFunction: start_new_part_of_round\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND");
  }

  // send the CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND message to the nodes and main node
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    send_data_socket(block_verifiers_list.block_verifiers_IP_address[count],SEND_DATA_PORT,data,"sending CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND message to the nodes and main node",0);
  }

  // read the current_round_part and current_round_part_backup_node from the database
  memset(current_round_part,0,strnlen(current_round_part,BUFFER_SIZE));
  memset(current_round_part_backup_node,0,strnlen(current_round_part_backup_node,BUFFER_SIZE));
  if (read_document_field_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,"current_round_part",current_round_part,0) == 0 || read_document_field_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,"current_round_part_backup_node",current_round_part_backup_node,0) == 0)
  {
     START_NEW_PART_OF_ROUND_ERROR("Could not read the current_round_part or the current_round_part_backup_node from the database\nFunction: start_new_part_of_round\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND");
  }

  // update the current_round_part and current_round_part_backup_node in the database
  if (memcmp(current_round_part,"1",1) == 0)
  {
    memcpy(data,"{\"current_round_part\":\"2\"}",26);
  }
  else if (memcmp(current_round_part,"2",1) == 0)
  {
    memcpy(data,"{\"current_round_part\":\"3\"}",26);
  }
  else if (memcmp(current_round_part,"3",1) == 0)
  {
    memcpy(data,"{\"current_round_part\":\"4\"}",26);
  }
  else if (memcmp(current_round_part,"4",1) == 0)
  {
    memcpy(data,"{\"current_round_part\":\"1\"}",26);
  }

  // set the current_round_part and current_round_part_backup_node in the database
  if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,0) == 0 || update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,"{\"current_round_part_backup_node\":\"0\"}",0) == 0)
  {
    START_NEW_PART_OF_ROUND_ERROR("Could not update the current_round_part and current_round_part_backup_node in the database\nFunction: start_new_part_of_round\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND");
  }

  // set the current_round_part and current_round_part_backup_node in the database
  if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,data,0) == 0)
  {
    START_NEW_PART_OF_ROUND_ERROR("Could not update the current_round_part and current_round_part_backup_node in the database\nFunction: start_new_part_of_round\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND");
  }

  // send the main nodes public address to the block verifiers
  if (send_data_socket_consensus_node_to_node() == 0)
  {
    START_NEW_PART_OF_ROUND_ERROR("Could not send the main nodes public address to the block verifiers\nFunction: start_new_part_of_round\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND");
  }

  // let the main node know they are the main node and they need to start the part of the round
  if (send_data_socket_consensus_node_to_mainnode() == 0)
  {
    START_NEW_PART_OF_ROUND_ERROR("Could not send the main nodes public address to the block verifiers\nFunction: start_new_part_of_round\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND");
  }

  return 1;

  #undef DATABASE_COLLECTION
  #undef MESSAGE
  #undef START_NEW_PART_OF_ROUND_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: start_next_round
Description: Starts the new part of the round
Parameters:
   SETTINGS - 1 to run the consensus_node_create_new_block to start the next round, otherwise just send the messages to start the next round
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int start_next_round(const int SETTINGS)
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count;

  // define macros
  #define DATABASE_COLLECTION "current_round"
  #define MESSAGE "{\"username\":\"xcash\"}"

  #define START_NEXT_ROUND_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset(data); \
  return 0;

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // create the message
  memcpy(data,"{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND\",\r\n}",79);

  // sign_data
  if (sign_data(data,0) == 0)
  { 
    START_NEXT_ROUND_ERROR("Could not sign_data\nFunction: start_next_round\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND");
  }

  // send the CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND message to the nodes and main node
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    send_data_socket(block_verifiers_list.block_verifiers_IP_address[count],SEND_DATA_PORT,data,"sending CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND message to the nodes and main node",0);
  }
 
  // set the current_round_part and current_round_part_backup_node in the database
  if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,"{\"current_round_part\":\"0\"}",0) == 0 || update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,"{\"current_round_part_backup_node\":\"0\"}",0) == 0)
  {
    START_NEXT_ROUND_ERROR("Could not update the current_round_part and current_round_part_backup_node in the database\nFunction: start_next_round\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND");
  }

  // Add the block to the network
  if (SETTINGS == 1)
  {
    consensus_node_create_new_block();
  }
  else
  {
    create_new_block();
  }

  return 1;

  #undef DATABASE_COLLECTION
  #undef MESSAGE
  #undef START_NEXT_ROUND_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: update_block_producer_eligibility
Description: Sets the update_block_producer_eligibility field to false for all block verifiers that voted for the invalid vote
Parameters:
   SETTINGS - 0 to set all block verifiers that voted for the mainnode_timeout to false, 1 to set all block verifiers that voted for the vote_next_round_false to false, 2 to set all block verifiers that voted for the vote_next_round_true to false.
-----------------------------------------------------------------------------------------------------------
*/

void update_block_producer_eligibility(const int SETTINGS)
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count;
  size_t data_length;

  // define macros
  #define DATABASE_COLLECTION "delegates"

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  if (SETTINGS == 0)
  {
    // set all block verifiers that voted for the mainnode_timeout to false
    for (count = 0; count < mainnode_timeout.vote_round_change_timeout; count++)
    {
      // create the message
      data_length = strnlen(mainnode_timeout.block_verifiers_public_address[count],BUFFER_SIZE);
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"public_address\":\"",19);
      memcpy(data+19,mainnode_timeout.block_verifiers_public_address[count],data_length);
      memcpy(data+19+data_length,"\"}",2);
      update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,data,"{\"block_producer_eligibility\":\"false\"}",0);      
    }
  }
  else if (SETTINGS == 1)
  {
    // set all block verifiers that voted for the vote_next_round_false to false
    for (count = 0; count < node_to_node_vote.vote_next_round_false; count++)
    {
      // create the message
      data_length = strnlen(node_to_node_vote.block_verifiers_public_address_vote_next_round_false[count],BUFFER_SIZE);
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"public_address\":\"",19);
      memcpy(data+19,node_to_node_vote.block_verifiers_public_address_vote_next_round_false[count],data_length);
      memcpy(data+19+data_length,"\"}",2);
      update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,data,"{\"block_producer_eligibility\":\"false\"}",0);      
    }
  }
  else if (SETTINGS == 2)
  {
    // set all block verifiers that voted for the vote_next_round_true to false
    for (count = 0; count < node_to_node_vote.vote_next_round_true; count++)
    {
      // create the message
      data_length = strnlen(node_to_node_vote.block_verifiers_public_address_vote_next_round_true[count],BUFFER_SIZE);
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"public_address\":\"",19);
      memcpy(data+19,node_to_node_vote.block_verifiers_public_address_vote_next_round_true[count],data_length);
      memcpy(data+19+data_length,"\"}",2);
      update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,data,"{\"block_producer_eligibility\":\"false\"}",0);      
    }
  }

  return;

  #undef DATABASE_COLLECTION
}



/*
-----------------------------------------------------------------------------------------------------------
Name: create_new_block
Description: Add the block that the block producer created to the network
Return: 1 if successfull, otherwise 0.
-----------------------------------------------------------------------------------------------------------
*/

int create_new_block()
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data2 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* message = (char*)calloc(BUFFER_SIZE,sizeof(char));
  time_t current_date_and_time;
  struct tm* current_UTC_date_and_time;  
  size_t count;
  size_t count2;
  size_t counter;
  size_t data_length;

  // threads
  pthread_t thread_id;

  // define macros
  #define DATABASE_COLLECTION "current_round"
  #define MESSAGE "{\"username\":\"xcash\"}"

  #define pointer_reset_all \
  free(data); \
  data = NULL; \
  free(data2); \
  data2 = NULL; \
  free(message); \
  message = NULL;

  #define CREATE_NEW_BLOCK_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset_all; \
  return 0;

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL || data2 == NULL || message == NULL)
  {
    if (data != NULL)
    {
      pointer_reset(data);
    }
    if (data2 != NULL)
    {
      pointer_reset(data2);
    }
    if (message != NULL)
    {
      pointer_reset(message);
    }
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // reset the variables
  memset(data,0,strnlen(data,BUFFER_SIZE));
  memset(data2,0,strnlen(data2,BUFFER_SIZE));
  memset(message,0,strnlen(message,BUFFER_SIZE));

  // convert the network_block_string to blockchain_data
  if (network_block_string_to_blockchain_data(VRF_data.block_blob) == 0)
  {
    CREATE_NEW_BLOCK_ERROR("Could not convert the network_block_string to blockchain_data\nFunction: create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK");
  }

  // add the VRF_data struct to the blockchain_data struct


  // change the nonce to the CONSENSUS_NODE_NETWORK_BLOCK_NONCE
  memset(blockchain_data.nonce_data,0,strnlen(blockchain_data.nonce_data,9));
  memcpy(blockchain_data.nonce_data,CONSENSUS_NODE_NETWORK_BLOCK_NONCE,8);

  // convert the blockchain_data to a network_block_string
  memset(data,0,strnlen(data,BUFFER_SIZE));
  if (blockchain_data_to_network_block_string(data) == 0)
  {
    CREATE_NEW_BLOCK_ERROR("Could not convert the blockchain_data to a network_block_string\nFunction: create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK");
  }

  // create the message
  data_length = strnlen(data,BUFFER_SIZE);
  memcpy(message,"{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK\",\r\n \"block_blob\": \"",116);
  memcpy(message+116,data,data_length);
  memcpy(message+116+data_length,"\",\r\n}",5);

  // sign_data
  if (sign_data(message,0) == 0)
  { 
    CREATE_NEW_BLOCK_ERROR("Could not sign_data\nFunction: create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK");
  }

  // add the block_validation_node_signature_data_length to the blockchain_data
  blockchain_data.blockchain_reserve_bytes.block_validation_node_signature_data_length = 196;

  // send the network_block_string to the block validation nodes
  memset(data,0,strnlen(data,BUFFER_SIZE));
  for (count = 0; count < BLOCK_VALIDATION_NODES_AMOUNT; count++)
  {
    if (send_and_receive_data_socket(data,block_validation_nodes_list.block_validation_nodes_IP_address[count],SEND_DATA_PORT,message,TOTAL_CONNECTION_TIME_SETTINGS,"sending the network_block_string to the block validation nodes",0) == 1)
    {
      // convert the block validation signature to hexadecimal
      memset(data2,0,strnlen(data2,BUFFER_SIZE));
      for (count2 = 0, counter = 0; count2 < XCASH_SIGN_DATA_LENGTH; count2++, counter += 2)
      {
        sprintf(data2+counter,"%02x",data[count2] & 0xFF);
      }

      // add the block validation signature to the blockchain_data
      memcpy(blockchain_data.blockchain_reserve_bytes.block_validation_node_signature_data[count],data2,196);
      memcpy(blockchain_data.blockchain_reserve_bytes.block_validation_node_signature[count],data,XCASH_SIGN_DATA_LENGTH);
    }
  }

  // verify the blockchain_data
  if (verify_network_block_data(1) == 0)
  {
    CREATE_NEW_BLOCK_ERROR("Could not verify the blockchain_data\nFunction: create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK");
  }

  // convert the blockchain_data to a network_block_string
  memset(data,0,strnlen(data,BUFFER_SIZE));
  if (blockchain_data_to_network_block_string(data) == 0)
  {
    CREATE_NEW_BLOCK_ERROR("Could not convert the blockchain_data to a network_block_string\nFunction: create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK");
  }

  // wait until the NETWORK_BLOCK_TIME to submit the block to the network
  time(&current_date_and_time);
  current_UTC_date_and_time = gmtime(&current_date_and_time);
  while(current_UTC_date_and_time->tm_min % NETWORK_BLOCK_TIME != 0 && current_UTC_date_and_time->tm_sec == 0)
  {
    // wait for 100 milliseconds this way blocks are always submitted towards the begining of a minute for a constant block time
    usleep(100000);
  }

  // add the network block
  if (submit_block_template(data,0) == 0)
  {
    CREATE_NEW_BLOCK_ERROR("Could not submit the block to the network\nFunction: create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK");
  }

  // add the round statistics to the database
  add_round_statistics();

  // add the block verifier statistics to the database
  add_block_verifiers_round_statistics();

  // check if it should wait if the update_block_verifiers_timer is running
  time(&current_date_and_time);
  current_UTC_date_and_time = gmtime(&current_date_and_time);
  if (current_UTC_date_and_time->tm_hour % 2 == 0 && current_UTC_date_and_time->tm_min == 0)
  {  
    sleep(UPDATE_BLOCK_VERIFIERS_TIME);
  }



  // set the current_round_part and current_round_part_backup_node in the database
  if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,"{\"current_round_part\":\"0\"}",0) == 0 || update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,"{\"current_round_part_backup_node\":\"0\"}",0) == 0)
  {
    CREATE_NEW_BLOCK_ERROR("Could not update the current_round_part and current_round_part_backup_node in the database\nFunction: create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK");
  }

  // calculate the new main nodes roles from the previous network block
  if (calculate_main_nodes_role() == 0)
  {
    CREATE_NEW_BLOCK_ERROR("Could not calculate main nodes role\nFunction: create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK");
    // add another block to the network since the next round could not be started
    consensus_node_create_new_block();
  }

  start_current_round_part:

  // calculate the current_round_part and current_round_part_backup_node 
  if (mainode_consensus() == 0)
  {
    CREATE_NEW_BLOCK_ERROR("Could not get the current_round_part and current_round_part_backup_node\nFunction: create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK");
    // add another block to the network since the next round could not be started
    consensus_node_create_new_block();
  }

  // send the main nodes public address to the block verifiers
  if (send_data_socket_consensus_node_to_node() == 0)
  {
    CREATE_NEW_BLOCK_ERROR("Could not send the main nodes public address to the block verifiers\nFunction: create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK");
    // add another block to the network since the next round could not be started
    consensus_node_create_new_block();
  }

  // let the main node know they are the main node and they need to start the part of the round
  if (send_data_socket_consensus_node_to_mainnode() == 0)
  {
    CREATE_NEW_BLOCK_ERROR("Could not send the main nodes public address to the block verifiers\nFunction: create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK");
    // add another block to the network since the next round could not be started
    goto start_current_round_part;
  }

  // start the receive_votes_from_nodes_timeout
  if (pthread_create(&thread_id, NULL, &receive_votes_from_nodes_timeout_thread, NULL) != 0)
  {
    CREATE_NEW_BLOCK_ERROR("Could not start the receive_votes_from_nodes_timeout\nFunction: create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK");
    // add another block to the network since the next round could not be started
    goto start_current_round_part;
  }
  // set the thread to detach once completed, since we do not need to use anything it will return
  if (pthread_detach(thread_id) != 0)
  {
    CREATE_NEW_BLOCK_ERROR("Could not start the receive_votes_from_nodes_timeout\nFunction: create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK");
    // add another block to the network since the next round could not be started
    goto start_current_round_part;
  }

  // set the server message
  memset(server_message,0,strnlen(server_message,BUFFER_SIZE));
  memcpy(server_message,"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE|NODES_TO_CONSENSUS_NODE_VOTE_RESULTS",98);

  return 1;

  #undef DATABASE_COLLECTION
  #undef MESSAGE
  #undef pointer_reset_all
  #undef CREATE_NEW_BLOCK_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: add_round_statistics
Description: Adds the round statistics to the database after adding the block to the network
-----------------------------------------------------------------------------------------------------------
*/

int add_round_statistics()
{
  // Constants
  const bson_t* current_document;
  
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data2 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data3 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* settings = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count;
  size_t count2;
  size_t counter;
  double total;
  double total2;
  double total3;
  mongoc_collection_t* collection;
  mongoc_cursor_t* document_settings;
  bson_error_t error;
  bson_t* document = NULL;  
  char* message;
  char* message_copy1;
  char* message_copy2;

  // define macros
  #define MESSAGE "{\"username\":\"xcash\"}"
  #define pointer_reset_all \
  free(data); \
  data = NULL; \
  free(data2); \
  data2 = NULL; \
  free(data3); \
  data3 = NULL; \
  free(settings); \
  settings = NULL; 

  #define ADD_ROUND_STATISTICS_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset(data); \
  return 0;

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

  // calculate the most_total_rounds_delegate_name and most_total_rounds
  count = 0;
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
    count2 = 0;

    message = bson_as_canonical_extended_json(current_document, NULL);
    memcpy(data,message,strnlen(message,BUFFER_SIZE));
    bson_free(message);

    // get the block_verifier_total_rounds
    memcpy(data2,", \"",3);
    memcpy(data2+3,"block_verifier_total_rounds",27);
    memcpy(data2+30,"\" : \"",5);

    message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
    message_copy2 = strstr(message_copy1,"\"");
    memcpy(data3,message_copy1,message_copy2 - message_copy1);
    sscanf(data3, "%zu", &count2);

    if (count2 > count)
    {
      count = count2;
      // get the delegate_name
      memcpy(data2,", \"",3);
      memcpy(data2+3,"delegate_name",13);
      memcpy(data2+16,"\" : \"",5);

      message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
      message_copy2 = strstr(message_copy1,"\"");
      memcpy(data3,message_copy1,message_copy2 - message_copy1);
      memset(settings,0,strnlen(settings,BUFFER_SIZE));
      memcpy(settings,data3,strnlen(data3,BUFFER_SIZE));
    }
  }

  // create the message
  memset(data,0,strnlen(data,BUFFER_SIZE));
  memcpy(data,"{\"most_total_rounds_delegate_name\":\"",36);
  memcpy(data+36,settings,strnlen(settings,BUFFER_SIZE));
  memcpy(data+36+strnlen(settings,BUFFER_SIZE),"\"}",2);

  memset(data2,0,strnlen(data2,BUFFER_SIZE));
  memcpy(data2,"{\"most_total_rounds\":\"",25);
  sprintf(data2+25,"%zu",count);
  memcpy(data2+strnlen(data2,BUFFER_SIZE),"\"}",2);

  // update the database
  if (update_document_from_collection(DATABASE_NAME,"delegates",MESSAGE,data,0) == 0 || update_document_from_collection(DATABASE_NAME,"delegates",MESSAGE,data2,0) == 0)
  {
    ADD_ROUND_STATISTICS_ERROR("Could not update a delegates most_total_rounds_delegate_name or most_total_rounds in the database\nFunction: add_round_statistics");
  }

  // calculate the best_block_verifier_online_percentage_delegate_name and best_block_verifier_online_percentage

  total = 0;
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
    count2 = 0;

    message = bson_as_canonical_extended_json(current_document, NULL);
    memcpy(data,message,strnlen(message,BUFFER_SIZE));
    bson_free(message);

    // get the block_verifier_total_rounds
    memcpy(data2,", \"",3);
    memcpy(data2+3,"block_verifier_total_rounds",27);
    memcpy(data2+30,"\" : \"",5);

    message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
    message_copy2 = strstr(message_copy1,"\"");
    memcpy(data3,message_copy1,message_copy2 - message_copy1);
    sscanf(data3, "%lf", &total2);

    // get the block_verifier_online_total_rounds
    memset(data2,0,strnlen(data2,BUFFER_SIZE));
    memset(data3,0,strnlen(data3,BUFFER_SIZE));
    memcpy(data2,", \"",3);
    memcpy(data2+3,"block_verifier_online_total_rounds",34);
    memcpy(data2+34,"\" : \"",5);

    message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
    message_copy2 = strstr(message_copy1,"\"");
    memcpy(data3,message_copy1,message_copy2 - message_copy1);
    sscanf(data3, "%lf", &total3);

    if (total3 / total2 > total)
    {
      total = total3 / total2;
      // get the delegate_name
      memcpy(data2,", \"",3);
      memcpy(data2+3,"delegate_name",13);
      memcpy(data2+16,"\" : \"",5);

      message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
      message_copy2 = strstr(message_copy1,"\"");
      memcpy(data3,message_copy1,message_copy2 - message_copy1);
      memset(settings,0,strnlen(settings,BUFFER_SIZE));
      memcpy(settings,data3,strnlen(data3,BUFFER_SIZE));
    }
  }

  // create the message
  memset(data,0,strnlen(data,BUFFER_SIZE));
  memcpy(data,"{\"most_block_producer_total_rounds_delegate_name\":\"",51);
  memcpy(data+51,settings,strnlen(settings,BUFFER_SIZE));
  memcpy(data+51+strnlen(settings,BUFFER_SIZE),"\"}",2);

  memset(data2,0,strnlen(data2,BUFFER_SIZE));
  memcpy(data2,"{\"best_block_verifier_online_percentage\":\"",45);
  sprintf(data2+45,"%lf",total);
  memcpy(data2+strnlen(data2,BUFFER_SIZE),"\"}",2);

  // update the database
  if (update_document_from_collection(DATABASE_NAME,"delegates",MESSAGE,data,0) == 0 || update_document_from_collection(DATABASE_NAME,"delegates",MESSAGE,data2,0) == 0)
  {
    ADD_ROUND_STATISTICS_ERROR("Could not update a delegates most_block_producer_total_rounds_delegate_name or best_block_verifier_online_percentage in the database\nFunction: add_round_statistics");
  }

  // calculate the most_block_producer_total_rounds_delegate_name and most_block_producer_total_rounds
  count = 0;
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
    count2 = 0;

    message = bson_as_canonical_extended_json(current_document, NULL);
    memcpy(data,message,strnlen(message,BUFFER_SIZE));
    bson_free(message);

    // get the block_verifier_total_rounds
    memcpy(data2,", \"",3);
    memcpy(data2+3,"block_producer_total_rounds",27);
    memcpy(data2+30,"\" : \"",5);

    message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
    message_copy2 = strstr(message_copy1,"\"");
    memcpy(data3,message_copy1,message_copy2 - message_copy1);
    sscanf(data3, "%zu", &count2);

    if (count2 > count)
    {
      count = count2;
      // get the delegate_name
      memcpy(data2,", \"",3);
      memcpy(data2+3,"delegate_name",13);
      memcpy(data2+16,"\" : \"",5);

      message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
      message_copy2 = strstr(message_copy1,"\"");
      memcpy(data3,message_copy1,message_copy2 - message_copy1);
      memset(settings,0,strnlen(settings,BUFFER_SIZE));
      memcpy(settings,data3,strnlen(data3,BUFFER_SIZE));
    }
  }

  // create the message
  memset(data,0,strnlen(data,BUFFER_SIZE));
  memcpy(data,"{\"most_block_producer_total_rounds_delegate_name\":\"",51);
  memcpy(data+51,settings,strnlen(settings,BUFFER_SIZE));
  memcpy(data+51+strnlen(settings,BUFFER_SIZE),"\"}",2);

  memset(data2,0,strnlen(data2,BUFFER_SIZE));
  memcpy(data2,"{\"most_block_producer_total_rounds\":\"",40);
  sprintf(data2+40,"%zu",count);
  memcpy(data2+strnlen(data2,BUFFER_SIZE),"\"}",2);

  // update the database
  if (update_document_from_collection(DATABASE_NAME,"delegates",MESSAGE,data,0) == 0 || update_document_from_collection(DATABASE_NAME,"delegates",MESSAGE,data2,0) == 0)
  {
    ADD_ROUND_STATISTICS_ERROR("Could not update a delegates most_block_producer_total_rounds_delegate_name or most_block_producer_total_rounds in the database\nFunction: add_round_statistics");
  }

  // calculate the most_VRF_node_public_and_private_key_total_rounds_delegate_name and most_VRF_node_public_and_private_key_total_rounds
  count = 0;
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
    count2 = 0;

    message = bson_as_canonical_extended_json(current_document, NULL);
    memcpy(data,message,strnlen(message,BUFFER_SIZE));
    bson_free(message);

    // get the block_verifier_total_rounds
    memcpy(data2,", \"",3);
    memcpy(data2+3,"VRF_node_public_and_private_key_total_rounds",44);
    memcpy(data2+47,"\" : \"",5);

    message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
    message_copy2 = strstr(message_copy1,"\"");
    memcpy(data3,message_copy1,message_copy2 - message_copy1);
    sscanf(data3, "%zu", &count2);

    if (count2 > count)
    {
      count = count2;
      // get the delegate_name
      memcpy(data2,", \"",3);
      memcpy(data2+3,"delegate_name",13);
      memcpy(data2+16,"\" : \"",5);

      message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
      message_copy2 = strstr(message_copy1,"\"");
      memcpy(data3,message_copy1,message_copy2 - message_copy1);
      memset(settings,0,strnlen(settings,BUFFER_SIZE));
      memcpy(settings,data3,strnlen(data3,BUFFER_SIZE));
    }
  }

  // create the message
  memset(data,0,strnlen(data,BUFFER_SIZE));
  memcpy(data,"{\"most_VRF_node_public_and_private_key_total_rounds_delegate_name\":\"",68);
  memcpy(data+68,settings,strnlen(settings,BUFFER_SIZE));
  memcpy(data+68+strnlen(settings,BUFFER_SIZE),"\"}",2);

  memset(data2,0,strnlen(data2,BUFFER_SIZE));
  memcpy(data2,"{\"most_VRF_node_public_and_private_key_total_rounds\":\"",54);
  sprintf(data2+54,"%zu",count);
  memcpy(data2+strnlen(data2,BUFFER_SIZE),"\"}",2);

  // update the database
  if (update_document_from_collection(DATABASE_NAME,"delegates",MESSAGE,data,0) == 0 || update_document_from_collection(DATABASE_NAME,"delegates",MESSAGE,data2,0) == 0)
  {
    ADD_ROUND_STATISTICS_ERROR("Could not update a delegates most_VRF_node_public_and_private_key_total_rounds_delegate_name or most_VRF_node_random_data_total_rounds in the database\nFunction: add_round_statistics");
  }

  // calculate the most_VRF_node_random_data_total_rounds_delegate_name and most_VRF_node_public_and_private_key_total_rounds
  count = 0;
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
    count2 = 0;

    message = bson_as_canonical_extended_json(current_document, NULL);
    memcpy(data,message,strnlen(message,BUFFER_SIZE));
    bson_free(message);

    // get the block_verifier_total_rounds
    memcpy(data2,", \"",3);
    memcpy(data2+3,"VRF_node_random_data_total_rounds",33);
    memcpy(data2+36,"\" : \"",5);

    message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
    message_copy2 = strstr(message_copy1,"\"");
    memcpy(data3,message_copy1,message_copy2 - message_copy1);
    sscanf(data3, "%zu", &count2);

    if (count2 > count)
    {
      count = count2;
      // get the delegate_name
      memcpy(data2,", \"",3);
      memcpy(data2+3,"delegate_name",13);
      memcpy(data2+16,"\" : \"",5);

      message_copy1 = strstr(data,data2) + strnlen(data2,BUFFER_SIZE);
      message_copy2 = strstr(message_copy1,"\"");
      memcpy(data3,message_copy1,message_copy2 - message_copy1);
      memset(settings,0,strnlen(settings,BUFFER_SIZE));
      memcpy(settings,data3,strnlen(data3,BUFFER_SIZE));
    }
  }

  // create the message
  memset(data,0,strnlen(data,BUFFER_SIZE));
  memcpy(data,"{\"most_VRF_node_random_data_total_rounds_delegate_name\":\"",57);
  memcpy(data+57,settings,strnlen(settings,BUFFER_SIZE));
  memcpy(data+57+strnlen(settings,BUFFER_SIZE),"\"}",2);

  memset(data2,0,strnlen(data2,BUFFER_SIZE));
  memcpy(data2,"{\"most_VRF_node_random_data_total_rounds\":\"",46);
  sprintf(data2+46,"%zu",count);
  memcpy(data2+strnlen(data2,BUFFER_SIZE),"\"}",2);

  // update the database
  if (update_document_from_collection(DATABASE_NAME,"delegates",MESSAGE,data,0) == 0 || update_document_from_collection(DATABASE_NAME,"delegates",MESSAGE,data2,0) == 0)
  {
    ADD_ROUND_STATISTICS_ERROR("Could not update a delegates most_VRF_node_random_data_total_rounds_delegate_name or most_VRF_node_random_data_total_rounds in the database\nFunction: add_round_statistics");
  }

  return 1;

  #undef MESSAGE
  #undef pointer_reset_all
  #undef ADD_ROUND_STATISTICS_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: add_delegate_round_statistics
Description: Adds the block verifier statistics to the database after adding the block to the network
-----------------------------------------------------------------------------------------------------------
*/

void add_block_verifiers_round_statistics()
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data2 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* message = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* VRF_node_public_and_private_key_public_address = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* VRF_node_random_data_public_address = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* block_producer_public_address = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* current_block_height = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count;
  size_t count2;
  size_t number;

  // define macros
  #define pointer_reset_all \
  free(data); \
  data = NULL; \
  free(data2); \
  data2 = NULL; \
  free(message); \
  message = NULL; \
  free(VRF_node_public_and_private_key_public_address); \
  VRF_node_public_and_private_key_public_address = NULL; \
  free(VRF_node_random_data_public_address); \
  VRF_node_random_data_public_address = NULL; \
  free(block_producer_public_address); \
  block_producer_public_address = NULL; \
  free(current_block_height); \
  current_block_height = NULL;
  
  #define ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset_all; \
  return;

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL || data2 == NULL || message == NULL || VRF_node_public_and_private_key_public_address == NULL || VRF_node_random_data_public_address == NULL || block_producer_public_address == NULL || current_block_height == NULL)
  {
    if (data != NULL)
    {
      pointer_reset(data);
    }
    if (data2 != NULL)
    {
      pointer_reset(data2);
    }
    if (message != NULL)
    {
      pointer_reset(message);
    }
    if (VRF_node_public_and_private_key_public_address != NULL)
    {
      pointer_reset(VRF_node_public_and_private_key_public_address);
    }
    if (VRF_node_random_data_public_address != NULL)
    {
      pointer_reset(VRF_node_random_data_public_address);
    }
    if (block_producer_public_address != NULL)
    {
      pointer_reset(block_producer_public_address);
    }
    if (current_block_height != NULL)
    {
      pointer_reset(current_block_height);
    }
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // get all of the main nodes public address
  if (read_document_field_from_collection(DATABASE_NAME,"current_round","{\"username\":\"xcash\"}","vrf_node_public_and_private_key_public_address",VRF_node_public_and_private_key_public_address,0) == 0 || read_document_field_from_collection(DATABASE_NAME,"current_round","{\"username\":\"xcash\"}","vrf_node_random_data_public_address",VRF_node_random_data_public_address,0) == 0 || read_document_field_from_collection(DATABASE_NAME,"current_round","{\"username\":\"xcash\"}","block_producer_public_address",block_producer_public_address,0) == 0)
  {
    ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not read the main nodes public address from the database\nFunction: add_block_verifiers_round_statistics");
  }

  // get the current block height
  if (get_current_block_height(current_block_height,0) == 0)
  {
    ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not get the current block height\nFunction: add_block_verifiers_round_statistics");
  }

  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    // create the message
    memset(message,0,strnlen(message,BUFFER_SIZE));
    memcpy(message,"{\"public_address\":\"",19);
    memcpy(message+19,block_verifiers_list.block_verifiers_public_address[count],XCASH_WALLET_LENGTH);
    memcpy(message+19+XCASH_WALLET_LENGTH,"\"}",2);

    // add one to the block_verifier_total_rounds for every block verifier
    memset(data,0,strnlen(data,BUFFER_SIZE));
    if (read_document_field_from_collection(DATABASE_NAME,"delegates",message,"block_verifier_total_rounds",data,0) == 0)
    {
      ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not read the block_verifier_total_rounds from the database\nFunction: add_block_verifiers_round_statistics");
    }
    count2 = strnlen(data,BUFFER_SIZE);
    sscanf(data, "%zu", &number);
    number++;
    memset(data,0,strnlen(data,BUFFER_SIZE));
    memcpy(data,"{\"block_verifier_total_rounds\":\"",32);
    sprintf(data+32,"%zu",number); 
    memcpy(data+32+count2,"\"}",2);
    if (update_document_from_collection(DATABASE_NAME,"delegates",message,data,0) == 0)
    {
      ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not update the block_verifier_total_rounds in the database\nFunction: add_block_verifiers_round_statistics");
    }

    // add one to the block_verifier_online_total_rounds for every block verifier that is currently online
    if (send_data_socket(block_verifiers_list.block_verifiers_IP_address[count],SEND_DATA_PORT,"","checking if the block verifier is online",0) == 1)
    {
      memset(data,0,strnlen(data,BUFFER_SIZE));
      if (read_document_field_from_collection(DATABASE_NAME,"delegates",message,"block_verifier_online_total_rounds",data,0) == 0)
      {
        ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not read the block_verifier_online_total_rounds from the database\nFunction: add_block_verifiers_round_statistics");
      }
      count2 = strnlen(data,BUFFER_SIZE);
      sscanf(data, "%zu", &number);
      number++;
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"block_verifier_online_total_rounds\":\"",39);
      sprintf(data+39,"%zu",number); 
      memcpy(data+39+count2,"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,"delegates",message,data,0) == 0)
      {
        ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not update the block_verifier_online_total_rounds in the database\nFunction: add_block_verifiers_round_statistics");
      }
    }

    // add one to the VRF_node_public_and_private_key_total_rounds and the current block height to the VRF_node_public_and_private_key_block_heights if the public address is the block producer
    if (memcmp(block_verifiers_list.block_verifiers_public_address[count],VRF_node_public_and_private_key_public_address,XCASH_WALLET_LENGTH) == 0)
    {
      memset(data,0,strnlen(data,BUFFER_SIZE));
      if (read_document_field_from_collection(DATABASE_NAME,"delegates",message,"VRF_node_public_and_private_key_total_rounds",data,0) == 0)
      {
        ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not read the VRF_node_public_and_private_key_total_rounds from the database\nFunction: add_block_verifiers_round_statistics");
      }
      count2 = strnlen(data,BUFFER_SIZE);
      sscanf(data, "%zu", &number);
      number++;
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"VRF_node_public_and_private_key_total_rounds\":\"",49);
      sprintf(data+49,"%zu",number); 
      memcpy(data+49+count2,"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,"delegates",message,data,0) == 0)
      {
        ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not update the VRF_node_public_and_private_key_total_rounds in the database\nFunction: add_block_verifiers_round_statistics");
      }

      memset(data,0,strnlen(data,BUFFER_SIZE));
      if (read_document_field_from_collection(DATABASE_NAME,"delegates",message,"VRF_node_public_and_private_key_block_heights",data,0) == 0)
      {
        ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not read the VRF_node_public_and_private_key_block_heights from the database\nFunction: add_block_verifiers_round_statistics");
      }      
      memcpy(data,",",1);
      memcpy(data+1,current_block_height,strnlen(current_block_height,BUFFER_SIZE));
      memset(data2,0,strnlen(data2,BUFFER_SIZE));
      memcpy(data2,"{\"VRF_node_public_and_private_key_block_heights\":\"",50);
      memcpy(data2+50,data,strnlen(data,BUFFER_SIZE));
      memcpy(data2+50+strnlen(data,BUFFER_SIZE),"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,"delegates",message,data2,0) == 0)
      {
        ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not update the VRF_node_public_and_private_key_block_heights in the database\nFunction: add_block_verifiers_round_statistics");
      }
    }

    // add one to the VRF_node_random_data_total_rounds and the current block height to the block_producer_block_heights if the public address is the block producer
    if (memcmp(block_verifiers_list.block_verifiers_public_address[count],VRF_node_random_data_public_address,XCASH_WALLET_LENGTH) == 0)
    {
      memset(data,0,strnlen(data,BUFFER_SIZE));
      if (read_document_field_from_collection(DATABASE_NAME,"delegates",message,"VRF_node_random_data_total_rounds",data,0) == 0)
      {
        ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not read the VRF_node_random_data_total_rounds from the database\nFunction: add_block_verifiers_round_statistics");
      }
      count2 = strnlen(data,BUFFER_SIZE);
      sscanf(data, "%zu", &number);
      number++;
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"VRF_node_random_data_total_rounds\":\"",38);
      sprintf(data+38,"%zu",number); 
      memcpy(data+38+count2,"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,"delegates",message,data,0) == 0)
      {
        ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not update the VRF_node_random_data_total_rounds in the database\nFunction: add_block_verifiers_round_statistics");
      }

      memset(data,0,strnlen(data,BUFFER_SIZE));
      if (read_document_field_from_collection(DATABASE_NAME,"delegates",message,"VRF_node_random_data_block_heights",data,0) == 0)
      {
        ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not read the VRF_node_random_data_block_heights from the database\nFunction: add_block_verifiers_round_statistics");
      }      
      memcpy(data,",",1);
      memcpy(data+1,current_block_height,strnlen(current_block_height,BUFFER_SIZE));
      memset(data2,0,strnlen(data2,BUFFER_SIZE));
      memcpy(data2,"{\"VRF_node_random_data_block_heights\":\"",39);
      memcpy(data2+39,data,strnlen(data,BUFFER_SIZE));
      memcpy(data2+39+strnlen(data,BUFFER_SIZE),"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,"delegates",message,data2,0) == 0)
      {
        ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not update the VRF_node_random_data_block_heights in the database\nFunction: add_block_verifiers_round_statistics");
      }
    }

    // add one to the block_producer_total_rounds and the current block height to the block_producer_block_heights if the public address is the block producer
    if (memcmp(block_verifiers_list.block_verifiers_public_address[count],block_producer_public_address,XCASH_WALLET_LENGTH) == 0)
    {
      memset(data,0,strnlen(data,BUFFER_SIZE));
      if (read_document_field_from_collection(DATABASE_NAME,"delegates",message,"block_producer_total_rounds",data,0) == 0)
      {
        ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not read the block_producer_total_rounds from the database\nFunction: add_block_verifiers_round_statistics");
      }
      count2 = strnlen(data,BUFFER_SIZE);
      sscanf(data, "%zu", &number);
      number++;
      memset(data,0,strnlen(data,BUFFER_SIZE));
      memcpy(data,"{\"block_producer_total_rounds\":\"",39);
      sprintf(data+39,"%zu",number); 
      memcpy(data+39+count2,"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,"delegates",message,data,0) == 0)
      {
        ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not update the block_producer_total_rounds in the database\nFunction: add_block_verifiers_round_statistics");
      }

      memset(data,0,strnlen(data,BUFFER_SIZE));
      if (read_document_field_from_collection(DATABASE_NAME,"delegates",message,"block_producer_block_heights",data,0) == 0)
      {
        ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not read the block_producer_block_heights from the database\nFunction: add_block_verifiers_round_statistics");
      }      
      memcpy(data,",",1);
      memcpy(data+1,current_block_height,strnlen(current_block_height,BUFFER_SIZE));
      memset(data2,0,strnlen(data2,BUFFER_SIZE));
      memcpy(data2,"{\"block_producer_block_heights\":\"",33);
      memcpy(data2+33,data,strnlen(data,BUFFER_SIZE));
      memcpy(data2+33+strnlen(data,BUFFER_SIZE),"\"}",2);
      if (update_document_from_collection(DATABASE_NAME,"delegates",message,data2,0) == 0)
      {
        ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR("Could not update the block_producer_block_heights in the database\nFunction: add_block_verifiers_round_statistics");
      }
    }
  }

  return;

  #undef pointer_reset_all
  #undef ADD_BLOCK_VERIFIERS_ROUND_STATISTICS_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: send_recalculating_votes_to_nodes_and_main_nodes
Description: sends the CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES message to the nodes and main node
Return: 1 if the consensus node is the current consensus node, otherwise 0.
-----------------------------------------------------------------------------------------------------------
*/

int send_recalculating_votes_to_nodes_and_main_nodes()
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count;

  // define macros
  #define SEND_RECALCULATING_VOTES_TO_NODES_AND_MAIN_NODES_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset(data); \
  return 0;


  // check if the memory needed was allocated on the heap successfully
  if (data == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // create the message
  memcpy(data,"{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES\",\r\n}",88);

  // sign_data
  if (sign_data(data,0) == 0)
  { 
    SEND_RECALCULATING_VOTES_TO_NODES_AND_MAIN_NODES_ERROR("Could not sign_data\nFunction: send_recalculating_votes_to_nodes_and_main_nodes\nSend Message: CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES");
  }

  // send the CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES message to the nodes and main node
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    send_data_socket(block_verifiers_list.block_verifiers_IP_address[count],SEND_DATA_PORT,data,"sending CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES message to the nodes and main node",0);
  }

  return 1;

  #undef SEND_RECALCULATING_VOTES_TO_NODES_AND_MAIN_NODES_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: send_vote_list_to_nodes
Description: sends the CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES message to the nodes and main node
Return: 1 if the consensus node is the current consensus node, otherwise 0.
-----------------------------------------------------------------------------------------------------------
*/

int send_vote_list_to_nodes()
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count;
  size_t counter;

  // define macros
  #define SEND_VOTE_LIST_TO_NODES_ERROR(settings) \
  color_print(settings,"red"); \
  pointer_reset(data); \
  return 0;


  // check if the memory needed was allocated on the heap successfully
  if (data == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // create the message
  memcpy(data,"{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES\",\r\n \"nodes_name_list\": \"{\r\n \\\"",100);
  counter = 100;
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    memcpy(data+counter,"node",4);
    counter += 4;
    sprintf(data+counter,"%zu",count);
    counter = strnlen(data,BUFFER_SIZE);
    memcpy(data+counter,"\\\": \\\"",4);
    counter += 4;
    memcpy(data+counter,block_verifiers_list.block_verifiers_name[count],strnlen(block_verifiers_list.block_verifiers_name[count],BUFFER_SIZE));
    counter += strnlen(block_verifiers_list.block_verifiers_name[count],BUFFER_SIZE);
    memcpy(data+counter,",\r\n \\\"",5);
  }
  memcpy(data+counter-2,"}\",\r\n \"nodes_public_address_list\": \"{\r\n \\\"",42);
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    memcpy(data+counter,"node",4);
    counter += 4;
    sprintf(data+counter,"%zu",count);
    counter = strnlen(data,BUFFER_SIZE);
    memcpy(data+counter,"\\\": \\\"",4);
    counter += 4;
    memcpy(data+counter,block_verifiers_list.block_verifiers_name[count],strnlen(block_verifiers_list.block_verifiers_name[count],BUFFER_SIZE));
    counter += strnlen(block_verifiers_list.block_verifiers_name[count],BUFFER_SIZE);
    memcpy(data+counter,",\r\n \\\"",5);
  }
  memcpy(data+counter-2,"}\",\r\n \"nodes_IP_address_list\": \"{\r\n \\\"",38);
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    memcpy(data+counter,"node",4);
    counter += 4;
    sprintf(data+counter,"%zu",count);
    counter = strnlen(data,BUFFER_SIZE);
    memcpy(data+counter,"\\\": \\\"",4);
    counter += 4;
    memcpy(data+counter,block_verifiers_list.block_verifiers_name[count],strnlen(block_verifiers_list.block_verifiers_name[count],BUFFER_SIZE));
    counter += strnlen(block_verifiers_list.block_verifiers_name[count],BUFFER_SIZE);
    memcpy(data+counter,",\r\n \\\"",5);
  }
  memcpy(data+counter-2,"}\",\r\n}",6);  

  // sign_data
  if (sign_data(data,0) == 0)
  { 
    SEND_VOTE_LIST_TO_NODES_ERROR("Could not sign_data\nFunction: send_vote_list_to_nodes\nSend Message: CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES");
  }

  // send the CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES message to the nodes and main node
  for (count = 0; count < BLOCK_VERIFIERS_AMOUNT; count++)
  {
    send_data_socket(block_verifiers_list.block_verifiers_IP_address[count],SEND_DATA_PORT,data,"sending CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES message to the nodes and main node",0);
  }

  return 1;

  #undef SEND_VOTE_LIST_TO_NODES_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: create_server
Description: Creates the server
Parameters:
   MESSAGE_SETTINGS - 1 to print the messages, otherwise 0. This is used for the testing flag to not print any success or error messages
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int create_server(const int MESSAGE_SETTINGS)
{
  // Constants
  const char* HTTP_HEADERS[] = {"Content-Type: application/json","Accept: application/json"};   
  const int SOCKET_OPTION = 1;  
  const size_t HTTP_HEADERS_LENGTH = sizeof(HTTP_HEADERS)/sizeof(HTTP_HEADERS[0]);

  // Variables
  char buffer[BUFFER_SIZE];
  char buffer2[BUFFER_SIZE];
  char client_address[BUFFER_SIZE];  
  char* string = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  int len;
  int receive_data_result; 
  struct sockaddr_in addr, cl_addr;  
  struct sockaddr_in serv_addr;

  // define macros
  #define SOCKET_FILE_DESCRIPTORS_LENGTH 1

  #define pointer_reset_all \
  free(string); \
  string = NULL;

  #define SERVER_ERROR(settings) \
  close(SOCKET); \
  pointer_reset_all; \
  if (settings == 0) \
  { \
    return 0; \
  } \
  else \
  { \
    _exit(0); \
  }  

  // threads
  pthread_t thread_id;

  // set the main process to ignore if forked processes return a value or not, since the timeout for the total connection time is run on a different thread
  signal(SIGCHLD, SIG_IGN); 

  if (string == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  } 
    
  /* Create the socket  
  AF_INET = IPV4 support
  SOCK_STREAM = TCP protocol
  */
  const int SOCKET = socket(AF_INET, SOCK_STREAM, 0);
  if (SOCKET == -1)
  {
    if (MESSAGE_SETTINGS == 1)
    {
      color_print("Error creating socket","red");
    }    
    pointer_reset_all;
    return 0;
  }

  /* Set the socket options
  SOL_SOCKET = socket level
  SO_REUSEADDR = allows for reuse of the same address, so one can shutdown and restart the program without errros
  SO_REUSEPORT = allows for reuse of the same port, so one can shutdown and restart the program without errros
  */
  if (setsockopt(SOCKET, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &SOCKET_OPTION,sizeof(int)) != 0)
  {
    if (MESSAGE_SETTINGS == 1)
    {
      color_print("Error setting socket options","red"); 
    }
    SERVER_ERROR(0);
  } 
  if (MESSAGE_SETTINGS == 1)
  {
    color_print("Socket created","green");
  }
 
  // convert the port to a string
  sprintf(buffer2,"%d",SEND_DATA_PORT);  
 
  memset(&addr, 0, sizeof(addr));
  /* setup the connection
  AF_INET = IPV4
  INADDR_ANY = connect to 0.0.0.0
  use htons to convert the port from host byte order to network byte order short
  */
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(SEND_DATA_PORT);
 
  // connect to 0.0.0.0
  if (bind(SOCKET, (struct sockaddr *) &addr, sizeof(addr)) != 0)
  {
   if (MESSAGE_SETTINGS == 1)
   {
     memset(string,0,strnlen(string,BUFFER_SIZE));
     memcpy(string,"Error connecting to port ",25);
     memcpy(string+25,buffer2,strnlen(buffer2,BUFFER_SIZE));
     color_print(string,"red"); 
   }
   SERVER_ERROR(0);
  } 
  if (MESSAGE_SETTINGS == 1)
  {
    memset(string,0,strnlen(string,BUFFER_SIZE));
    memcpy(string,"Connected to port ",18);
    memcpy(string+18,buffer2,strnlen(buffer2,BUFFER_SIZE));
    color_print(string,"green");

    printf("Waiting for a connection...\n");
  }

  // set the maximum simultaneous connections
  if (listen(SOCKET, MAXIMUM_CONNECTIONS) != 0)
  {
    if (MESSAGE_SETTINGS == 1)
    {
      color_print("Error creating the server","red"); 
    }
    SERVER_ERROR(0);
  }

  for (;;)
  {
    len = sizeof(cl_addr);
    const int CLIENT_SOCKET = accept(SOCKET, (struct sockaddr *) &cl_addr, (socklen_t*)&len);
    inet_ntop(AF_INET, &(cl_addr.sin_addr), client_address, BUFFER_SIZE);
    if (client_address == NULL)
    {
      if (MESSAGE_SETTINGS == 1)
      {
        color_print("Error accepting connection","red"); 
      }
      continue;
    }
    const size_t CLIENT_ADDRESS_LENGTH = strnlen(client_address,BUFFER_SIZE);
    const size_t BUFFER2_LENGTH = strnlen(buffer2,BUFFER_SIZE);
  
    if (CLIENT_SOCKET == -1)
    {
      if (MESSAGE_SETTINGS == 1)
      {
        memset(string,0,strnlen(string,BUFFER_SIZE));
        memcpy(string,"Error accepting connection from ",32);
        memcpy(string+32,inet_ntoa(cl_addr.sin_addr),CLIENT_ADDRESS_LENGTH);
        memcpy(string+32+CLIENT_ADDRESS_LENGTH," on ",4);
        memcpy(string+36+CLIENT_ADDRESS_LENGTH,buffer2,strnlen(buffer2,BUFFER_SIZE));
        color_print(string,"red"); 
      }
      continue;
    }
    if (MESSAGE_SETTINGS == 1)
    {
      memset(string,0,strnlen(string,BUFFER_SIZE));
      memcpy(string,"Connection accepted from ",25);
      memcpy(string+25,inet_ntoa(cl_addr.sin_addr),CLIENT_ADDRESS_LENGTH);
      memcpy(string+25+CLIENT_ADDRESS_LENGTH," on ",4);
      memcpy(string+29+CLIENT_ADDRESS_LENGTH,buffer2,strnlen(buffer2,BUFFER_SIZE));
      color_print(string,"green"); 
    }

   

    if (fork() == 0)
    {
      // create a struct for the parameters
      struct total_connection_time_thread_parameters parameters = {
        getpid(),
        client_address,
        buffer2,
        0,
        (int)MESSAGE_SETTINGS
      };
          // create a timeout for this connection, since we need to limit the amount of time a client has to send data from once it connected
         if (pthread_create(&thread_id, NULL, &total_connection_time_thread, (void *)&parameters) != 0)
         {
           // close the forked process
           SERVER_ERROR(1);
         }
         // set the thread to dettach once completed, since we do not need to use anything.
         if (pthread_detach(thread_id) != 0)
         {
           // close the forked process
           SERVER_ERROR(1);
         }
      

       // close the main socket, since the socket is now copied to the forked process
       close(SOCKET); 

       for (;;)
       {         
         // receive the data
         memset(buffer, 0, BUFFER_SIZE); 
         receive_data_result = receive_data(CLIENT_SOCKET,buffer,SOCKET_END_STRING,0,TOTAL_CONNECTION_TIME_SETTINGS);
         if (receive_data_result < 2)
         {
           if (MESSAGE_SETTINGS == 1)
           {
             memset(string,0,strnlen(string,BUFFER_SIZE));
             memcpy(string,"Error receiving data from ",26);
             memcpy(string+26,client_address,CLIENT_ADDRESS_LENGTH);
             memcpy(string+26+CLIENT_ADDRESS_LENGTH," on port ",9);
             memcpy(string+35+CLIENT_ADDRESS_LENGTH,buffer2,BUFFER2_LENGTH);
             if (receive_data_result == 1)
             {
               memcpy(string+35+CLIENT_ADDRESS_LENGTH+BUFFER2_LENGTH,", because of a timeout issue",28);
             }
             else if (receive_data_result == 0)
             {
               memcpy(string+35+CLIENT_ADDRESS_LENGTH+BUFFER2_LENGTH,", because of a potential buffer overflow issue",46);
             }
             color_print(string,"red"); 
           }
           // close the forked process, since the client had an error sending data       
           SERVER_ERROR(1);
         }
         else if (receive_data_result == 2)
         {
          // update the parameters, since we have received data from the client
          parameters.data_received = 1;
         }    



         // check if a certain type of message has been received         
         if (strstr(buffer,"\"message_settings\": \"XCASH_PROOF_OF_STAKE_TEST_DATA\"") != NULL && strncmp(server_message,"XCASH_PROOF_OF_STAKE_TEST_DATA",BUFFER_SIZE) == 0)
         {
           // close the forked process when done
           server_received_data_xcash_proof_of_stake_test_data(CLIENT_SOCKET,buffer);
           SERVER_ERROR(1);
         }
         else if (strstr(buffer,"\"message_settings\": \"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS\"") != NULL)
         {
           // close the forked process when done
           server_receive_data_socket_node_to_consensus_node_send_current_consensus_node_IP_address(CLIENT_SOCKET,buffer);
           SERVER_ERROR(1);
         }
         else if (strstr(buffer,"\"message_settings\": \"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST\"") != NULL)
         {
           // close the forked process when done
           server_receive_data_socket_node_to_consensus_node_send_updated_node_list(CLIENT_SOCKET,buffer);
           SERVER_ERROR(1);
         }
         else if (strstr(buffer,"\"message_settings\": \"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE\"") != NULL && strstr(server_message,"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE") != NULL)
         {
           // close the forked process when done
           server_receive_data_socket_main_node_timeout_from_node(buffer);
           SERVER_ERROR(1);
         }
         else if (strstr(buffer,"\"message_settings\": \"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS\"") != NULL && strstr(server_message,"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS") != NULL)
         {
           // close the forked process when done
           server_receive_data_socket_node_to_node_vote(buffer);
           SERVER_ERROR(1);
         }
         else
         {
           printf("Received %s from %s on port %s\r\n",buffer,client_address,buffer2);
           // send the message 
           if (send_data(CLIENT_SOCKET,buffer,1) == 1)
           {
             printf("Sent %s to %s on port %s\r\n",buffer,client_address,buffer2);
           } 
           else
           {
             memset(string,0,strnlen(string,BUFFER_SIZE));
             memcpy(string,"Error sending data to ",22);
             memcpy(string+22,client_address,CLIENT_ADDRESS_LENGTH);
             memcpy(string+22+CLIENT_ADDRESS_LENGTH," on port ",9);
             memcpy(string+31+CLIENT_ADDRESS_LENGTH,buffer2,BUFFER2_LENGTH);
             color_print(string,"red"); 
             continue;
           } 
         }

         
       
       }
     }   
     else
     {
       // if the process did not fork, close the client socket
       close(CLIENT_SOCKET);
     } 
   }
   return 1;
   #undef pointer_reset_all
   #undef SERVER_ERROR
}
