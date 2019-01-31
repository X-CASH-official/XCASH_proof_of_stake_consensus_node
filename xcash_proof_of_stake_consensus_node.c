#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <unistd.h>
#include <signal.h>
#include "sys/types.h"
#include "sys/socket.h"
#include <netdb.h> 
#include "netinet/in.h"
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h> 
#include <mongoc/mongoc.h>
#include <bson/bson.h>

#include "xcash_proof_of_stake_consensus_node_functions_and_macros.h"
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

  // iniltize the global variables
  xcash_wallet_public_address = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  nodes_public_address_list = (char*)calloc(BUFFER_SIZE,sizeof(char));
  nodes_name_list = (char*)calloc(BUFFER_SIZE,sizeof(char));
  nodes_public_address_list_received_data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  server_message = (char*)calloc(BUFFER_SIZE,sizeof(char));
  current_consensus_nodes_IP_address = (char*)calloc(BUFFER_SIZE,sizeof(char));
  main_nodes_public_address = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  current_round_part = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  current_round_part_backup_node = (char*)calloc(BUFFER_SIZE,sizeof(char));

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
    mongoc_cleanup();
    exit(0);
  }
  

  // set the current_round_part and current_round_part_backup_node to an empty string, this way the node will start at the begining of a round
  memcpy(current_round_part,"",1); 
  memcpy(current_round_part_backup_node,"",1);

  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char)); 

  // write the message
  color_print("X-CASH Proof Of Stake - Consensus Node, Version 1.0.0\n","green");

  // set the server_message
  memcpy(server_message,"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS",48);

 /* // get the wallets public address
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
  }*/
  
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