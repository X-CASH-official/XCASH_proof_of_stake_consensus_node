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

#include "xcash_proof_of_stake_consensus_node_functions_and_macros.h"
#include "xcash_proof_of_stake_consensus_node_test.h"

/*
-----------------------------------------------------------------------------------------------------------
Global variables
-----------------------------------------------------------------------------------------------------------
*/

const char STR1_TEST [BUFFER_SIZE] = "test string 1";
const char* STR2_TEST = "test string 2";
char string1_test [BUFFER_SIZE];
char* string2_test;
char* result_test;
char* data_test;
int count_test = 0;

/*
-----------------------------------------------------------------------------------------------------------
Functions
-----------------------------------------------------------------------------------------------------------
*/

/*
-----------------------------------------------------------------------------------------------------------
Name: append_string_test
Description: Test the append_string macro
Return: The number of passed append_string test
-----------------------------------------------------------------------------------------------------------
*/

int append_string_test()
{  
  // define macros
  #define APPEND_STRING_TOTAL_TEST 4

  // reset the variables
  memset(&string1_test,0,sizeof(string1_test)); 
  memset(string2_test,0,strnlen(string2_test,BUFFER_SIZE)); 
  count_test = 0;

  // write the start test message
  color_print(TEST_OUTLINE,"blue");
  printf("\033[1;34mappend_string test - Total test: %d\033[0m\n",APPEND_STRING_TOTAL_TEST);
  color_print(TEST_OUTLINE,"blue");
  printf("\n");

  // run the test
  
  // test for using append_string on an empty statically allocated char
  append_string(string1_test,STR1_TEST);
  if (strncmp(string1_test,STR1_TEST,BUFFER_SIZE) == 0)
  {
    color_print("PASSED! Test for using append_string on an empty statically allocated char","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for using append_string on an empty statically allocated char","red");
  }

  // test for using append_string on a statically allocated char
  append_string(string1_test," ");
  append_string(string1_test,STR1_TEST);
  if (strncmp(string1_test,"test string 1 test string 1",BUFFER_SIZE) == 0)
  {
    color_print("PASSED! Test for using append_string on a statically allocated char","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for using append_string on a statically allocated char","red");
  }
    
  // test for using append_string on an empty dynamically allocated char
  append_string(string2_test,STR2_TEST);
  if (strncmp(string2_test,STR2_TEST,BUFFER_SIZE) == 0)
  {
    color_print("PASSED! Test for using append_string on an empty dynamically allocated char","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for using append_string on an empty dynamically allocated char","red");
  }

  // test for using append_string on a dynamically allocated char
  append_string(string2_test," ");
  append_string(string2_test,STR2_TEST);
  if (strncmp(string2_test,"test string 2 test string 2",BUFFER_SIZE) == 0)
  {
    color_print("PASSED! Test for using append_string on a dynamically allocated char","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for using append_string on a dynamically allocated char","red");
  }



  // write the end test message
  if (count_test == APPEND_STRING_TOTAL_TEST)
  {
    printf("\n");
    color_print(TEST_OUTLINE,"green");
    printf("\033[1;32mappend_string test - Passed test: %d, Failed test: 0\033[0m\n",APPEND_STRING_TOTAL_TEST);
    color_print(TEST_OUTLINE,"green");
    printf("\n\n");
  }
  else
  {
    printf("\n");
    color_print(TEST_OUTLINE,"red");
    printf("\033[1;31mappend_string test - Passed test: %d, Failed test: %d\033[0m\n",count_test,APPEND_STRING_TOTAL_TEST-count_test);
    color_print(TEST_OUTLINE,"red");
    printf("\n\n");
  } 
  return count_test;
}


/*
-----------------------------------------------------------------------------------------------------------
Name: parse_json_data_test
Description: Test the parse_json_data function
Return: The number of passed parse_json_data test
-----------------------------------------------------------------------------------------------------------
*/

