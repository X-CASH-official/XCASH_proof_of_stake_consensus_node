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
#include "database_functions.h"
#include "file_functions.h"
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
    return 0;
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
    return 0;
  }  
  
  // set the collection
  collection = mongoc_client_get_collection(database_client, DATABASE_NAME, DATABASE_COLLECTION);

  document = bson_new();
  if (!document)
  {
    GET_BLOCK_VERIFIERS_LIST_ERROR("Could not create the document for the database\nFunction: get_block_verifiers_list");
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
    return 0;
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

  #undef DATABASE_COLLECTION
  #undef MESSAGE
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
    return 0;
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
  }
  // set the thread to detach once completed, since we do not need to use anything it will return
  if (pthread_detach(thread_id) != 0)
  {
    CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR("Could not start the receive_votes_from_nodes_timeout\nFunction: consensus_node_create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK");
  }

  return 1;

  #undef CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR
}



/*
-----------------------------------------------------------------------------------------------------------
Name: calculate_main_nodes_role
Description: calculate the new main nodes roles from the previous network block
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
    return 0;
  }

  // get the previous block template
  if (get_previous_block_template(data,0) == 0)
  {
    CALCULATE_MAIN_NODES_ROLE_ERROR("Could not get the previous block template\nFunction: calculate_main_nodes_role");
  }

  // convert the network_block_string to blockchain_data
  if (network_block_string_to_blockchain_data(data) == 0)
  {
    CONSENSUS_NODE_CREATE_NEW_BLOCK_ERROR("Could not convert the network_block_string to blockchain_data\nFunction: consensus_node_create_new_block\nReceive Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK");
  }

  // read the VRF beta string for round part 3 and calculate the main nodes role


  // update the main nodes role in the database
  

  return 1;

  #undef DATABASE_COLLECTION
  #undef MESSAGE
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

  // define macros
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
    return 0;
  }

  // read the current_round_part and current_round_part_backup_node from the database
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
  memcpy(data+strnlen(data),current_round_part_backup_node,1);

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
    CALCULATE_MAIN_NODES_ROLE_ERROR("Could not update the current_round_part and current_round_part_backup_node in the database\nFunction: mainode_consensus");
  }

  pointer_reset_all;
  return 1;

  #undef DATABASE_COLLECTION
  #undef MESSAGE
  #undef pointer_reset_all
  #undef CALCULATE_MAIN_NODES_ROLE_ERROR
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
Name: server_receive_data_socket_consensus_node_to_node
Description: Runs the code when the server receives the CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS message
Parameters:
  message - The message
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int server_receive_data_socket_consensus_node_to_node(const int CLIENT_SOCKET, pthread_t thread_id, char* message)
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL)
  {
    return 0;
  }

  // verify the data
  if (verify_data(message,1,0,0) == 0)
  {
    // close the forked process
    color_print("Message could not be verified from consensus node for CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
    return 0;
  }

  // parse the message
  if (parse_json_data(message,"main_nodes_public_address",data) == 0)
  {
    color_print("Could not parse main_nodes_public_address from the CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS message","red");
    return 0;
  }
  memcpy(main_nodes_public_address,data,strnlen(data,BUFFER_SIZE));

  if (parse_json_data(message,"current_round_part",data) == 0)
  {
    color_print("Could not parse current_round_part from the CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS message","red");
    return 0;
  }
  memcpy(current_round_part,data,strnlen(data,BUFFER_SIZE));

  if (parse_json_data(message,"current_round_part_backup_node",data) == 0)
  {
    color_print("Could not parse current_round_part_backup_node from the CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS message","red");
    return 0;
  }
  memcpy(current_round_part_backup_node,data,strnlen(data,BUFFER_SIZE));



  // create a timeout from the time the consensus node lets us know who the main node is for this part of the round, to the time the main node sends us data.
  if (strncmp(current_round_part,"1",BUFFER_SIZE) == 0 || strncmp(current_round_part,"3",BUFFER_SIZE) == 0)
  {
    memcpy(data,"VRF_PUBLIC_AND_PRIVATE_KEY",26);
  }
  else if (strncmp(current_round_part,"2",BUFFER_SIZE) == 0)
  {
    memcpy(data,"VRF_RANDOM_DATA",15);
  }
  else if (strncmp(current_round_part,"4",BUFFER_SIZE) == 0)
  {
    memcpy(data,"BLOCK_PRODUCER",14);
  }
  // create a struct for the parameters
  struct mainnode_timeout_thread_parameters parameters = {
    (const pid_t)getpid(),
    0,
    (const char*)data,
    (const char*)current_round_part,
    (const char*)current_round_part_backup_node,

  };
  // create a timeout for this connection, since we need to limit the amount of time a client has to send data from once it connected
  if (pthread_create(&thread_id, NULL, &mainnode_timeout_thread, (void *)&parameters) != 0)
  {
    return 0;
  }
  // set the thread to dettach once completed, since we do not need to use anything it will return.
  if (pthread_detach(thread_id) != 0)
  {
    return 0;
  }
  pointer_reset(data);
  return 1;
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
    return 0;
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
           if (server_received_data_xcash_proof_of_stake_test_data(CLIENT_SOCKET,buffer) == 0)
           {
             SERVER_ERROR(1);
           }
         }
         else if (strstr(buffer,"\"message_settings\": \"NODE_TO_CONSENSUS_NODE_RECEIVE_UPDATED_NODE_LIST\"") != NULL && strncmp(server_message,"NODE_TO_CONSENSUS_NODE_RECEIVE_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
         {
           if (server_receive_data_socket_consensus_node_to_node(CLIENT_SOCKET,thread_id,buffer) == 0)
           {
             SERVER_ERROR(1);
           }
         }
         else if (strstr(buffer,"\"message_settings\": \"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS\"") != NULL && strncmp(server_message,"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS",BUFFER_SIZE) == 0)
         {
           // check to see if the node should start only at the begining of a round
           if (strncmp(current_round_part,"",strnlen(current_round_part,BUFFER_SIZE)) == 0 && strncmp(current_round_part,"",strnlen(current_round_part,BUFFER_SIZE)) == 0)
           {
             if (strstr(buffer,"\"current_round_part\": \"1\"") != NULL && strstr(buffer,"\"current_round_part_backup_node\": \"0\"") != NULL)
             {
               if (server_receive_data_socket_consensus_node_to_node(CLIENT_SOCKET,thread_id,buffer) == 0)
               {
                 SERVER_ERROR(1);
               }               
             }
           }
           else
           {
             if (server_receive_data_socket_consensus_node_to_node(CLIENT_SOCKET,thread_id,buffer) == 0)
             {
               SERVER_ERROR(1);
             }
           }           
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
