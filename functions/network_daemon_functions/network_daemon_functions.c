#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mongoc/mongoc.h>
#include <bson/bson.h>

#include "define_macro_functions.h"
#include "define_macros.h"
#include "structures.h"
#include "variables.h"

#include "define_macros_functions.h"
#include "network_daemon_functions.h"
#include "network_functions.h"
#include "string_functions.h"

/*
-----------------------------------------------------------------------------------------------------------
Functions
-----------------------------------------------------------------------------------------------------------
*/

/*
-----------------------------------------------------------------------------------------------------------
Name: get_block_template
Description: Gets the block template for creating a new block
Parameters:
  result - The result to store the block_blob in
  reserve_bytes_length - The amount of reserve bytes to create in the block template
  MESSAGE_SETTINGS - 1 to print the messages, otherwise 0. This is used for the testing flag to not print any success or error messages
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int get_block_template(char *result, char* reserve_bytes_length, const int HTTP_SETTINGS)
{
  // Constants
  const char* HTTP_HEADERS[] = {"Content-Type: application/json","Accept: application/json"}; 
  const size_t HTTP_HEADERS_LENGTH = sizeof(HTTP_HEADERS)/sizeof(HTTP_HEADERS[0]);
  const size_t RESERVE_BYTES_LENGTH = strnlen(reserve_bytes_length,BUFFER_SIZE);

  // Variables
  char* message = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // define macros
  #define pointer_reset_all \
  free(message); \
  message = NULL; \
  free(data); \
  data = NULL; \

  // check if the memory needed was allocated on the heap successfully
  if (message == NULL || data == NULL)
  {
    if (message != NULL)
    {
      pointer_reset(message);
    }
    if (data != NULL)
    {
      pointer_reset(data);
    }
    return 0;
  }

  // create the message
  memcpy(message,"{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"get_block_template\",\"params\":{\"wallet_address\":\"",84);
  memcpy(message+84,xcash_wallet_public_address,XCASH_WALLET_LENGTH);
  memcpy(message+84+XCASH_WALLET_LENGTH,"\",\"reserve_size\":",17);
  memcpy(message+101+XCASH_WALLET_LENGTH,reserve_bytes_length,RESERVE_BYTES_LENGTH);
  memcpy(message+101+XCASH_WALLET_LENGTH+RESERVE_BYTES_LENGTH,"}",1);

  if (send_http_request(data,"127.0.0.1","/json_rpc",XCASH_DAEMON_PORT,"POST", HTTP_HEADERS, HTTP_HEADERS_LENGTH,message,RECEIVE_DATA_TIMEOUT_SETTINGS,"get block template",HTTP_SETTINGS) <= 0)
  {  
    pointer_reset_all;
    return 0;
  }
  
  if (parse_json_data(data,"blocktemplate_blob",result) == 0)
  {
    pointer_reset_all;
    return 0;
  }
  
  pointer_reset_all; 
  return 1;
  
  #undef pointer_reset_all
}



/*
-----------------------------------------------------------------------------------------------------------
Name: get_previous_block_template
Description: Gets the previous_block template
Parameters:
  result - The result to store the previous block_blob in
  MESSAGE_SETTINGS - 1 to print the messages, otherwise 0. This is used for the testing flag to not print any success or error messages
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int get_previous_block_template(char *result, const int HTTP_SETTINGS)
{
  // Constants
  const char* HTTP_HEADERS[] = {"Content-Type: application/json","Accept: application/json"}; 
  const size_t HTTP_HEADERS_LENGTH = sizeof(HTTP_HEADERS)/sizeof(HTTP_HEADERS[0]);

  // Variables
  char* message = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // define macros
  #define pointer_reset_all \
  free(message); \
  message = NULL; \
  free(data); \
  data = NULL; \

  // check if the memory needed was allocated on the heap successfully
  if (message == NULL || data == NULL)
  {
    if (message != NULL)
    {
      pointer_reset(message);
    }
    if (data != NULL)
    {
      pointer_reset(data);
    }
    return 0;
  }

  // get the current block height
  if (get_current_block_height(data, 0) == 0)
  {
    pointer_reset_all;
    return 0;
  }

  // create the message
  memcpy(message,"{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"get_block\",\"params\":{\"height\":\"",68);
  memcpy(message+68,data,strnlen(data,BUFFER_SIZE));
  memcpy(message+68+strnlen(data,BUFFER_SIZE),"\"}}",3);
  memset(data,0,strnlen(data,BUFFER_SIZE));

  if (send_http_request(data,"127.0.0.1","/json_rpc",XCASH_DAEMON_PORT,"POST", HTTP_HEADERS, HTTP_HEADERS_LENGTH,message,RECEIVE_DATA_TIMEOUT_SETTINGS,"get block template",HTTP_SETTINGS) <= 0)
  {  
    pointer_reset_all;
    return 0;
  }
  
  if (parse_json_data(data,"blob",result) == 0)
  {
    pointer_reset_all;
    return 0;
  }
  
  pointer_reset_all; 
  return 1;
  
  #undef pointer_reset_all
}



/*
-----------------------------------------------------------------------------------------------------------
Name: submit_block_template
Description: Adds a network block to the network
Parameters:
  data - The block_blob
  MESSAGE_SETTINGS - 1 to print the messages, otherwise 0. This is used for the testing flag to not print any success or error messages
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int submit_block_template(char* data, const int HTTP_SETTINGS)
{
  // Constants
  const char* HTTP_HEADERS[] = {"Content-Type: application/json","Accept: application/json"}; 
  const size_t HTTP_HEADERS_LENGTH = sizeof(HTTP_HEADERS)/sizeof(HTTP_HEADERS[0]);
  const size_t DATA_LENGTH = strnlen(data,BUFFER_SIZE);

  // Variables
  char* message = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // check if the memory needed was allocated on the heap successfully
  if (message == NULL)
  {
    return 0;
  }

  // create the message
  memcpy(message,"{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"submit_block\",\"params\":[\"",61);
  memcpy(message+61,data,DATA_LENGTH);
  memcpy(message+61+DATA_LENGTH,"\"]}",3);
  memset(data,0,strnlen(data,BUFFER_SIZE));

  if (send_http_request(data,"127.0.0.1","/json_rpc",XCASH_DAEMON_PORT,"POST", HTTP_HEADERS, HTTP_HEADERS_LENGTH,message,RECEIVE_DATA_TIMEOUT_SETTINGS,"submit block template",HTTP_SETTINGS) <= 0)
  {  
    pointer_reset(message);
    return 0;
  }
  
  if (strstr(data,"error") != NULL)
  {
    pointer_reset(message);
    return 0;
  }
  
  pointer_reset(message); 
  return 1;
}



/*
-----------------------------------------------------------------------------------------------------------
Name: verify_blockchain_network_transactions
Description: Gets the transaction details
Parameters:
  data - The transactions to verify
  MESSAGE_SETTINGS - 1 to print the messages, otherwise 0. This is used for the testing flag to not print any success or error messages
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int verify_blockchain_network_transactions(char* transactions[], const size_t AMOUNT_OF_TRANSACTIONS, const int MESSAGE_SETTINGS)
{
  // Constants
  const char* HTTP_HEADERS[] = {"Content-Type: application/json","Accept: application/json"}; 
  const size_t HTTP_HEADERS_LENGTH = sizeof(HTTP_HEADERS)/sizeof(HTTP_HEADERS[0]);

  // Variables
  char* message = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t count;
  size_t counter = 0;

  // define macros
  #define pointer_reset_all \
  free(message); \
  message = NULL; \
  free(data); \
  data = NULL; \

  // check if the memory needed was allocated on the heap successfully
  if (message == NULL || data == NULL)
  {
    if (message != NULL)
    {
      pointer_reset(message);
    }
    if (data != NULL)
    {
      pointer_reset(data);
    }
    return 0;
  }

  // create the message
  memcpy(message,"{\"txs_hashes\":[",15);
  counter += 15;
  for (count = 0; count < AMOUNT_OF_TRANSACTIONS; count++)
  {
    memcpy(message+counter,"\"",1);
    counter++;
    memcpy(message+counter,transactions[count],strnlen(transactions[count],BUFFER_SIZE));
    counter += strnlen(transactions[count],BUFFER_SIZE);
    memcpy(message+counter,"\",",2);
    counter += 2;
  }
  memcpy(message+counter-1,"]}",2);

  if (send_http_request(data,"127.0.0.1","/get_transactions",XCASH_DAEMON_PORT,"POST", HTTP_HEADERS, HTTP_HEADERS_LENGTH,message,RECEIVE_DATA_TIMEOUT_SETTINGS,"",MESSAGE_SETTINGS) <= 0)
  {  
    pointer_reset_all;   
    return 0;
  }

  // verify the blockchain_network_transactions
  // if the results contain missed_tx or "in_pool": false then the transactions are not verified  
  if (strstr(data,"missed_tx") != NULL || strstr(data,"\"in_pool\": false") != NULL)
  {
    pointer_reset_all;   
    return 0;
  }
    
  pointer_reset_all; 
  return 1;
  
  #undef pointer_reset_all
}



/*
-----------------------------------------------------------------------------------------------------------
Name: get_current_block_height
Description: Gets the current block height of the network
Parameters:
  result - The string where you want the current block height to be saved to
  MESSAGE_SETTINGS - 1 to print the messages, otherwise 0. This is used for the testing flag to not print any success or error messages
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int get_current_block_height(char *result, const int MESSAGE_SETTINGS)
{
  // Constants
  const char* HTTP_HEADERS[] = {"Content-Type: application/json","Accept: application/json"}; 
  const size_t HTTP_HEADERS_LENGTH = sizeof(HTTP_HEADERS)/sizeof(HTTP_HEADERS[0]);

  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL)
  {
    return 0;
  }

  if (send_http_request(data,"127.0.0.1","/json_rpc",XCASH_DAEMON_PORT,"POST", HTTP_HEADERS, HTTP_HEADERS_LENGTH,"{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"get_block_count\"}",RECEIVE_DATA_TIMEOUT_SETTINGS,"get current block height",MESSAGE_SETTINGS) <= 0)
  {  
    pointer_reset(data);   
    return 0;
  }
  
  if (parse_json_data(data,"count",result) == 0)
  {
    pointer_reset(data); 
    return 0;
  }
    
  pointer_reset(data); 
  return 1;
}



/*
-----------------------------------------------------------------------------------------------------------
Name: get_previous_block_hash
Description: Gets the previous block hash of the network
Parameters:
  result - The string where you want the previous block hash to be saved to
  MESSAGE_SETTINGS - 1 to print the messages, otherwise 0. This is used for the testing flag to not print any success or error messages
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int get_previous_block_hash(char *result, const int MESSAGE_SETTINGS)
{
  // Constants
  const char* HTTP_HEADERS[] = {"Content-Type: application/json","Accept: application/json"}; 
  const size_t HTTP_HEADERS_LENGTH = sizeof(HTTP_HEADERS)/sizeof(HTTP_HEADERS[0]);

  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL)
  {
    return 0;
  }

  if (send_http_request(data,"127.0.0.1","/json_rpc",XCASH_DAEMON_PORT,"POST", HTTP_HEADERS, HTTP_HEADERS_LENGTH,"{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"get_last_block_header\"}",RECEIVE_DATA_TIMEOUT_SETTINGS,"get previous block hash",MESSAGE_SETTINGS) <= 0)
  {  
    pointer_reset(data);   
    return 0;
  }
  
  if (parse_json_data(data,"hash",result) == 0)
  {
    pointer_reset(data); 
    return 0;
  }
      
  pointer_reset(data); 
  return 1;
}