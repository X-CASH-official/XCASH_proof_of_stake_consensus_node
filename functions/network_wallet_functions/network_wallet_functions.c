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
#include "network_functions.h"
#include "network_wallet_functions.h"
#include "string_functions.h"

/*
-----------------------------------------------------------------------------------------------------------
Functions
-----------------------------------------------------------------------------------------------------------
*/

/*
-----------------------------------------------------------------------------------------------------------
Name: get_public_address
Description: Gets the public address of your wallet
Parameters:
  MESSAGE_SETTINGS - 1 to print the messages, otherwise 0. This is used for the testing flag to not print any success or error messages
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int get_public_address(const int HTTP_SETTINGS)
{
  // Constants
  const char* HTTP_HEADERS[] = {"Content-Type: application/json","Accept: application/json"}; 
  const size_t HTTP_HEADERS_LENGTH = sizeof(HTTP_HEADERS)/sizeof(HTTP_HEADERS[0]);

  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));

  if (data == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // define macros
  #define GET_PUBLIC_ADDRESS_DATA "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"get_address\"}"

  if (send_http_request(data,"127.0.0.1","/json_rpc",XCASH_WALLET_PORT,"POST", HTTP_HEADERS, HTTP_HEADERS_LENGTH,GET_PUBLIC_ADDRESS_DATA,RECEIVE_DATA_TIMEOUT_SETTINGS,"get public address",HTTP_SETTINGS) <= 0)
  {  
    pointer_reset(data);   
    return 0;
  }
  
  if (parse_json_data(data,"address",xcash_wallet_public_address) == 0)
  {
    pointer_reset(data); 
    return 0;
  }
  
  // check if the returned data is valid
  if (strnlen(xcash_wallet_public_address,BUFFER_SIZE) != XCASH_WALLET_LENGTH && strncmp(xcash_wallet_public_address,XCASH_WALLET_PREFIX,3) != 0)
  {
     pointer_reset(data); 
     return 0;
  }
  
  pointer_reset(data); 
  return 1;

  #undef GET_PUBLIC_ADDRESS_DATA
}



/*
-----------------------------------------------------------------------------------------------------------
Name: check_reserve_proofs
Description: Checks all of the reserve proofs in the reserve_proof_list struct
Parameters:
  HTTP_SETTINGS - 1 to print the messages, otherwise 0. This is used for the testing flag to not print any success or error messages
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int check_reserve_proofs(char* result, const int HTTP_SETTINGS)
{
  // Constants
  const char* HTTP_HEADERS[] = {"Content-Type: application/json","Accept: application/json"}; 
  const size_t HTTP_HEADERS_LENGTH = sizeof(HTTP_HEADERS)/sizeof(HTTP_HEADERS[0]);

  // Variables
  char* data = (char*)calloc(205000000,sizeof(char));
  size_t count;
  size_t counter;

  if (data == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // create the message
  memcpy(data,"{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"check_reserve_proofs\",\"params\":{\"address\":[\"",80);
  counter = 80;
  for (count = 0; count < RESERVE_PROOFS_LIST_MAXIMUM_AMOUNT; count++)
  {
    memcpy(data+counter,reserve_proofs_list.public_address_created_reserve_proof[count],XCASH_WALLET_LENGTH);
    counter += XCASH_WALLET_LENGTH;
    memcpy(data+counter,"\",\"",3);
    counter += 3;
  }
  memcpy(data+counter-1,"],\"message\":[\"",14);
  for (count = 0; count < RESERVE_PROOFS_LIST_MAXIMUM_AMOUNT; count++)
  {
    memcpy(data+counter,reserve_proofs_list.public_address_voted_for[count],XCASH_WALLET_LENGTH);
    counter += XCASH_WALLET_LENGTH;
    memcpy(data+counter,"\",\"",3);
    counter += 3;
  }
  memcpy(data+counter-1,"],\"signature\":[\"",14);
  for (count = 0; count < RESERVE_PROOFS_LIST_MAXIMUM_AMOUNT; count++)
  {
    memcpy(data+counter,reserve_proofs_list.reserve_proof[count],strnlen(reserve_proofs_list.reserve_proof[count],10000));
    counter += strnlen(reserve_proofs_list.reserve_proof[count],10000);
    memcpy(data+counter,"\",\"",3);
    counter += 3;
  }
  memcpy(data+counter-1,"]}}",3);

  if (send_http_request(result,"127.0.0.1","/json_rpc",XCASH_WALLET_PORT,"POST", HTTP_HEADERS, HTTP_HEADERS_LENGTH,data,RECEIVE_DATA_TIMEOUT_SETTINGS,"check reserve proofs",HTTP_SETTINGS) <= 0)
  {  
    pointer_reset(data);   
    return 0;
  }
  
  pointer_reset(data); 
  return 1;
}