int parse_json_data_test()
{  
  // define macros
  #define PARSE_JSON_DATA_TOTAL_TEST 227
 
  #define SIGN_RPC_CALL_TEST_DATA "{\r\n  \"id\": \"0\",\r\n  \"jsonrpc\": \"2.0\",\r\n  \"result\": {\r\n    \"xcash_proof_of_stake_signature\": \"SIGN_RPC_CALL_TEST_DATA\"\r\n  }\r\n}"
  #define VERIFY_RPC_CALL_TEST_DATA "{\r\n  \"id\": \"0\",\r\n  \"jsonrpc\": \"2.0\",\r\n  \"result\": {\r\n    \"good\": VERIFY_RPC_CALL_TEST_DATA\r\n  }\r\n}"
  #define GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA "{\r\n  \"id\": \"0\",\r\n  \"jsonrpc\": \"2.0\",\r\n  \"result\": {\r\n    \"blockhashing_blob\": \"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\",\r\n    \"blocktemplate_blob\": \"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\",\r\n    \"difficulty\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,\r\n    \"expected_reward\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,\r\n    \"height\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,\r\n    \"prev_hash\": \"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\",\r\n    \"reserved_offset\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,\r\n    \"status\": \"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\",\r\n    \"untrusted\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\r\n  }\r\n}"
 


 /*
  This message is sent from the Consensus node in the node_to_consensus_node_send_current_consensus_node_IP_address function and received by the nodes in the get_current_consensus_node_IP_address function.
 
  The purpose of this message is for the Consensus node to send an updated list of nodes to the node. 
 
  message_settings - The type of the message
  current_consensus_node_IP_address - The current consensus nodes IP address.
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n \"current_consensus_node_IP_address\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n \"data\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n}"



/*
  This message is sent from the nodes in the get_current_consensus_node_IP_address function and received by the consensus node in the node_to_consensus_node_send_current_consensus_node_IP_address function.
 
  The purpose of this message is for the node to get an updated list of nodes from the consensus node.
 
  message_settings - The type of the message
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS "{\r\n \"message_settings\": \"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n \"public_address\": \"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n \"previous_block_hash\": \"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n \"current_round_part\": \"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n \"current_round_part_backup_node\": \"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n \"data\": \"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n \"xcash_proof_of_stake_signature\": \"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n}"



/*
  This message is sent from the Consensus node in the node_to_consensus_node_send_updated_node_list function and received by the nodes in the get_updated_node_list function.
 
  The purpose of this message is for the Consensus node to send an updated list of nodes to the node. 
 
  message_settings - The type of the message
  nodes_name_list - The list of the nodes name list (node1|node2) or UPDATED_NODE_LIST
  nodes_public_address_list - the list of the nodes public address (node1|node2) or UPDATED_NODE_LIST
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST\",\r\n \"nodes_name_list\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST\",\r\n \"nodes_public_address_list\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST\",\r\n \"data\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST\",\r\n}"



/*
  This message is sent from the nodes in the get_updated_node_list function and received by the consensus node in the node_to_consensus_node_send_updated_node_list function.
 
  The purpose of this message is for the node to get an updated list of nodes from the consensus node.
 
  message_settings - The type of the message
  nodes_updated_time - The nodes_updated_time that the node last updated the nodes list
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST "{\r\n \"message_settings\": \"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST\",\r\n \"nodes_updated_time\": \"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST\",\r\n \"public_address\": \"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST\",\r\n \"previous_block_hash\": \"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST\",\r\n \"current_round_part\": \"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST\",\r\n \"current_round_part_backup_node\": \"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST\",\r\n \"data\": \"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST\",\r\n \"xcash_proof_of_stake_signature\": \"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST\",\r\n}"



  /*
  This message is sent from the Consensus node in the send_and_receive_data_socket_consensus_node_to_node function and received by the nodes in the receive_data_socket_consensus_node_to_node function.
 
  The purpose of this message is for the consensus node to let the nodes know who is the main node for this part of the round.
 
  message_settings - The type of the message.
  main_nodes_public_address - The public address of the main node for that part of the round.
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS\",\r\n \"main_nodes_public_address\": \"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS\",\r\n \"data\": \"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS\",\r\n}"
 
 
 
 /*
  This message is sent from the nodes in the mainnode_timeout function and received by the Consensus node in the main_node_timeout_from_node function.
 
  The purpose of this message is for the node to let the consensus node know that the main node did not send the data for its part of the round, so the node is voting for a round change so a backup main node can start that part of the round.
 
  message_settings - The type of the message.
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE "{\r\n \"message_settings\": \"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE\",\r\n \"public_address\": \"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE\",\r\n \"previous_block_hash\": \"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE\",\r\n \"current_round_part\": \"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE\",\r\n \"current_round_part_backup_node\": \"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE\",\r\n \"data\": \"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE\",\r\n \"xcash_proof_of_stake_signature\": \"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE\",\r\n}"
 
 
 
/*
  This message is sent from the Consensus node in the send_and_receive_data_socket_consensus_node_to_mainnode function and received by the main node in the consensus_node_to_main_node function.
 
  The purpose of this message is for the consensus node to let the main node that they are a main node, and they need to start this part of the round.
 
  message_settings - The type of the message.
  message - the part of the round (1-4).
  vrf_beta_string_part_3_of_round - This is the beta_string from part 3 of the round, and is only including in the message to the block producer in part 4 of the round. For the part of the rounds 1-3 the beta_string ""
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND\",\r\n \"message\": \"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND\",\r\n \"vrf_beta_string_part_3_of_round\": \"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND\",\r\n \"data\": \"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND\",\r\n}"
 
 
 
/*
  This message is sent from the main node in the send_and_receive_data_socket_consensus_node_to_mainnode function and received by the nodes in the mainnode_to_node_message_part_1 function.
 
  The purpose of this message is for the main node to send the created data for the part of the round to the nodes, so they can verify the data.
 
  message_settings - The type of the message
  vrf_public_key - The VRF public key.
  vrf_alpha_string - The VRF alpha string. (this is the vrf_public_key for this part of the round)
  vrf_proof - The VRF proof.
  vrf_beta_string - The VRF beta_string.
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define MAIN_NODES_TO_NODES_PART_1_OF_ROUND "{\r\n \"message_settings\": \"MAIN_NODES_TO_NODES_PART_1_OF_ROUND\",\r\n \"vrf_public_key\": \"MAIN_NODES_TO_NODES_PART_1_OF_ROUND\",\r\n \"vrf_alpha_string\": \"MAIN_NODES_TO_NODES_PART_1_OF_ROUND\",\r\n \"vrf_proof\": \"MAIN_NODES_TO_NODES_PART_1_OF_ROUND\",\r\n \"vrf_beta_string\": \"MAIN_NODES_TO_NODES_PART_1_OF_ROUND\",\r\n \"public_address\": \"MAIN_NODES_TO_NODES_PART_1_OF_ROUND\",\r\n \"previous_block_hash\": \"MAIN_NODES_TO_NODES_PART_1_OF_ROUND\",\r\n \"current_round_part\": \"MAIN_NODES_TO_NODES_PART_1_OF_ROUND\",\r\n \"current_round_part_backup_node\": \"MAIN_NODES_TO_NODES_PART_1_OF_ROUND\",\r\n \"data\": \"MAIN_NODES_TO_NODES_PART_1_OF_ROUND\",\r\n \"xcash_proof_of_stake_signature\": \"MAIN_NODES_TO_NODES_PART_1_OF_ROUND\",\r\n}"
 
 
 
/*
  This message is sent from the main node in the send_and_receive_data_socket_consensus_node_to_mainnode function and received by the nodes in the mainnode_to_node_message_part_2 function.
 
  The purpose of this message is for the main node to send the created data for the part of the round to the nodes, so they can verify the data.
 
  message_settings - The type of the message
  vrf_random_character_string - A random 100 character string, used to create the VRF alpha_string.
  vrf_public_key - The VRF public key.
  vrf_alpha_string - The VRF alpha string. (this is the vrf_random_character_string|previous_block_hash)
  vrf_proof - The VRF proof.
  vrf_beta_string - The VRF beta_string.
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define MAIN_NODES_TO_NODES_PART_2_OF_ROUND "{\r\n \"message_settings\": \"MAIN_NODES_TO_NODES_PART_2_OF_ROUND\",\r\n \"vrf_random_character_string\": \"MAIN_NODES_TO_NODES_PART_2_OF_ROUND\",\r\n \"vrf_public_key\": \"MAIN_NODES_TO_NODES_PART_2_OF_ROUND\",\r\n \"vrf_alpha_string\": \"MAIN_NODES_TO_NODES_PART_2_OF_ROUND\",\r\n \"vrf_proof\": \"MAIN_NODES_TO_NODES_PART_2_OF_ROUND\",\r\n \"vrf_beta_string\": \"MAIN_NODES_TO_NODES_PART_2_OF_ROUND\",\r\n \"public_address\": \"MAIN_NODES_TO_NODES_PART_2_OF_ROUND\",\r\n \"previous_block_hash\": \"MAIN_NODES_TO_NODES_PART_2_OF_ROUND\",\r\n \"current_round_part\": \"MAIN_NODES_TO_NODES_PART_2_OF_ROUND\",\r\n \"current_round_part_backup_node\": \"MAIN_NODES_TO_NODES_PART_2_OF_ROUND\",\r\n \"data\": \"MAIN_NODES_TO_NODES_PART_2_OF_ROUND\",\r\n \"xcash_proof_of_stake_signature\": \"MAIN_NODES_TO_NODES_PART_2_OF_ROUND\",\r\n}"
 
 
 
/*
  This message is sent from the main node in the send_and_receive_data_socket_consensus_node_to_mainnode function and received by the nodes in the mainnode_to_node_message_part_3 function.
 
  The purpose of this message is for the main node to send the created data for the part of the round to the nodes, so they can verify the data.
 
  message_settings - The type of the message
  vrf_random_character_string - A random 100 character string, used to create the VRF alpha_string.
  vrf_public_key - The VRF public key.
  vrf_alpha_string - The VRF alpha string. (this is the vrf_random_character_string|previous_block_hash)
  vrf_proof - The VRF proof.
  vrf_beta_string - The VRF beta_string.
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define MAIN_NODES_TO_NODES_PART_3_OF_ROUND "{\r\n \"message_settings\": \"MAIN_NODES_TO_NODES_PART_3_OF_ROUND\",\r\n \"vrf_random_character_string\": \"MAIN_NODES_TO_NODES_PART_3_OF_ROUND\",\r\n \"vrf_public_key\": \"MAIN_NODES_TO_NODES_PART_3_OF_ROUND\",\r\n \"vrf_alpha_string\": \"MAIN_NODES_TO_NODES_PART_3_OF_ROUND\",\r\n \"vrf_proof\": \"MAIN_NODES_TO_NODES_PART_3_OF_ROUND\",\r\n \"vrf_beta_string\": \"MAIN_NODES_TO_NODES_PART_3_OF_ROUND\",\r\n \"public_address\": \"MAIN_NODES_TO_NODES_PART_3_OF_ROUND\",\r\n \"previous_block_hash\": \"MAIN_NODES_TO_NODES_PART_3_OF_ROUND\",\r\n \"current_round_part\": \"MAIN_NODES_TO_NODES_PART_3_OF_ROUND\",\r\n \"current_round_part_backup_node\": \"MAIN_NODES_TO_NODES_PART_3_OF_ROUND\",\r\n \"data\": \"MAIN_NODES_TO_NODES_PART_3_OF_ROUND\",\r\n \"xcash_proof_of_stake_signature\": \"MAIN_NODES_TO_NODES_PART_3_OF_ROUND\",\r\n}"
 
 
 
/*
  This message is sent from the main node in the send_and_receive_data_socket_consensus_node_to_mainnode function and received by the nodes in the mainnode_to_node_message_part_4 function.
 
  The purpose of this message is for the main node to send the created data for the part of the round to the nodes, so they can verify the data.
 
  message_settings - The type of the message
  vrf_public_key - The VRF public key.
  vrf_alpha_string - The VRF alpha string. (this is the vrf_random_character_string|previous_block_hash)
  vrf_proof - The VRF proof.
  vrf_beta_string - The VRF beta_string.
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define MAIN_NODES_TO_NODES_PART_4_OF_ROUND "{\r\n \"message_settings\": \"MAIN_NODES_TO_NODES_PART_4_OF_ROUND\",\r\n \"vrf_public_key\": \"MAIN_NODES_TO_NODES_PART_4_OF_ROUND\",\r\n \"vrf_alpha_string\": \"MAIN_NODES_TO_NODES_PART_4_OF_ROUND\",\r\n \"vrf_proof\": \"MAIN_NODES_TO_NODES_PART_4_OF_ROUND\",\r\n \"vrf_beta_string\": \"MAIN_NODES_TO_NODES_PART_4_OF_ROUND\",\r\n \"public_address\": \"MAIN_NODES_TO_NODES_PART_4_OF_ROUND\",\r\n \"previous_block_hash\": \"MAIN_NODES_TO_NODES_PART_4_OF_ROUND\",\r\n \"current_round_part\": \"MAIN_NODES_TO_NODES_PART_4_OF_ROUND\",\r\n \"current_round_part_backup_node\": \"MAIN_NODES_TO_NODES_PART_4_OF_ROUND\",\r\n \"data\": \"MAIN_NODES_TO_NODES_PART_4_OF_ROUND\",\r\n \"xcash_proof_of_stake_signature\": \"MAIN_NODES_TO_NODES_PART_4_OF_ROUND\",\r\n}"
 
 
 
/*
  This message is sent from the nodes in the mainnode_to_node_message_part_1 - 4 function and received by the nodes in the node_to_node function.
 
  The purpose of this message is for the nodes to verify what the other nodes received from the main node.
 
  message_settings - The type of the message
  vote_settings - Valid or Invalid if the data was not verified.
  vote_data - The SHA 256 data that the node received.
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define NODES_TO_NODES_VOTE_RESULTS "{\r\n \"message_settings\": \"NODES_TO_NODES_VOTE_RESULTS\",\r\n \"vote_settings\": \"NODES_TO_NODES_VOTE_RESULTS\",\r\n \"vote_data\": \"NODES_TO_NODES_VOTE_RESULTS\",\r\n \"public_address\": \"NODES_TO_NODES_VOTE_RESULTS\",\r\n \"previous_block_hash\": \"NODES_TO_NODES_VOTE_RESULTS\",\r\n \"current_round_part\": \"NODES_TO_NODES_VOTE_RESULTS\",\r\n \"current_round_part_backup_node\": \"NODES_TO_NODES_VOTE_RESULTS\",\r\n \"data\": \"NODES_TO_NODES_VOTE_RESULTS\",\r\n \"xcash_proof_of_stake_signature\": \"NODES_TO_NODES_VOTE_RESULTS\",\r\n}"
 
 
 
/*
  This message is sent from the nodes in the node_to_node_message_timeout function and received by the consensus node in the node_to_node_vote function.
 
  The purpose of this message is for the nodes to let the consensus node know what the vote count is for that part of the round.
 
  message_settings - The type of the message
  vote_result - TRUE or FALSE
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define NODES_TO_CONSENSUS_NODE_VOTE_RESULTS "{\r\n \"message_settings\": \"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS\",\r\n \"vote_result\": \"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS\",\r\n \"public_address\": \"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS\",\r\n \"previous_block_hash\": \"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS\",\r\n \"current_round_part\": \"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS\",\r\n \"current_round_part_backup_node\": \"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS\",\r\n \"data\": \"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS\",\r\n \"xcash_proof_of_stake_signature\": \"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS\",\r\n}"
 
 
 
 
/*
  This message is sent from the Consensus node in the send_vote_list_to_nodes function and received by the nodes in the receive_vote_list function.
 
  The purpose of this message is for the nodes to get the list of the current top 100 delegates for that 24 hour time period, so they know what delegates are enabled.
 
  message_settings - The type of the message
  nodes_name_list - The list of the nodes name list (node1|node2)
  nodes_public_address_list - The list of the nodes public address (node1|node2)
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES\",\r\n \"nodes_name_list\": \"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES\",\r\n \"nodes_public_address_list\": \"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES\",\r\n \"data\": \"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES\",\r\n}"


 
/*
  This message is sent from the Consensus node in the send_round_change function and received by the nodes and main nodes in the receive_round_change function.
 
  The purpose of this message is for the Consensus node to let the nodes and the main node know that there is a round change, and they should restart.
 
  message_settings - The type of the message
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE\",\r\n \"data\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE\",\r\n}"
 
 
 
/*
  This message is sent from the Consensus node in the check_if_consensus_node_is_offline function and received by the nodes and main nodes in the receive_change_consensus_node function.
 
  The purpose of this message is for the Consensus node to let the nodes and the main node know that there is a consensus node change, and they should restart.
 
  message_settings - The type of the message
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE\",\r\n \"data\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE\",\r\n}"
 
 
/*
  This message is sent from the Consensus node in the send_xcash_proof_of_stake_message function and received by the nodes and main nodes in the receive_xcash_proof_of_stake function.
 
  The purpose of this message is for the Consensus node to let the nodes and the main node know that the Consensus node will now create the blocks on the network, due to a possible hack, and they should restart.
 
  message_settings - The type of the message
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE\",\r\n \"data\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE\",\r\n}"
 
 
 
/*
  This message is sent from the Consensus node in the xcash_proof_of_stake function and received by the consensus node private key in the receive_xcash_proof_of_stake_settings function.
 
  The purpose of this message is for the consensus node to get the xcash_proof_of_stake_settings
 
  message_settings - The type of the message
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"data\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n}"
 
 
 
/*
  This message is sent from the Consensus node private key in the receive_xcash_proof_of_stake_settings function and received by the consensus node in the xcash_proof_of_stake function.
 
  The purpose of this message is for the consensus node private key to return the receive_xcash_proof_of_stake_settings to the consensus node.
 
  message_settings - The type of the message
  xcash_proof_of_stake_settings - The xcash_proof_of_stake_settings (0 or 1)
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS "{\r\n \"message_settings\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"xcash_proof_of_stake_settings\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"public_address\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"current_round_part\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"data\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n}"
 
 
 
/*
  This message is sent from the consensus node in the consensus_node_create_new_block function and received by the consensus node private key in the consensus_node_create_new_block function.
 
  The purpose of this message is for the consensus node to create a block without the delegates
 
  message_settings - The type of the message
  current_block_template_blob - The current block template blob
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"current_block_template_blob\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"data\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n}"
 
 
 
/*
  This message is sent from the consensus node private key in the consensus_node_create_new_block function and received by the consensus node in the consensus_node_create_new_block function.
 
  The purpose of this message is for the consensus node private key to sign the previous_block_hash|current_block_template_blob so the block will be valid and can be added to the network to create a block without the delegates
 
  message_settings - The type of the message
  public_address - The public address of the node that is sending the data.
  message_data_settings - Previous block hash | current block template blob.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK "{\r\n \"message_settings\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"message_data_settings\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"public_address\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"current_round_part\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"data\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n}"
 
 
 
/*
  This message is sent from the Consensus node in the send_new_part_of_round function and received by the nodes and main nodes in the receive_new_part_of_round function.
 
  The purpose of this message is for the consensus node to tell the nodes and main nodes that a new part of the round is starting
 
  message_settings - The type of the message
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND\",\r\n \"data\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND\",\r\n}"
 
 
 
/*
  This message is sent from the Consensus node in the send_next_round function and received by the nodes and main nodes in the receive_new_round function.
 
  The purpose of this message is for the consensus node to tell the nodes and main nodes that a new round is starting
 
  message_settings - The type of the message
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND\",\r\n \"data\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND\",\r\n}"
 
 
 
/*
  This message is sent from the consensus node in the create_new_block function and received by the consensus node private key in the create_new_block function.
 
  The purpose of this message is for the consensus node to submit the block to the network that the block producer has created.
 
  message_settings - The type of the message
  current_block_template_blob - The current block template blob
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK\",\r\n \"current_block_template_blob\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK\",\r\n \"data\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK\",\r\n}"
 
 
 
/*
  This message is sent from the consensus node private key in the create_new_block function and received by the consensus node in the create_new_block function.
 
  The purpose of this message is for the consensus node private key to sign the previous_block_hash|current_block_template_blob so the block will be valid and can be added to the network
 
  message_settings - The type of the message
  public_address - The public address of the node that is sending the data.
  message_data_settings - Previous block hash | current block template blob.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK "{\r\n \"message_settings\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"message_data_settings\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"public_address\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"current_round_part\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"data\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n}"
 
 
 
/*
  This message is sent from the Consensus node in the send_recalculating_votes_to_nodes_and_main_nodes function and received by the nodes and main nodes in the receive_recalculating_votes function.
 
  The purpose of this message is for the Consensus node to let the nodes and the main node know that the Consensus node will now recalculate the votes, and they should restart.
 
  message_settings - The type of the message
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES\",\r\n \"data\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES\",\r\n}"
 
 
 
/*
  This message is sent from the VOTING WEBSITE API PROGRAM and received by the consensus node private key in the send_xcash_proof_of_stake_settings function.
 
  The purpose of this message is for the consensus node private key to change the xcash_proof_of_stake_settings to 1
 
  message_settings - The type of the message
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS "{\r\n \"message_settings\": \"VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"public_address\": \"VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"previous_block_hash\": \"VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"current_round_part\": \"VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"current_round_part_backup_node\": \"VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"data\": \"VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"xcash_proof_of_stake_signature\": \"VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n}"

  // reset the variables
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  count_test = 0;
 
  // write the start test message
  color_print(TEST_OUTLINE,"blue");
  printf("\033[1;34mparse_json_data test - Total test: %d\033[0m\n",PARSE_JSON_DATA_TOTAL_TEST);
  color_print(TEST_OUTLINE,"blue");
  printf("\n");
 
  // run the test
 
  // test parsing the return data for the sign RPC call for the xcash_proof_of_stake_signature field
  append_string(result_test,SIGN_RPC_CALL_TEST_DATA);
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"SIGN_RPC_CALL_TEST_DATA",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing the return data for the sign RPC call for the xcash_proof_of_stake_signature field","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing the return data for the sign RPC call for the xcash_proof_of_stake_signature field","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing the return data for the sign RPC call for the xcash_proof_of_stake_signature field","red");
  }
 
  // test parsing the return data for the verify RPC call for the good field
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,VERIFY_RPC_CALL_TEST_DATA);
  if (parse_json_data(result_test,"good",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"VERIFY_RPC_CALL_TEST_DATA",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing the return data for the verify RPC call for the good field","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing the return data for the verify RPC call for the good field","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing the return data for the verify RPC call for the good field","red");
  }
 
  // test parsing the return data for the get_block_template RPC call for the blocktemplate_blob field
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA);
  if (parse_json_data(result_test,"blocktemplate_blob",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing the return data for the get_block_template RPC call for the blocktemplate_blob field","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing the return data for the get_block_template RPC call for the blocktemplate_blob field","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing the return data for the get_block_template RPC call for the blocktemplate_blob field","red");
  }
  printf("\n");



  // test for parsing CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
  }  
  if (parse_json_data(result_test,"current_consensus_node_IP_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_consensus_node_IP_address from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_consensus_node_IP_address from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_consensus_node_IP_address from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
  }  
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
  }
  printf("\n");



  // test for parsing NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
  }  
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS","red");
  }
  printf("\n");



  // test for parsing CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
  }  
  if (parse_json_data(result_test,"nodes_name_list",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing nodes_name_list from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing nodes_name_list from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing nodes_name_list from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
  }  
  if (parse_json_data(result_test,"nodes_public_address_list",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing nodes_public_address_list from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing nodes_public_address_list from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing nodes_public_address_list from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST","red");
  }
  printf("\n");



  // test for parsing NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","red");
  }  
  if (parse_json_data(result_test,"nodes_updated_time",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing nodes_updated_time from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing nodes_updated_time from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing nodes_updated_time from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","red");
  }  
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from NODE_TO_CONSENSUS_NODE_SEND_UPDATED_NODE_LIST","red");
  }
  printf("\n");
 
 
 
  // test for parsing CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
  }
  if (parse_json_data(result_test,"main_nodes_public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing main_nodes_public_address from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing main_nodes_public_address from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing main_nodes_public_address from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS","red");
  }
  printf("\n");



  // test for parsing NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","red");
  }  
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from NODES_TO_CONSENSUS_NODE_MAIN_NODE_SOCKET_TIMEOUT_ROUND_CHANGE","red");
  }
  printf("\n");



  // test for parsing CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"message",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_beta_string_part_3_of_round",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_beta_string_part_3_of_round from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_beta_string_part_3_of_round from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_beta_string_part_3_of_round from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND","red");
  }
  printf("\n");



  // test for parsing MAIN_NODES_TO_NODES_PART_1_OF_ROUND
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,MAIN_NODES_TO_NODES_PART_1_OF_ROUND);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_1_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_public_key",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_1_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_public_key from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_public_key from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_public_key from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_alpha_string",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_1_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_alpha_string from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_alpha_string from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_alpha_string from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_proof",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_1_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_proof from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_proof from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_proof from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_beta_string",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_1_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_beta_string from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_beta_string from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_beta_string from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_1_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_1_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_1_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_1_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_1_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_1_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from MAIN_NODES_TO_NODES_PART_1_OF_ROUND","red");
  }
  printf("\n");



  // test for parsing MAIN_NODES_TO_NODES_PART_2_OF_ROUND
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,MAIN_NODES_TO_NODES_PART_2_OF_ROUND);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_2_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_random_character_string",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_2_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_random_character_string from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_random_character_string from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_random_character_string from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_public_key",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_2_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_public_key from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_public_key from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_public_key from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_alpha_string",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_2_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_alpha_string from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_alpha_string from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_alpha_string from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_proof",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_2_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_proof from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_proof from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_proof from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_beta_string",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_2_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_beta_string from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_beta_string from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_beta_string from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_2_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_2_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_2_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_2_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_2_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_2_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from MAIN_NODES_TO_NODES_PART_2_OF_ROUND","red");
  }
  printf("\n");



  // test for parsing MAIN_NODES_TO_NODES_PART_3_OF_ROUND
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,MAIN_NODES_TO_NODES_PART_3_OF_ROUND);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_3_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_random_character_string",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_3_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_random_character_string from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_random_character_string from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_random_character_string from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_public_key",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_3_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_public_key from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_public_key from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_public_key from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_alpha_string",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_3_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_alpha_string from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_alpha_string from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_alpha_string from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_proof",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_3_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_proof from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_proof from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_proof from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_beta_string",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_3_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_beta_string from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_beta_string from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_beta_string from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_3_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_3_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_3_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_3_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_3_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_3_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from MAIN_NODES_TO_NODES_PART_3_OF_ROUND","red");
  }
  printf("\n");



  // test for parsing MAIN_NODES_TO_NODES_PART_4_OF_ROUND
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,MAIN_NODES_TO_NODES_PART_4_OF_ROUND);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_4_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_public_key",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_4_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_public_key from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_public_key from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_public_key from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_alpha_string",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_4_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_alpha_string from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_alpha_string from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_alpha_string from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_proof",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_4_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_proof from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_proof from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_proof from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"vrf_beta_string",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_4_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vrf_beta_string from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vrf_beta_string from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vrf_beta_string from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
  }  
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_4_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_4_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_4_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_4_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_4_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"MAIN_NODES_TO_NODES_PART_4_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from MAIN_NODES_TO_NODES_PART_4_OF_ROUND","red");
  }
  printf("\n");



  // test for parsing NODES_TO_NODES_VOTE_RESULTS
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,NODES_TO_NODES_VOTE_RESULTS);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_NODES_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from NODES_TO_NODES_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from NODES_TO_NODES_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from NODES_TO_NODES_VOTE_RESULTS","red");
  }  
  if (parse_json_data(result_test,"vote_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_NODES_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vote_settings from NODES_TO_NODES_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vote_settings from NODES_TO_NODES_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vote_settings from NODES_TO_NODES_VOTE_RESULTS","red");
  }  
  if (parse_json_data(result_test,"vote_data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_NODES_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vote_data from NODES_TO_NODES_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vote_data from NODES_TO_NODES_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vote_data from NODES_TO_NODES_VOTE_RESULTS","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_NODES_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from NODES_TO_NODES_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from NODES_TO_NODES_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from NODES_TO_NODES_VOTE_RESULTS","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_NODES_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from NODES_TO_NODES_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from NODES_TO_NODES_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from NODES_TO_NODES_VOTE_RESULTS","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_NODES_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from NODES_TO_NODES_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from NODES_TO_NODES_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from NODES_TO_NODES_VOTE_RESULTS","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_NODES_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from NODES_TO_NODES_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from NODES_TO_NODES_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from NODES_TO_NODES_VOTE_RESULTS","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_NODES_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from NODES_TO_NODES_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from NODES_TO_NODES_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from NODES_TO_NODES_VOTE_RESULTS","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_NODES_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from NODES_TO_NODES_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from NODES_TO_NODES_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from NODES_TO_NODES_VOTE_RESULTS","red");
  }
  printf("\n");



  // test for parsing NODES_TO_CONSENSUS_NODE_VOTE_RESULTS
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,NODES_TO_CONSENSUS_NODE_VOTE_RESULTS);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","red");
  }  
  if (parse_json_data(result_test,"vote_result",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing vote_result from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing vote_result from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing vote_result from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","red");
  }  
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"NODES_TO_CONSENSUS_NODE_VOTE_RESULTS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from NODES_TO_CONSENSUS_NODE_VOTE_RESULTS","red");
  }
  printf("\n");



  // test for parsing CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
  }  
  if (parse_json_data(result_test,"nodes_name_list",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing nodes_name_list from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing nodes_name_list from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing nodes_name_list from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
  }  
  if (parse_json_data(result_test,"nodes_public_address_list",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing nodes_public_address_list from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing nodes_public_address_list from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing nodes_public_address_list from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES","red");
  }
  printf("\n");



  // test for parsing CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE","red");
  }
  printf("\n");



  // test for parsing CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE","red");
  }
  printf("\n");



  // test for parsing CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE","red");
  }
  printf("\n");



  // test for parsing CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  printf("\n");



  // test for parsing CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  printf("\n");



  // test for parsing CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"current_block_template_blob",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_block_template_blob from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_block_template_blob from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_block_template_blob from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  printf("\n");



  // test for parsing CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"message_data_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_data_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_data_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_data_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  printf("\n");



  // test for parsing CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND","red");
  }
  printf("\n");



  // test for parsing CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND","red");
  }
  printf("\n");



  // test for parsing CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"current_block_template_blob",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_block_template_blob from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_block_template_blob from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_block_template_blob from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_CONSENSUS_NODE_PRIVATE_KEY_CREATE_NEW_BLOCK","red");
  }
  printf("\n");



  // test for parsing CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"message_data_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_data_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_data_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_data_settings from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_PRIVATE_KEY_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  printf("\n");



  // test for parsing CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES","red");
  }
  printf("\n");



  // test for parsing VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  append_string(result_test,VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS);
  if (parse_json_data(result_test,"message_settings",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing message_settings from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing message_settings from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing message_settings from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"public_address",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing public_address from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing public_address from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing public_address from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"previous_block_hash",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing previous_block_hash from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing previous_block_hash from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing previous_block_hash from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"current_round_part",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing current_round_part_backup_node from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing current_round_part_backup_node from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing current_round_part_backup_node from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"data",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing data from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing data from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing data from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing xcash_proof_of_stake_signature from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing xcash_proof_of_stake_signature from VOTING_WEBSITE_API_PROGRAM_TO_CONSENSUS_NODE_PRIVATE_KEY_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  
  



 
 
  // write the end test message
  if (count_test == PARSE_JSON_DATA_TOTAL_TEST)
  {
    printf("\n\n");
    color_print(TEST_OUTLINE,"green");
    printf("\033[1;32mparse_json_data test - Passed test: %d, Failed test: 0\033[0m\n",PARSE_JSON_DATA_TOTAL_TEST);
    color_print(TEST_OUTLINE,"green");
    printf("\n\n");
  }
  else
  {
    printf("\n\n");
    color_print(TEST_OUTLINE,"red");
    printf("\033[1;31mparse_json_data test - Passed test: %d, Failed test: %d\033[0m\n",count_test,PARSE_JSON_DATA_TOTAL_TEST-count_test);
    color_print(TEST_OUTLINE,"red");
    printf("\n\n");
  }
  return count_test;
}


/*
-----------------------------------------------------------------------------------------------------------
Name: random_string_test
Description: Test the random_string function
Return: The number of passed random_string test
-----------------------------------------------------------------------------------------------------------
*/

int random_string_test()
{  
  // define macros
  #define RANDOM_STRING_TOTAL_TEST 1
 
  // reset the variables
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  count_test = 0;

  // write the start test message
  color_print(TEST_OUTLINE,"blue");
  printf("\033[1;34mrandom_string test - Total test: %d\033[0m\n",RANDOM_STRING_TOTAL_TEST);
  color_print(TEST_OUTLINE,"blue");
  printf("\n");

  // run the test
  if (random_string(result_test,RANDOM_STRING_LENGTH) == 1)
  {   
    color_print("PASSED! Test for creating a 100 character random string","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for creating a 100 character random string","red");
  }



  // write the end test message
  if (count_test == RANDOM_STRING_TOTAL_TEST)
  {
    printf("\n");
    color_print(TEST_OUTLINE,"green");
    printf("\033[1;32mrandom_string test - Passed test: %d, Failed test: 0\033[0m\n",RANDOM_STRING_TOTAL_TEST);
    color_print(TEST_OUTLINE,"green");
    printf("\n\n");
  }
  else
  {
    printf("\n");
    color_print(TEST_OUTLINE,"red");
    printf("\033[1;31msend_http_request_and_get_public_address test - Passed test: %d, Failed test: %d\033[0m\n",count_test,RANDOM_STRING_TOTAL_TEST-count_test);
    color_print(TEST_OUTLINE,"red");
    printf("\n\n");
  } 
  return count_test;
}



/*
-----------------------------------------------------------------------------------------------------------
Name: create_json_data_from_database_array test
Description: Test the create_json_data_from_database_array function
Return: The number of passed create_json_data_from_database_array test
-----------------------------------------------------------------------------------------------------------
*/

int create_json_data_from_database_array_test()
{  
  // define macros
  #define CREATE_JSON_DATA_FROM_DATABASE_ARRAY_TOTAL_TEST 1
  #define MESSAGE "{\"username\":\"XCASH\",\"most_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_total_rounds\":\"5\",\"best_block_verifier_online_percentage_delegate_name\":\"DELEGATE_NAME\",\"best_block_verifier_online_percentage\":\"10\",\"most_block_producer_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_block_producer_total_rounds\":\"15\",\"most_VRF_node_public_and_private_key_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_public_and_private_key_total_rounds\":\"5\",\"most_VRF_node_random_data_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_random_data_total_rounds\":\"10\",\"total_XCASH_proof_of_stake_rounds\":\"15\",\"total_coins_in_proof_of_stake\":\"5\",\"total_circulating_supply_percentage_in_proof_of_stake\":\"10\"}"

  // reset the variables
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  count_test = 0;

  // write the start test message
  color_print(TEST_OUTLINE,"blue");
  printf("\033[1;34mcreate_json_data_from_database_array_test - Total test: %d\033[0m\n",CREATE_JSON_DATA_FROM_DATABASE_ARRAY_TOTAL_TEST);
  color_print(TEST_OUTLINE,"blue");
  printf("\n");

  // run the test
  int count;
  struct database_document_fields database_data;

  // initialize the database_document_fields struct 
  for (count = 0; count < DATABASE_ARRAY_COUNT; count++)
  {
    database_data.item[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    database_data.value[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
  }

  memcpy(database_data.item[0],"username",8);
  memcpy(database_data.item[1],"most_total_rounds_delegate_name",31);
  memcpy(database_data.item[2],"most_total_rounds",17);
  memcpy(database_data.item[3],"best_block_verifier_online_percentage_delegate_name",51);
  memcpy(database_data.item[4],"best_block_verifier_online_percentage",37);
  memcpy(database_data.item[5],"most_block_producer_total_rounds_delegate_name",46);
  memcpy(database_data.item[6],"most_block_producer_total_rounds",32);
  memcpy(database_data.item[7],"most_VRF_node_public_and_private_key_total_rounds_delegate_name",63);
  memcpy(database_data.item[8],"most_VRF_node_public_and_private_key_total_rounds",49);
  memcpy(database_data.item[9],"most_VRF_node_random_data_total_rounds_delegate_name",52);
  memcpy(database_data.item[10],"most_VRF_node_random_data_total_rounds",38);
  memcpy(database_data.item[11],"total_XCASH_proof_of_stake_rounds",33);
  memcpy(database_data.item[12],"total_coins_in_proof_of_stake",29);
  memcpy(database_data.item[13],"total_circulating_supply_percentage_in_proof_of_stake",53);

  memcpy(database_data.value[0],"XCASH",5);  
  memcpy(database_data.value[1],"DELEGATE_NAME",13);
  memcpy(database_data.value[2],"5",1);
  memcpy(database_data.value[3],"DELEGATE_NAME",13);
  memcpy(database_data.value[4],"10",2);
  memcpy(database_data.value[5],"DELEGATE_NAME",13);  
  memcpy(database_data.value[6],"15",2);
  memcpy(database_data.value[7],"DELEGATE_NAME",13);  
  memcpy(database_data.value[8],"5",1);
  memcpy(database_data.value[9],"DELEGATE_NAME",13);  
  memcpy(database_data.value[10],"10",2);  
  memcpy(database_data.value[11],"15",2);
  memcpy(database_data.value[12],"5",1);
  memcpy(database_data.value[13],"10",2);

  database_data.count = 14;

  create_json_data_from_database_array(&database_data,result_test,"");
  
  if (strncmp(result_test,MESSAGE,BUFFER_SIZE) == 0)  
  {
    color_print("PASSED! Test for creating json data from a database array","green");
    count_test++;
  }
  else
  { 
    color_print("FAILED! Test for creating json data from a database array","red");
  }

  for (count = 0; count < DATABASE_ARRAY_COUNT; count++)
  {
    pointer_reset(database_data.item[count]);
    pointer_reset(database_data.value[count]);
  }



  // write the end test message
  if (count_test == CREATE_JSON_DATA_FROM_DATABASE_ARRAY_TOTAL_TEST)
  {
    printf("\n");
    color_print(TEST_OUTLINE,"green");
    printf("\033[1;32mstring_count test - Passed test: %d, Failed test: 0\033[0m\n",CREATE_JSON_DATA_FROM_DATABASE_ARRAY_TOTAL_TEST);
    color_print(TEST_OUTLINE,"green");
    printf("\n\n");
  }
  else
  {
    printf("\n");
    color_print(TEST_OUTLINE,"red");
    printf("\033[1;31mcreate_json_data_from_database_array_test - Passed test: %d, Failed test: %d\033[0m\n",count_test,CREATE_JSON_DATA_FROM_DATABASE_ARRAY_TOTAL_TEST-count_test);
    color_print(TEST_OUTLINE,"red");
    printf("\n\n");
  } 
  #undef MESSAGE
  return count_test;
}



/*
-----------------------------------------------------------------------------------------------------------
Name: string_count test
Description: Test the string_count function
Return: The number of passed string_count test
-----------------------------------------------------------------------------------------------------------
*/

/*
-----------------------------------------------------------------------------------------------------------
Name: string_count test
Description: Test the string_count function
Return: The number of passed string_count test
-----------------------------------------------------------------------------------------------------------
*/

int string_count_test()
{  
  // define macros
  #define STRING_COUNT_TOTAL_TEST 2

  // reset the variables
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  count_test = 0;

  // write the start test message
  color_print(TEST_OUTLINE,"blue");
  printf("\033[1;34mstring_count test - Total test: %d\033[0m\n",STRING_COUNT_TOTAL_TEST);
  color_print(TEST_OUTLINE,"blue");
  printf("\n");

  // run the test
  memcpy(result_test,TEST_OUTLINE,strnlen(TEST_OUTLINE,BUFFER_SIZE));

  // test for counting a byte in a string
  if (string_count(result_test,"-") == strnlen(TEST_OUTLINE,BUFFER_SIZE))  
  {
    color_print("PASSED! Test for using string_count to count occurences of a byte in a string","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for using string_count to count occurences of a byte in a string","red");
  }

  // test for counting multiple bytes in a string
  if (string_count(result_test,"--") == strnlen(TEST_OUTLINE,BUFFER_SIZE)/2)  
  {
    color_print("PASSED! Test for using string_count to count occurences of multiple bytes in a string","green");
    count_test++;
  }
  else
  { 
    color_print("FAILED! Test for using string_count to count occurences of multiple bytes a string","red");
  }



  // write the end test message
  if (count_test == STRING_COUNT_TOTAL_TEST)
  {
    printf("\n");
    color_print(TEST_OUTLINE,"green");
    printf("\033[1;32mstring_count test - Passed test: %d, Failed test: 0\033[0m\n",STRING_COUNT_TOTAL_TEST);
    color_print(TEST_OUTLINE,"green");
    printf("\n\n");
  }
  else
  {
    printf("\n");
    color_print(TEST_OUTLINE,"red");
    printf("\033[1;31mstring_count test - Passed test: %d, Failed test: %d\033[0m\n",count_test,STRING_COUNT_TOTAL_TEST-count_test);
    color_print(TEST_OUTLINE,"red");
    printf("\n\n");
  } 
  return count_test;
}



/*
-----------------------------------------------------------------------------------------------------------
Name: string_replace_test
Description: Test the string_replace function
Return: The number of passed string_replace test
-----------------------------------------------------------------------------------------------------------
*/

int string_replace_test()
{  
  // define macros
  #define STRING_REPLACE_TOTAL_TEST 4

  // reset the variables
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  count_test = 0;

  // write the start test message
  color_print(TEST_OUTLINE,"blue");
  printf("\033[1;34mstring_replace test - Total test: %d\033[0m\n",STRING_REPLACE_TOTAL_TEST);
  color_print(TEST_OUTLINE,"blue");
  printf("\n");

  // run the test
 
  // test for using string_replace to replace a string
  append_string(result_test,"{\r\n \"message_settings\": \"string_replace_test\",\r\n}");
  if (string_replace(result_test,"string_replace_test","string_replace") == 1)
  {
    if (strncmp(result_test,"{\r\n \"message_settings\": \"string_replace\",\r\n}",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for using string_replace to replace a string","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for using string_replace to replace a string","red");
    }
  }
  else
  {
    color_print("FAILED! Test for using string_replace to replace a string","red");
  }

  // test for using string_replace to replace a string with a string that has the substring of str1 in it
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  append_string(result_test,"{\r\n \"message_settings\": \"string_replace_test\",\r\n}");
  if (string_replace(result_test,"\"","\\\"") == 1)
  {
    if (strncmp(result_test,"{\r\n \\\"message_settings\\\": \\\"string_replace_test\\\",\r\n}",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for using string_replace to replace a string with a string that has the substring of str1 in it","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for using string_replace to replace a string with a string that has the substring of str1 in it","red");
    }
  }
  else
  {
    color_print("FAILED! Test for using string_replace to replace a string with a string that has the substring of str1 in it","red");
  }

  // test for using string_replace to remove a string
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  append_string(result_test,"{\r\n \"message_settings\": \"string_replace_test\",\r\n}");
  if (string_replace(result_test,"_test","") == 1)
  {
    if (strncmp(result_test,"{\r\n \"message_settings\": \"string_replace\",\r\n}",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for using string_replace to remove a string","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for using string_replace to remove a string","red");
    }
  }
  else
  {
    color_print("FAILED! Test for using string_replace to remove a string","red");
  }

  // test for using string_replace to replace a string that is not in the string
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  append_string(result_test,"{\r\n \"message_settings\": \"string_replace\",\r\n}");
  if (string_replace(result_test,"string_replace_test","") == 1)
  {    
    color_print("FAILED! Test for using string_replace to replace a string that is not in the string","red");
  }
  else
  {
    if (strncmp(result_test,"{\r\n \"message_settings\": \"string_replace\",\r\n}",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for using string_replace to replace a string that is not in the string","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for using string_replace to replace a string that is not in the string","red");
    }    
  }



  // write the end test message
  if (count_test == STRING_REPLACE_TOTAL_TEST)
  {
    printf("\n");
    color_print(TEST_OUTLINE,"green");
    printf("\033[1;32mstring_replace test - Passed test: %d, Failed test: 0\033[0m\n",STRING_REPLACE_TOTAL_TEST);
    color_print(TEST_OUTLINE,"green");
    printf("\n\n");
  }
  else
  {
    printf("\n");
    color_print(TEST_OUTLINE,"red");
    printf("\033[1;31mstring_replace test - Passed test: %d, Failed test: %d\033[0m\n",count_test,STRING_REPLACE_TOTAL_TEST-count_test);
    color_print(TEST_OUTLINE,"red");
    printf("\n\n");
  } 
  return count_test;
}



/*
-----------------------------------------------------------------------------------------------------------
Name: send_wallet_http_request_test
Description: Test the send_http_request and other HTTP request wallet functions
Return: The number of passed send_wallet_http_request test
-----------------------------------------------------------------------------------------------------------
*/

int send_wallet_http_request_test()
{  
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // define macros
  #define SEND_WALLET_HTTP_REQUEST_TOTAL_TEST 6
  #define MESSAGE "{\r\n \"message_settings\": \"XCASH_PROOF_OF_STAKE_TEST_DATA\",\r\n}"
  
  // reset the variables
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  memset(server_message,0,strnlen(server_message,BUFFER_SIZE));
  count_test = 0;

  // set the server_message
  memcpy(server_message,"XCASH_PROOF_OF_STAKE_TEST_DATA",30);

  // write the start test message
  color_print(TEST_OUTLINE,"blue");
  printf("\033[1;34msend_wallet_http_request test - Total test: %d\033[0m\n",SEND_WALLET_HTTP_REQUEST_TOTAL_TEST);
  color_print(TEST_OUTLINE,"blue");
  printf("\n");

  // run the test

  // set the current_round_part and current_round_part_backup_node
  memset(current_round_part,0,strnlen(current_round_part,BUFFER_SIZE));
  memset(current_round_part_backup_node,0,strnlen(current_round_part_backup_node,BUFFER_SIZE));
  memcpy(current_round_part,"1",1);
  memcpy(current_round_part_backup_node,"0",1);

  // test the send_http_request and get_public_address functions
  memset(xcash_wallet_public_address,0,strnlen(xcash_wallet_public_address,BUFFER_SIZE));
  if (get_public_address(0) == 1)
  {   
    color_print("PASSED! Test for sending an HTTP request and getting the public address of the opened X-CASH wallet","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for sending an HTTP request and getting the public address of the opened X-CASH wallet","red");
  }

  // test the get_block_template function
  memset(data,0,strnlen(data,BUFFER_SIZE));
  if (get_block_template(data,0) == 1)
  {   
    color_print("PASSED! Test for getting the block template","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for getting the block template","red");
  }

  // test the get_current_block_height function
  memset(data,0,strnlen(data,BUFFER_SIZE));
  if (get_current_block_height(data,0) == 1)
  {   
    color_print("PASSED! Test for getting the current block height","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for getting the current block height","red");
  }

  // test the get_previous_block_hash function
  memset(data,0,strnlen(data,BUFFER_SIZE));
  if (get_previous_block_hash(data,0) == 1)
  {   
    color_print("PASSED! Test for getting the previous block hash","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for getting the previous block hash","red");
  }
  
  // create the message
  memset(result_test,0,strlen(result_test));
  append_string(result_test,MESSAGE);

  // test the sign_data functions
  if (sign_data(result_test,0) == 1)
  {   
    color_print("PASSED! Test for sign data to send data securely","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for sign data to send data securely","red");
  }
  
  // test the verify_data functions
  if (verify_data(result_test,0,1,1) == 1)
  {   
    color_print("PASSED! Test for verify data to receive data securely","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for verify data to receive data securely","red");
  }
  


  // write the end test message
  if (count_test == SEND_WALLET_HTTP_REQUEST_TOTAL_TEST)
  {
    printf("\n");
    color_print(TEST_OUTLINE,"green");
    printf("\033[1;32msend_wallet_http_request test - Passed test: %d, Failed test: 0\033[0m\n",SEND_WALLET_HTTP_REQUEST_TOTAL_TEST);
    color_print(TEST_OUTLINE,"green");
    printf("\n\n");
  }
  else
  {
    printf("\n");
    color_print(TEST_OUTLINE,"red");
    printf("\033[1;31msend_wallet_http_request test - Passed test: %d, Failed test: %d\033[0m\n",count_test,SEND_WALLET_HTTP_REQUEST_TOTAL_TEST-count_test);
    color_print(TEST_OUTLINE,"red");
    printf("\n\n");
  } 
  pointer_reset(data);
  #undef MESSAGE
  return count_test;
}



/*
-----------------------------------------------------------------------------------------------------------
Name: read_and_write_file_test
Description: Test the read_file and write_file functions
Return: The number of passed read_and_write_file test
-----------------------------------------------------------------------------------------------------------
*/

int read_and_write_file_test()
{   
  // Variables
  pthread_t thread_id;

  // define macros
  #define READ_AND_WRITE_FILE_TEST 4
  #define NODES_PUBLIC_ADDRESS_LIST_FILE_NAME_COPY "nodes_public_address_list_copy.txt"
  #define MESSAGE "XCASH_PROOF_OF_STAKE_TEST_DATA"

  // reset the variables
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  count_test = 0;

  // write the start test message
  color_print(TEST_OUTLINE,"blue");
  printf("\033[1;34mread_and_write_file test - Total test: %d\033[0m\n",READ_AND_WRITE_FILE_TEST);
  color_print(TEST_OUTLINE,"blue");
  printf("\n");

  // run the test

  // write the file
  memcpy(data_test,MESSAGE,30);
  if (write_file(data_test,NODES_PUBLIC_ADDRESS_LIST_FILE_NAME_COPY) == 0)
  {
    color_print("FAILED! Test for writing the file","red");
  }
  else
  {
    color_print("PASSED! Test for writing the file","green");
    count_test++;
  }

  // read the file
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (read_file(data_test,NODES_PUBLIC_ADDRESS_LIST_FILE_NAME_COPY) == 0)
  {
    color_print("FAILED! Test for reading the file","red");
  }
  if (strncmp(data_test,MESSAGE,BUFFER_SIZE) != 0)
  {
    color_print("FAILED! Test for reading the file","red");
  }
  color_print("PASSED! Test for reading the file","green");
  count_test++;
  remove(NODES_PUBLIC_ADDRESS_LIST_FILE_NAME_COPY);



  // write the file using a seperate thread  
  // create a struct for the parameters
  struct write_file_thread_parameters write_file_thread_parameters = {MESSAGE,NODES_PUBLIC_ADDRESS_LIST_FILE_NAME_COPY};
  pthread_create(&thread_id, NULL, &write_file_thread,(void *)&write_file_thread_parameters);
  if (thread_settings(thread_id) == 0)
  {
    color_print("FAILED! Test for writing the file on a seperate thread","red");
  }
  else
  {
    color_print("PASSED! Test for writing the file on a seperate thread","green");
    count_test++;
  }

   // read the file
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  struct read_file_thread_parameters read_file_thread_parameters = {data_test,NODES_PUBLIC_ADDRESS_LIST_FILE_NAME_COPY};
  pthread_create(&thread_id, NULL, &read_file_thread,(void *)&read_file_thread_parameters);
  if (thread_settings(thread_id) == 0)
  {
    color_print("FAILED! Test for reading the file on a seperate thread","red");
  }
  if (strncmp(data_test,MESSAGE,BUFFER_SIZE) != 0)
  {
    color_print("FAILED! Test for reading the file on a seperate thread","red");
  }
  color_print("PASSED! Test for reading the file on a seperate thread","green");
  count_test++;
  remove(NODES_PUBLIC_ADDRESS_LIST_FILE_NAME_COPY);



  // write the end test message
  if (count_test == READ_AND_WRITE_FILE_TEST)
  {
    printf("\n");
    color_print(TEST_OUTLINE,"green");
    printf("\033[1;32mread_and_write_file test - Passed test: %d, Failed test: 0\033[0m\n",READ_AND_WRITE_FILE_TEST);
    color_print(TEST_OUTLINE,"green");
    printf("\n\n");
  }
  else
  {
    printf("\n");
    color_print(TEST_OUTLINE,"red");
    printf("\033[1;31mread_and_write_file test - Passed test: %d, Failed test: %d\033[0m\n",count_test,READ_AND_WRITE_FILE_TEST-count_test);
    color_print(TEST_OUTLINE,"red");
    printf("\n\n");
  } 
  #undef NODES_PUBLIC_ADDRESS_LIST_FILE_NAME_COPY
  #undef MESSAGE
  return count_test;
}



/*
-----------------------------------------------------------------------------------------------------------
Name: database_test
Description: Test the database functions
Return: The number of passed database test
-----------------------------------------------------------------------------------------------------------
*/

int database_test()
{   
  // Variables
  pthread_t thread_id;

  // define macros
  #define DATABASE_TEST 21
  #define DATA_COUNT 5
  #define DATABASE_COLLECTION "XCASH_PROOF_OF_STAKE_TEST_DATA"
  #define MESSAGE "{\"message_settings\": \"XCASH_PROOF_OF_STAKE_TEST_DATA\"}"
  #define MESSAGE_SETTINGS "{\"message_settings\": \"XCASH_PROOF_OF_STAKE_DATA\"}"
  #define DATABASE_COLLECTION_STATISTICS_DATA "{\"username\":\"XCASH\",\"most_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_total_rounds\":\"5\",\"best_block_verifier_online_percentage_delegate_name\":\"DELEGATE_NAME\",\"best_block_verifier_online_percentage\":\"10\",\"most_block_producer_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_block_producer_total_rounds\":\"15\",\"most_VRF_node_public_and_private_key_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_public_and_private_key_total_rounds\":\"5\",\"most_VRF_node_random_data_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_random_data_total_rounds\":\"10\",\"total_XCASH_proof_of_stake_rounds\":\"15\",\"total_coins_in_proof_of_stake\":\"5\",\"total_circulating_supply_percentage_in_proof_of_stake\":\"10\"}"

  // Variables
  char** data = (char**)calloc(DATA_COUNT * sizeof(char*),sizeof(char*));
  char** settings = (char**)calloc(DATA_COUNT * sizeof(char*),sizeof(char*));
  int count;
  
  // reset the variables
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  count_test = 0;

  // write the start test message
  color_print(TEST_OUTLINE,"blue");
  printf("\033[1;34mdatabase test - Total test: %d\033[0m\n",DATABASE_TEST);
  color_print(TEST_OUTLINE,"blue");
  printf("\n");

  // run the test

  // initialize the arrays
  for (count = 0; count < DATA_COUNT; count++)
  {
    data[count] = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
    settings[count] = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  }

  // create the the arrays
  for (count = 0; count < DATA_COUNT; count++)
  {
    sprintf(data[count],"%d",count);
    sprintf(settings[count],"%d",count);
  }

  // insert a document into the collection using arrays
  if (insert_document_into_collection_array(DATABASE_NAME,DATABASE_COLLECTION,data,settings,DATA_COUNT) == 0)
  {
    color_print("FAILED! Test for inserting a document into a collection using an array","red");
  }
  else
  {
    color_print("PASSED! Test for inserting a document into a collection using an array","green");
    count_test++;
  }

  for (count = 0; count < DATA_COUNT; count++)
  {
    pointer_reset(data[count]);
    pointer_reset(settings[count]);
  }
  pointer_reset(data);
  pointer_reset(settings);
  
  // insert a document into the collection using json data
  if (insert_document_into_collection_json(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,0) == 0)
  {
    color_print("FAILED! Test for inserting a document into a collection using json data","red");
  }
  else
  {
    color_print("PASSED! Test for inserting a document into a collection using json data","green");
    count_test++;
  }  

  // update a document in the collection
  if (update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,MESSAGE_SETTINGS,0) == 0)
  {
    color_print("FAILED! Test for updating a document in a collection","red");
  }
  else
  {
    color_print("PASSED! Test for updating a document in a collection","green");
    count_test++;
  }

  // insert a document into the collection using json data on a separate thread
  struct insert_document_into_collection_json_thread_parameters insert_document_into_collection_json_thread_parameters = {DATABASE_NAME,DATABASE_COLLECTION,MESSAGE};
  pthread_create(&thread_id, NULL, &insert_document_into_collection_json_thread,(void *)&insert_document_into_collection_json_thread_parameters);
  if (thread_settings(thread_id) == 0)
  {
    color_print("FAILED! Test for inserting a document into a collection using json data on a separate thread","red");
  }
  else
  {
    color_print("PASSED! Test for inserting a document into a collection using json data on a separate thread","green");
    count_test++;
  }

  // update a document in the collection on a separate thread
  struct update_document_from_collection_thread_parameters update_document_from_collection_thread_parameters = {DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,MESSAGE_SETTINGS};
  pthread_create(&thread_id, NULL, &update_document_from_collection_thread,(void *)&update_document_from_collection_thread_parameters);
  if (thread_settings(thread_id) == 0)
  {
    color_print("FAILED! Test for updating a document in a collection on a separate thread","red");
  }
  else
  {
    color_print("PASSED! Test for updating a document in a collection on a separate thread","green");
    count_test++;
  }

  // read a document in the collection
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (read_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE_SETTINGS,data_test,0) == 1)
  {
    if (strstr(data_test,"XCASH_PROOF_OF_STAKE_DATA") != NULL)
    {
      color_print("PASSED! Test for reading a document from a collection","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for reading a document from a collection","red");
    }    
  }
  else
  {
    color_print("FAILED! Test for reading a document from a collection","red");
  }

  // read a document in the collection on a separate thread
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  struct read_document_from_collection_thread_parameters read_document_from_collection_thread_parameters = {DATABASE_NAME,DATABASE_COLLECTION,MESSAGE_SETTINGS,data_test};
  pthread_create(&thread_id, NULL, &read_document_from_collection_thread,(void *)&read_document_from_collection_thread_parameters);
  if (thread_settings(thread_id) == 1)
  {
    if (strstr(data_test,"XCASH_PROOF_OF_STAKE_DATA") != NULL)
    {
      color_print("PASSED! Test for reading a document on a separate thread","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for reading a document on a separate thread","red");
    }    
  }
  else
  {
    color_print("FAILED! Test for reading a document on a separate thread","red");
  }

  // read a document in the collection and parse a field
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (read_document_field_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE_SETTINGS,"message_settings",data_test,0) == 1)
  {
    if (strncmp(data_test,"XCASH_PROOF_OF_STAKE_DATA",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for reading a document from a collection and parsing a field","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for reading a document from a collection and parsing a field","red");
    }    
  }
  else
  {
    color_print("FAILED! Test for reading a document from a collection and parsing a field","red");
  }

  // read a document in the collection and parse a field on a separate thread
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  struct read_document_field_from_collection_thread_parameters read_document_field_from_collection_thread_parameters = {DATABASE_NAME,DATABASE_COLLECTION,MESSAGE_SETTINGS,"message_settings",data_test};
  pthread_create(&thread_id, NULL, &read_document_field_from_collection_thread,(void *)&read_document_field_from_collection_thread_parameters);
  if (thread_settings(thread_id) == 1)
  {
    if (strncmp(data_test,"XCASH_PROOF_OF_STAKE_DATA",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for reading a document from a collection and parsing a field on a separate thread","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for reading a document from a collection and parsing a field on a separate thread","red");
    }    
  }
  else
  {
    color_print("FAILED! Test for reading a document from a collection and parsing a field on a separate thread","red");
  }

  // read a document in the collection and parse all fields
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  delete_collection_from_database(DATABASE_NAME,DATABASE_COLLECTION,0);
  insert_document_into_collection_json(DATABASE_NAME,DATABASE_COLLECTION,DATABASE_COLLECTION_STATISTICS_DATA,0);
  struct database_document_fields database_data;

  // initialize the database_document_fields struct 
  for (count = 0; count < DATABASE_ARRAY_COUNT; count++)
  {
    database_data.item[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    database_data.value[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
  }

  if (read_document_all_fields_from_collection(DATABASE_NAME,DATABASE_COLLECTION,"{\"username\":\"XCASH\"}",&database_data,0) == 1)
  {
    if (strncmp(database_data.item[0],"username",BUFFER_SIZE) == 0 && strncmp(database_data.value[0],"XCASH",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[1],"most_total_rounds_delegate_name",BUFFER_SIZE) == 0 && strncmp(database_data.value[1],"DELEGATE_NAME",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[2],"most_total_rounds",BUFFER_SIZE) == 0 && strncmp(database_data.value[2],"5",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[3],"best_block_verifier_online_percentage_delegate_name",BUFFER_SIZE) == 0 && strncmp(database_data.value[3],"DELEGATE_NAME",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[4],"best_block_verifier_online_percentage",BUFFER_SIZE) == 0 && strncmp(database_data.value[4],"10",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[5],"most_block_producer_total_rounds_delegate_name",BUFFER_SIZE) == 0 && strncmp(database_data.value[5],"DELEGATE_NAME",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[6],"most_block_producer_total_rounds",BUFFER_SIZE) == 0 && strncmp(database_data.value[6],"15",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[7],"most_VRF_node_public_and_private_key_total_rounds_delegate_name",BUFFER_SIZE) == 0 && strncmp(database_data.value[7],"DELEGATE_NAME",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[8],"most_VRF_node_public_and_private_key_total_rounds",BUFFER_SIZE) == 0 && strncmp(database_data.value[8],"5",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[9],"most_VRF_node_random_data_total_rounds_delegate_name",BUFFER_SIZE) == 0 && strncmp(database_data.value[9],"DELEGATE_NAME",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[10],"most_VRF_node_random_data_total_rounds",BUFFER_SIZE) == 0 && strncmp(database_data.value[10],"10",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[11],"total_XCASH_proof_of_stake_rounds",BUFFER_SIZE) == 0 && strncmp(database_data.value[11],"15",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[12],"total_coins_in_proof_of_stake",BUFFER_SIZE) == 0 && strncmp(database_data.value[12],"5",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[13],"total_circulating_supply_percentage_in_proof_of_stake",BUFFER_SIZE) == 0 && strncmp(database_data.value[13],"10",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for reading a document from a collection and parsing all fields","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for reading a document from a collection and parsing all fields","red");
    }    
  }
  else
  {
    color_print("FAILED! Test for reading a document from a collection and parsing all fields","red");
  }

  for (count = 0; count < DATABASE_ARRAY_COUNT; count++)
  {
    pointer_reset(database_data.item[count]);
    pointer_reset(database_data.value[count]);
  }

  // read a document in the collection and parse all fields on a separate thread
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  delete_collection_from_database(DATABASE_NAME,DATABASE_COLLECTION,0);
  insert_document_into_collection_json(DATABASE_NAME,DATABASE_COLLECTION,DATABASE_COLLECTION_STATISTICS_DATA,0);
  
  // initialize the database_document_fields struct 
  for (count = 0; count < DATABASE_ARRAY_COUNT; count++)
  {
    database_data.item[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    database_data.value[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
  }

  struct read_document_all_fields_from_collection_thread_parameters read_document_all_fields_from_collection_thread_parameters = {DATABASE_NAME,DATABASE_COLLECTION,"{\"username\":\"XCASH\"}",&database_data};
  pthread_create(&thread_id, NULL, &read_document_all_fields_from_collection_thread,(void *)&read_document_all_fields_from_collection_thread_parameters);
  if (thread_settings(thread_id) == 1)
  {
    if (read_document_all_fields_from_collection(DATABASE_NAME,DATABASE_COLLECTION,"{\"username\":\"XCASH\"}",&database_data,0) == 1)
    {
      if (strncmp(database_data.item[0],"username",BUFFER_SIZE) == 0 && strncmp(database_data.value[0],"XCASH",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[1],"most_total_rounds_delegate_name",BUFFER_SIZE) == 0 && strncmp(database_data.value[1],"DELEGATE_NAME",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[2],"most_total_rounds",BUFFER_SIZE) == 0 && strncmp(database_data.value[2],"5",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[3],"best_block_verifier_online_percentage_delegate_name",BUFFER_SIZE) == 0 && strncmp(database_data.value[3],"DELEGATE_NAME",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[4],"best_block_verifier_online_percentage",BUFFER_SIZE) == 0 && strncmp(database_data.value[4],"10",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[5],"most_block_producer_total_rounds_delegate_name",BUFFER_SIZE) == 0 && strncmp(database_data.value[5],"DELEGATE_NAME",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[6],"most_block_producer_total_rounds",BUFFER_SIZE) == 0 && strncmp(database_data.value[6],"15",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[7],"most_VRF_node_public_and_private_key_total_rounds_delegate_name",BUFFER_SIZE) == 0 && strncmp(database_data.value[7],"DELEGATE_NAME",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[8],"most_VRF_node_public_and_private_key_total_rounds",BUFFER_SIZE) == 0 && strncmp(database_data.value[8],"5",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[9],"most_VRF_node_random_data_total_rounds_delegate_name",BUFFER_SIZE) == 0 && strncmp(database_data.value[9],"DELEGATE_NAME",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[10],"most_VRF_node_random_data_total_rounds",BUFFER_SIZE) == 0 && strncmp(database_data.value[10],"10",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[11],"total_XCASH_proof_of_stake_rounds",BUFFER_SIZE) == 0 && strncmp(database_data.value[11],"15",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[12],"total_coins_in_proof_of_stake",BUFFER_SIZE) == 0 && strncmp(database_data.value[12],"5",BUFFER_SIZE) == 0 &&
        strncmp(database_data.item[13],"total_circulating_supply_percentage_in_proof_of_stake",BUFFER_SIZE) == 0 && strncmp(database_data.value[13],"10",BUFFER_SIZE) == 0)
      {
        color_print("PASSED! Test for reading a document from a collection and parsing all fields","green");
        count_test++;
      }
      else
      {
        color_print("FAILED! Test for reading a document from a collection and parsing all fields","red");
      }    
    }
    else
    {
      color_print("FAILED! Test for reading a document from a collection and parsing all fields","red");
    }
  }
  else
  {
    color_print("FAILED! Test for reading a document from a collection and parsing all fields","red");
  }

  for (count = 0; count < DATABASE_ARRAY_COUNT; count++)
  {
    pointer_reset(database_data.item[count]);
    pointer_reset(database_data.value[count]);
  }

  // update all document in the collection
  if (update_all_documents_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,0) == 0)
  {
    color_print("FAILED! Test for updating all documents in a collection","red");
  }
  else
  {
    color_print("PASSED! Test for updating all documents in a collection","green");
    count_test++;
  }

  // update all document in the collection on a separate thread
  struct update_all_documents_from_collection_thread_parameters update_all_documents_from_collection_thread_parameters = {DATABASE_NAME,DATABASE_COLLECTION,MESSAGE};
  pthread_create(&thread_id, NULL, &update_all_documents_from_collection_thread,(void *)&update_all_documents_from_collection_thread_parameters);
  if (thread_settings(thread_id) == 0)
  {
    color_print("FAILED! Test for updating all documents in a collection on a separate thread","red");
  }
  else
  {
    color_print("PASSED! Test for updating all documents in a collection on a separate thread","green");
    count_test++;
  }

  // count how many documents have "message_settings":"XCASH_PROOF_OF_STAKE_TEST_DATA" in the collection
  int count1 = count_documents_in_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,0);
  int count2 = count_all_documents_in_collection(DATABASE_NAME,DATABASE_COLLECTION,0);
  if ((count1 == count2) && (count1 != -1 || count2 != -1))
  {
    color_print("PASSED! Test for counting documents in a collection that match a specific field name and field","green");
    color_print("PASSED! Test for counting all documents in a collection","green");
    count_test+= 2;   
  }
  else
  {
     color_print("FAILED! Test for counting documents in a collection that match a specific field name and field","red");
     color_print("FAILED! Test for counting all documents in a collection","red");
  }

  // count how many documents have "message_settings":"XCASH_PROOF_OF_STAKE_TEST_DATA" in the collection on a separate thread
  struct count_documents_in_collection_thread_parameters count_documents_in_collection_thread_parameters = {DATABASE_NAME,DATABASE_COLLECTION,MESSAGE};
  pthread_create(&thread_id, NULL, &count_documents_in_collection_thread,(void *)&count_documents_in_collection_thread_parameters);
  count1 = thread_settings(thread_id);
  struct count_all_documents_in_collection_thread_parameters count_all_documents_in_collection_thread_parameters = {DATABASE_NAME,DATABASE_COLLECTION};
  pthread_create(&thread_id, NULL, &count_all_documents_in_collection_thread,(void *)&count_all_documents_in_collection_thread_parameters);
  count2 = thread_settings(thread_id);
  if ((count1 == count2) && (count1 != -1 || count2 != -1))
  {
    color_print("PASSED! Test for counting documents in a collection that match a specific field name and field on a separate thread","green");
    color_print("PASSED! Test for counting all documents in a collection on a separate thread","green");
    count_test+= 2;   
  }
  else
  {
     color_print("FAILED! Test for counting documents in a collection that match a specific field name and field on a separate thread","red");
     color_print("FAILED! Test for counting all documents in a collection on a separate thread","red");
  }

  // delete a document from the collection
  if (delete_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,0) == 0)
  {
    color_print("FAILED! Test for deleting a document from a collection","red");
  }
  else
  {
    color_print("PASSED! Test for deleting a document from a collection","green");
    count_test++;
  }

  // delete a document from the collection on a separate thread
  if (insert_document_into_collection_json(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,0) == 0)
  {
    color_print("FAILED! Test for deleting a document from a collection on a separate thread","red");
  }
  else
  {
    struct delete_document_from_collection_thread_parameters delete_document_from_collection_thread_parameters = {DATABASE_NAME,DATABASE_COLLECTION,MESSAGE};
    pthread_create(&thread_id, NULL, &delete_document_from_collection_thread,(void *)&delete_document_from_collection_thread_parameters);
    if (thread_settings(thread_id) == 0)
    {
      color_print("FAILED! Test for deleting a document from a collection on a separate thread","red");
    }
    else
    {
      color_print("PASSED! Test for deleting a document from a collection on a separate thread","green");
      count_test++;
    }
  }  

  // delete a collection from the database
  if (delete_collection_from_database(DATABASE_NAME,DATABASE_COLLECTION,0) == 0)
  {
    color_print("FAILED! Test for deleting a collection from a database","red");
  }
  else
  {
    color_print("PASSED! Test for deleting a collection from a database","green");
    count_test++;
  }

  // delete a collection from the database on a separate thread
  if (insert_document_into_collection_json(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,0) == 0)
  {
    color_print("FAILED! Test for deleting a collection from a database on a separate thread","red");
  }
  else
  {
    struct delete_collection_from_database_thread_parameters delete_collection_from_database_thread_parameters = {DATABASE_NAME,DATABASE_COLLECTION};
    pthread_create(&thread_id, NULL, &delete_collection_from_database_thread,(void *)&delete_collection_from_database_thread_parameters);
    if (thread_settings(thread_id) == 0)
    {
      color_print("FAILED! Test for deleting a collection from a database on a separate thread","red");
    }
    else
    {
      color_print("PASSED! Test for deleting a collection from a database on a separate thread","green");
      count_test++;
    }  
  }

/*delete_collection_from_database(DATABASE_NAME,"delegates",0);
  delete_collection_from_database(DATABASE_NAME,"statistics",0);
  insert_document_into_collection_json(DATABASE_NAME,"delegates","{\"public_address\":\"XCA\",\"password\":\"XCA\",\"salt\":\"XCA\",\"session\":\"XCA\",\"total_vote_count\":\"XCA\",\"current_vote_count\":\"XCA\",\"delegate_number\":\"XCA\",\"IP_address\":\"XCA\",\"delegate_name\":\"XCA\",\"about\":\"XCA\",\"website\":\"XCA\",\"team\":\"XCA\",\"pool_mode\":\"XCA\",\"fee_structure\":\"XCA\",\"server_settings\":\"XCA\",\"block_producer_eligibility\":\"XCA\",\"block_verifier_total_rounds\":\"XCA\",\"block_verifier_online_total_rounds\":\"XCA\",\"block_verifier_online_percentage\":\"XCA\",\"block_producer_total_rounds\":\"XCA\",\"VRF_node_public_and_private_key_total_rounds\":\"XCA\",\"VRF_node_random_data_total_rounds\":\"XCA\",\"block_producer_block_heights\":\"XCA\",\"VRF_node_public_and_private_key_block_heights\":\"XCA\",\"VRF_node_random_data_block_heights\":\"XCA\"}",0);
  insert_document_into_collection_json(DATABASE_NAME,"statistics",DATABASE_COLLECTION_STATISTICS_DATA,0);*/
  
  // write the end test message
  if (count_test == DATABASE_TEST)
  {
    printf("\n");
    color_print(TEST_OUTLINE,"green");
    printf("\033[1;32mdatabase test - Passed test: %d, Failed test: 0\033[0m\n",DATABASE_TEST);
    color_print(TEST_OUTLINE,"green");
    printf("\n\n");
  }
  else
  {
    printf("\n");
    color_print(TEST_OUTLINE,"red");
    printf("\033[1;31mdatabase test - Passed test: %d, Failed test: %d\033[0m\n",count_test,DATABASE_TEST-count_test);
    color_print(TEST_OUTLINE,"red");
    printf("\n\n");
  } 

  #undef MESSAGE
  #undef MESSAGE_SETTINGS
  #undef DATABASE_COLLECTION
  #undef DATA_COUNT
  return count_test;
}



/*
-----------------------------------------------------------------------------------------------------------
Name: create_server_on_separate_thread
Description: Creates the server on a separate thread
Return: NULL
-----------------------------------------------------------------------------------------------------------
*/

void* create_server_on_separate_thread()
{
  create_server(0);
  return NULL;
}



/*
-----------------------------------------------------------------------------------------------------------
Name: send_and_receive_data_socket_test
Description: Test the create_server, send_and_receive_data_socket, send_data, receive_data functions
Return: The number of passed send_and_receive_data_socket test
-----------------------------------------------------------------------------------------------------------
*/

int send_and_receive_data_socket_test()
{   
  // Variables
  char* message = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* public_address = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* string = (char*)calloc(BUFFER_SIZE,sizeof(char));
  int settings = 1;
  pthread_t thread_id;

  // define macros
  #define SEND_AND_RECEIVE_DATA_SOCKET_TOTAL_TEST 2
  #define MESSAGE "{\r\n \"message_settings\": \"XCASH_PROOF_OF_STAKE_TEST_DATA\",\r\n}"

  // reset the variables
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  memset(server_message,0,strnlen(server_message,BUFFER_SIZE));
  count_test = 0;

  // set the server_message
  memcpy(server_message,"XCASH_PROOF_OF_STAKE_TEST_DATA",30);

  // write the start test message
  color_print(TEST_OUTLINE,"blue");
  printf("\033[1;34msend data socket test - Total test: %d\033[0m\n",SEND_AND_RECEIVE_DATA_SOCKET_TOTAL_TEST);
  color_print(TEST_OUTLINE,"blue");
  printf("\n");

  // run the test

  // set the current_round_part and current_round_part_backup_node
  memset(current_round_part,0,strnlen(current_round_part,BUFFER_SIZE));
  memset(current_round_part_backup_node,0,strnlen(current_round_part_backup_node,BUFFER_SIZE));
  memcpy(current_round_part,"1",1);
  memcpy(current_round_part_backup_node,"0",1); 
  
  // test for creating the server
  if (pthread_create(&thread_id, NULL, &create_server_on_separate_thread,NULL) != 0)
  {
    color_print("FAILED! Test for creating the server","red");
    color_print("FAILED! Test for sending and receving data using sockets","red");
    settings = 0;
  }
  if (settings == 1)
  {
    if (pthread_detach(thread_id) != 0)
    {      
      color_print("FAILED! Test for creating the server","red");
      color_print("FAILED! Test for sending and receving data using sockets","red");
      settings = 0;
    }  
  }
  sleep(1);



  // test for sending and receiving data using sockets
  // create the message
  memset(message,0,strlen(message));
  append_string(message,MESSAGE);

  // sign_data
  if (settings == 1)
  {
    if (sign_data(message,0) == 0)
    { 
      color_print("FAILED! Test for creating the server","red");
      color_print("FAILED! Test for sending and receving data using sockets","red");
    }
  }
 
  if (settings == 1)
  {
    if (send_and_receive_data_socket(string,"127.0.0.1",SEND_DATA_PORT,message,TOTAL_CONNECTION_TIME_SETTINGS,"XCASH_PROOF_OF_STAKE_TEST_DATA",0) <= 0)
    {
      color_print("FAILED! Test for creating the server","red");
      color_print("FAILED! Test for sending and receving data using sockets","red");
      settings = 0;
    }
  }
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));

  // verify the message
  if (settings == 1)
  {
    if (verify_data(string,0,1,1) == 0)
    {   
      color_print("FAILED! Test for creating the server","red");
      color_print("FAILED! Test for sending and receving data using sockets","red");
      settings = 0;
    }
  }

  // parse the data
  if (settings == 1)
  {
    if (parse_json_data(string,"message_settings",data_test) == 0)
    {
      color_print("FAILED! Test for creating the server","red");
      color_print("FAILED! Test for sending and receving data using sockets","red");
      settings = 0;
    }
  }
  
  // check if the received data is correct
  if (settings == 1)
  {
    if (strncmp(data_test,"XCASH_PROOF_OF_STAKE_TEST_DATA",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for creating the server","green");
      color_print("PASSED! Test for sending and receving data using sockets","green");
      count_test += 2;
    }
    else
    {
      color_print("FAILED! Test for creating the server","red");
      color_print("FAILED! Test for sending and receving data using sockets","red");
      settings = 0;
    }
  }



  // write the end test message
  if (count_test == SEND_AND_RECEIVE_DATA_SOCKET_TOTAL_TEST)
  {
    printf("\n");
    color_print(TEST_OUTLINE,"green");
    printf("\033[1;32msend_and_receive_data_socket_test - Passed test: %d, Failed test: 0\033[0m\n",SEND_AND_RECEIVE_DATA_SOCKET_TOTAL_TEST);
    color_print(TEST_OUTLINE,"green");
    printf("\n\n");
  }
  else
  {
    printf("\n");
    color_print(TEST_OUTLINE,"red");
    printf("\033[1;31msend_and_receive_data_socket_test - Passed test: %d, Failed test: %d\033[0m\n",count_test,SEND_AND_RECEIVE_DATA_SOCKET_TOTAL_TEST-count_test);
    color_print(TEST_OUTLINE,"red");
    printf("\n\n");
  } 
  pointer_reset(message);
  pointer_reset(public_address);
  pointer_reset(string);
  #undef MESSAGE
  return count_test;
}



/*
-----------------------------------------------------------------------------------------------------------
Name: test
Description: Run the test
-----------------------------------------------------------------------------------------------------------
*/

void test()
{
  // Variables
  int xcash_proof_of_stake_total_passed_test = 0;

  // define macros
  #define XCASH_PROOF_OF_STAKE_TOTAL_TEST 272

  // write the test message
  printf("Starting Test\n\n");

  // initialize the variables
  string2_test = (char*)calloc(BUFFER_SIZE,sizeof(char));
  result_test = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  data_test = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // run the tests
  xcash_proof_of_stake_total_passed_test += append_string_test();
  xcash_proof_of_stake_total_passed_test += parse_json_data_test();
  xcash_proof_of_stake_total_passed_test += random_string_test();
  xcash_proof_of_stake_total_passed_test += create_json_data_from_database_array_test();   
  xcash_proof_of_stake_total_passed_test += string_count_test(); 
  xcash_proof_of_stake_total_passed_test += string_replace_test(); 
  xcash_proof_of_stake_total_passed_test += send_wallet_http_request_test(); 
  xcash_proof_of_stake_total_passed_test += read_and_write_file_test(); 
  xcash_proof_of_stake_total_passed_test += database_test(); 
  xcash_proof_of_stake_total_passed_test += send_and_receive_data_socket_test();
  


  // write the end test message
  if (xcash_proof_of_stake_total_passed_test == XCASH_PROOF_OF_STAKE_TOTAL_TEST)
  {
    printf("\n");
    color_print(TEST_OUTLINE,"green");
    printf("\033[1;32mX-CASH proof of stake test results - Passed test: %d, Failed test: 0\033[0m\n",XCASH_PROOF_OF_STAKE_TOTAL_TEST);
    color_print(TEST_OUTLINE,"green");
    printf("\n\n");
  }
  else
  {
    printf("\n");
    color_print(TEST_OUTLINE,"red");
    printf("\033[1;31mX-CASH proof of stake test results - Passed test: %d, Failed test: %d\033[0m\n",xcash_proof_of_stake_total_passed_test,XCASH_PROOF_OF_STAKE_TOTAL_TEST-xcash_proof_of_stake_total_passed_test);
    color_print(TEST_OUTLINE,"red");
    printf("\n\n");
  }

  pointer_reset(string2_test);
  pointer_reset(result_test);
  pointer_reset(data_test);
  return;
}