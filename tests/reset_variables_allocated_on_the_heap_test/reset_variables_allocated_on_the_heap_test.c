#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include "network_daemon_functions.h"
#include "network_functions.h"
#include "network_security_functions.h"
#include "network_wallet_functions.h"
#include "blockchain_functions.h"
#include "server_functions.h"
#include "string_functions.h"
#include "thread_functions.h"
#include "vrf.h"
#include "crypto_vrf.h"
#include "VRF_functions.h"
#include "sha512EL.h"

#include "define_macros_test.h"
#include "variables_test.h"
#include "network_functions_test.h"
#include "reset_variables_allocated_on_the_heap_test.h"

/*
-----------------------------------------------------------------------------------------------------------
Functions
-----------------------------------------------------------------------------------------------------------
*/

/*
-----------------------------------------------------------------------------------------------------------
Name: get_program_memory_usage
Description: Gets the current memory usage of the program
Parameters:
   process_id_file - The file to read the memory usage from
Return: 0 if an error has occured, otherwise the programs memory usage in KB
-----------------------------------------------------------------------------------------------------------
*/

size_t get_program_memory_usage(char* process_id_file)
{
  // Variables
  FILE* file;
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t programs_memory_usage = 0;

  if (data == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // read the current system memory usage
  file = fopen(process_id_file,"r");
  if (file != NULL)
  {
    while(fgets(data,BUFFER_SIZE,file) != NULL)
    {
      if (strstr(data,"VmSize:") != NULL)
      {
        string_replace(data,"VmSize:","");
        string_replace(data,"	",""); // tab
        string_replace(data," ",""); // space
        string_replace(data,"kB","");
        string_replace(data,"\n","");
        programs_memory_usage = atoi(data);
      }
      memset(data,0,strnlen(data,BUFFER_SIZE));
    }
    fclose(file);
  }
  pointer_reset(data);
  return programs_memory_usage;
}



/*
-----------------------------------------------------------------------------------------------------------
Name: reset_variables_allocated_on_the_heap_test
Description: Test each function to make sure that the variables are reset that were allocated on the heap
Return: The number of passed reset_variables_allocated_on_the_heap test
-----------------------------------------------------------------------------------------------------------
*/

int reset_variables_allocated_on_the_heap_test()
{
  // Constants
  const char STR1_TEST [BUFFER_SIZE] = "test string 1";
  const char* STR2_TEST = "test string 2";
  const unsigned char data2[crypto_vrf_SEEDBYTES] = {0x4c,0xcd,0x08,0x9b,0x28,0xff,0x96,0xda,0x9d,0xb6,0xc3,0x46,0xec,0x11,0x4e,0x0f,0x5b,0x8a,0x31,0x9f,0x35,0xab,0xa6,0x24,0xda,0x8c,0xf6,0xed,0x4f,0xb8,0xa6,0xfb};
  const unsigned char public_key[crypto_vrf_PUBLICKEYBYTES] = {0x3d,0x40,0x17,0xc3,0xe8,0x43,0x89,0x5a,0x92,0xb7,0x0a,0xa7,0x4d,0x1b,0x7e,0xbc,0x9c,0x98,0x2c,0xcf,0x2e,0xc4,0x96,0x8c,0xc0,0xcd,0x55,0xf1,0x2a,0xf4,0x66,0x0c};
  const unsigned char proof[crypto_vrf_PROOFBYTES] = {0xae,0x5b,0x66,0xbd,0xf0,0x4b,0x4c,0x01,0x0b,0xfe,0x32,0xb2,0xfc,0x12,0x6e,0xad,0x21,0x07,0xb6,0x97,0x63,0x4f,0x6f,0x73,0x37,0xb9,0xbf,0xf8,0x78,0x5e,0xe1,0x11,0x20,0x00,0x95,0xec,0xe8,0x7d,0xde,0x4d,0xbe,0x87,0x34,0x3f,0x6d,0xf3,0xb1,0x07,0xd9,0x17,0x98,0xc8,0xa7,0xeb,0x12,0x45,0xd3,0xbb,0x9c,0x5a,0xaf,0xb0,0x93,0x35,0x8c,0x13,0xe6,0xae,0x11,0x11,0xa5,0x57,0x17,0xe8,0x95,0xfd,0x15,0xf9,0x9f,0x07};
  const unsigned char alpha_string[1] = {"\x72"};
  const unsigned char beta_string[crypto_vrf_OUTPUTBYTES] = {0x94,0xf4,0x48,0x7e,0x1b,0x2f,0xec,0x95,0x43,0x09,0xef,0x12,0x89,0xec,0xb2,0xe1,0x50,0x43,0xa2,0x46,0x1e,0xcc,0x7b,0x2a,0xe7,0xd4,0x47,0x06,0x07,0xef,0x82,0xeb,0x1c,0xfa,0x97,0xd8,0x49,0x91,0xfe,0x4a,0x7b,0xfd,0xfd,0x71,0x56,0x06,0xbc,0x27,0xe2,0x96,0x7a,0x6c,0x55,0x7c,0xfb,0x58,0x75,0x87,0x9b,0x67,0x17,0x40,0xb7,0xd8};


  // Variables
  char* process_id_file = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char** data = (char**)calloc(5 * sizeof(char*),sizeof(char*));
  char** settings = (char**)calloc(5 * sizeof(char*),sizeof(char*));
  int previous_system_memory_usage = 0;
  int current_system_memory_usage = 0;
  int current_memory_usage = 0;
  size_t count = 0;
  size_t count2 = 0;
  size_t counter = 0;
  struct database_document_fields database_data;
  struct database_multiple_documents_fields database_multiple_documents_fields;
  unsigned char vrf_public_key[crypto_vrf_PUBLICKEYBYTES];
  unsigned char vrf_secret_key[crypto_vrf_SECRETKEYBYTES];
  unsigned char vrf_proof[crypto_vrf_PROOFBYTES];
  unsigned char vrf_beta[crypto_vrf_OUTPUTBYTES];
  pthread_t thread_id;
  int settings2 = 1;

  // define macros
  #define RESET_VARAIBLES_ALLOCATED_ON_THE_HEAP_TEST 26
  #define GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA "{\r\n  \"id\": \"0\",\r\n  \"jsonrpc\": \"2.0\",\r\n  \"result\": {\r\n    \"blockhashing_blob\": \"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\",\r\n    \"blocktemplate_blob\": \"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\",\r\n    \"difficulty\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,\r\n    \"expected_reward\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,\r\n    \"height\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,\r\n    \"prev_hash\": \"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\",\r\n    \"reserved_offset\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,\r\n    \"status\": \"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\",\r\n    \"untrusted\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\r\n  }\r\n}"
  #define DATA1 "{\"username\":\"XCASH\",\"most_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_total_rounds\":\"5\",\"best_block_verifier_online_percentage_delegate_name\":\"DELEGATE_NAME\",\"best_block_verifier_online_percentage\":\"10\",\"most_block_producer_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_block_producer_total_rounds\":\"15\",\"most_VRF_node_public_and_private_key_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_public_and_private_key_total_rounds\":\"5\",\"most_VRF_node_random_data_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_random_data_total_rounds\":\"10\",\"total_XCASH_proof_of_stake_rounds\":\"15\",\"total_coins_in_proof_of_stake\":\"5\",\"total_circulating_supply_percentage_in_proof_of_stake\":\"10\"}"
  #define DATA2 "[{\"username\":\"XCASH\",\"most_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_total_rounds\":\"5\",\"best_block_verifier_online_percentage_delegate_name\":\"DELEGATE_NAME\",\"best_block_verifier_online_percentage\":\"10\",\"most_block_producer_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_block_producer_total_rounds\":\"15\",\"most_VRF_node_public_and_private_key_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_public_and_private_key_total_rounds\":\"5\",\"most_VRF_node_random_data_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_random_data_total_rounds\":\"10\",\"total_XCASH_proof_of_stake_rounds\":\"15\",\"total_coins_in_proof_of_stake\":\"5\",\"total_circulating_supply_percentage_in_proof_of_stake\":\"10\"},{\"username\":\"XCASH\",\"most_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_total_rounds\":\"5\",\"best_block_verifier_online_percentage_delegate_name\":\"DELEGATE_NAME\",\"best_block_verifier_online_percentage\":\"10\",\"most_block_producer_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_block_producer_total_rounds\":\"15\",\"most_VRF_node_public_and_private_key_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_public_and_private_key_total_rounds\":\"5\",\"most_VRF_node_random_data_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_random_data_total_rounds\":\"10\",\"total_XCASH_proof_of_stake_rounds\":\"15\",\"total_coins_in_proof_of_stake\":\"5\",\"total_circulating_supply_percentage_in_proof_of_stake\":\"10\"}]" 
  #define DATABASE_COLLECTION "XCASH_PROOF_OF_STAKE_TEST_DATA"
  #define MESSAGE "{\"message_settings\": \"XCASH_PROOF_OF_STAKE_TEST_DATA\"}"
  #define MESSAGE_SETTINGS "{\"message_settings\": \"XCASH_PROOF_OF_STAKE_DATA\"}"
  #define DATABASE_COLLECTION_STATISTICS_DATA "{\"username\":\"XCASH\",\"most_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_total_rounds\":\"5\",\"best_block_verifier_online_percentage_delegate_name\":\"DELEGATE_NAME\",\"best_block_verifier_online_percentage\":\"10\",\"most_block_producer_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_block_producer_total_rounds\":\"15\",\"most_VRF_node_public_and_private_key_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_public_and_private_key_total_rounds\":\"5\",\"most_VRF_node_random_data_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_random_data_total_rounds\":\"10\",\"total_XCASH_proof_of_stake_rounds\":\"15\",\"total_coins_in_proof_of_stake\":\"5\",\"total_circulating_supply_percentage_in_proof_of_stake\":\"10\"}"
  #define DATABASE_COLLECTION_DELEGATES_DATA "{\"public_address\":\"XCA\",\"password\":\"XCA\",\"salt\":\"XCA\",\"session\":\"XCA\",\"total_vote_count\":\"XCA\",\"current_vote_count\":\"XCA\",\"delegate_number\":\"XCA\",\"IP_address\":\"127.0.0.1\",\"delegate_name\":\"XCA\",\"about\":\"XCA\",\"website\":\"XCA\",\"team\":\"XCA\",\"pool_mode\":\"XCA\",\"fee_structure\":\"XCA\",\"server_settings\":\"XCA\",\"block_producer_eligibility\":\"XCA\",\"online_status\":\"XCA\",\"block_verifier_total_rounds\":\"XCA\",\"block_verifier_online_total_rounds\":\"XCA\",\"block_verifier_online_percentage\":\"XCA\",\"block_producer_total_rounds\":\"XCA\",\"VRF_node_public_and_private_key_total_rounds\":\"XCA\",\"VRF_node_random_data_total_rounds\":\"XCA\",\"block_producer_block_heights\":\"XCA\",\"VRF_node_public_and_private_key_block_heights\":\"XCA\",\"VRF_node_random_data_block_heights\":\"XCA\"}"
  
  if (process_id_file == NULL || data == NULL || settings == NULL)
  {
    if (process_id_file != NULL)
    {
      pointer_reset(process_id_file);
    }
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

  // reset the variables
  memset(&string1_test,0,sizeof(string1_test)); 
  memset(string2_test,0,strnlen(string2_test,BUFFER_SIZE)); 
  count_test = 0;  

  // initialize the database_document_fields struct 
  for (count = 0; count < 14; count++)
  {
    database_data.item[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    database_data.value[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
    
    if (database_data.item[count] == NULL || database_data.value[count] == NULL)
    {
      color_print("Could not allocate the memory needed on the heap","red");
      exit(0);
    }
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

  // initialize the database_multiple_documents_fields struct 
  for (count = 0; count < 2; count++)
  {
    for (counter = 0; counter < 14; counter++)
    {
      database_multiple_documents_fields.item[count][counter] = (char*)calloc(BUFFER_SIZE,sizeof(char));
      database_multiple_documents_fields.value[count][counter] = (char*)calloc(BUFFER_SIZE,sizeof(char));

      if (database_multiple_documents_fields.item[count][counter] == NULL || database_multiple_documents_fields.value[count][counter] == NULL)
      {
        color_print("Could not allocate the memory needed on the heap","red");
        exit(0);
      }
    }
  }

  memcpy(database_multiple_documents_fields.item[0][0],"username",8);
  memcpy(database_multiple_documents_fields.item[0][1],"most_total_rounds_delegate_name",31);
  memcpy(database_multiple_documents_fields.item[0][2],"most_total_rounds",17);
  memcpy(database_multiple_documents_fields.item[0][3],"best_block_verifier_online_percentage_delegate_name",51);
  memcpy(database_multiple_documents_fields.item[0][4],"best_block_verifier_online_percentage",37);
  memcpy(database_multiple_documents_fields.item[0][5],"most_block_producer_total_rounds_delegate_name",46);
  memcpy(database_multiple_documents_fields.item[0][6],"most_block_producer_total_rounds",32);
  memcpy(database_multiple_documents_fields.item[0][7],"most_VRF_node_public_and_private_key_total_rounds_delegate_name",63);
  memcpy(database_multiple_documents_fields.item[0][8],"most_VRF_node_public_and_private_key_total_rounds",49);
  memcpy(database_multiple_documents_fields.item[0][9],"most_VRF_node_random_data_total_rounds_delegate_name",52);
  memcpy(database_multiple_documents_fields.item[0][10],"most_VRF_node_random_data_total_rounds",38);
  memcpy(database_multiple_documents_fields.item[0][11],"total_XCASH_proof_of_stake_rounds",33);
  memcpy(database_multiple_documents_fields.item[0][12],"total_coins_in_proof_of_stake",29);
  memcpy(database_multiple_documents_fields.item[0][13],"total_circulating_supply_percentage_in_proof_of_stake",53);
  memcpy(database_multiple_documents_fields.item[1][0],"username",8);
  memcpy(database_multiple_documents_fields.item[1][1],"most_total_rounds_delegate_name",31);
  memcpy(database_multiple_documents_fields.item[1][2],"most_total_rounds",17);
  memcpy(database_multiple_documents_fields.item[1][3],"best_block_verifier_online_percentage_delegate_name",51);
  memcpy(database_multiple_documents_fields.item[1][4],"best_block_verifier_online_percentage",37);
  memcpy(database_multiple_documents_fields.item[1][5],"most_block_producer_total_rounds_delegate_name",46);
  memcpy(database_multiple_documents_fields.item[1][6],"most_block_producer_total_rounds",32);
  memcpy(database_multiple_documents_fields.item[1][7],"most_VRF_node_public_and_private_key_total_rounds_delegate_name",63);
  memcpy(database_multiple_documents_fields.item[1][8],"most_VRF_node_public_and_private_key_total_rounds",49);
  memcpy(database_multiple_documents_fields.item[1][9],"most_VRF_node_random_data_total_rounds_delegate_name",52);
  memcpy(database_multiple_documents_fields.item[1][10],"most_VRF_node_random_data_total_rounds",38);
  memcpy(database_multiple_documents_fields.item[1][11],"total_XCASH_proof_of_stake_rounds",33);
  memcpy(database_multiple_documents_fields.item[1][12],"total_coins_in_proof_of_stake",29);
  memcpy(database_multiple_documents_fields.item[1][13],"total_circulating_supply_percentage_in_proof_of_stake",53);

  memcpy(database_multiple_documents_fields.value[0][0],"XCASH",5);  
  memcpy(database_multiple_documents_fields.value[0][1],"DELEGATE_NAME",13);
  memcpy(database_multiple_documents_fields.value[0][2],"5",1);
  memcpy(database_multiple_documents_fields.value[0][3],"DELEGATE_NAME",13);
  memcpy(database_multiple_documents_fields.value[0][4],"10",2);
  memcpy(database_multiple_documents_fields.value[0][5],"DELEGATE_NAME",13);  
  memcpy(database_multiple_documents_fields.value[0][6],"15",2);
  memcpy(database_multiple_documents_fields.value[0][7],"DELEGATE_NAME",13);  
  memcpy(database_multiple_documents_fields.value[0][8],"5",1);
  memcpy(database_multiple_documents_fields.value[0][9],"DELEGATE_NAME",13);  
  memcpy(database_multiple_documents_fields.value[0][10],"10",2);  
  memcpy(database_multiple_documents_fields.value[0][11],"15",2);
  memcpy(database_multiple_documents_fields.value[0][12],"5",1);
  memcpy(database_multiple_documents_fields.value[0][13],"10",2);
  memcpy(database_multiple_documents_fields.value[1][0],"XCASH",5);  
  memcpy(database_multiple_documents_fields.value[1][1],"DELEGATE_NAME",13);
  memcpy(database_multiple_documents_fields.value[1][2],"5",1);
  memcpy(database_multiple_documents_fields.value[1][3],"DELEGATE_NAME",13);
  memcpy(database_multiple_documents_fields.value[1][4],"10",2);
  memcpy(database_multiple_documents_fields.value[1][5],"DELEGATE_NAME",13);  
  memcpy(database_multiple_documents_fields.value[1][6],"15",2);
  memcpy(database_multiple_documents_fields.value[1][7],"DELEGATE_NAME",13);  
  memcpy(database_multiple_documents_fields.value[1][8],"5",1);
  memcpy(database_multiple_documents_fields.value[1][9],"DELEGATE_NAME",13);  
  memcpy(database_multiple_documents_fields.value[1][10],"10",2);  
  memcpy(database_multiple_documents_fields.value[1][11],"15",2);
  memcpy(database_multiple_documents_fields.value[1][12],"5",1);
  memcpy(database_multiple_documents_fields.value[1][13],"10",2);

  database_multiple_documents_fields.document_count = 2;
  database_multiple_documents_fields.database_fields_count = 14;
  
  // get the process_id_file
  memcpy(process_id_file,"/proc/",6);
  sprintf(process_id_file+6,"%d",getpid());
  memcpy(process_id_file+strnlen(process_id_file,BUFFER_SIZE),"/status",7);

  // initialize the arrays
  for (count = 0; count < 5; count++)
  {
    data[count] = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
    settings[count] = (char*)calloc(BUFFER_SIZE,sizeof(char)); 

    if (data[count] == NULL || settings[count] == NULL)
    {
      color_print("Could not allocate the memory needed on the heap","red");
      exit(0);
    }
  }  

  // create the the arrays
  for (count = 0; count < 5; count++)
  {
    sprintf(data[count],"%ld",count);
    sprintf(settings[count],"%ld",count);
  }


  // write the start test message
  color_print(TEST_OUTLINE,"blue");
  printf("\033[1;34mreset_variables_allocated_on_the_heap test - Total test: %d\033[0m\n",RESET_VARAIBLES_ALLOCATED_ON_THE_HEAP_TEST);
  color_print(TEST_OUTLINE,"blue");
  printf("\n");

  // run the test

/*  // append_string   
  // read the current system memory usage
  previous_system_memory_usage = get_program_memory_usage(process_id_file);
  for (count = 0; count <= 1000; count++)
  {
    // test for using append_string on an empty statically allocated char
    append_string(string1_test,STR1_TEST);
    // test for using append_string on a statically allocated char
    append_string(string1_test," ");
    append_string(string1_test,STR1_TEST);
    // test for using append_string on an empty dynamically allocated char
    append_string(string2_test,STR2_TEST);
    // test for using append_string on a dynamically allocated char
    append_string(string2_test," ");
    memset(&string1_test,0,sizeof(string1_test)); 
    memset(string2_test,0,strnlen(string2_test,BUFFER_SIZE)); 
    if (count == 0)
    {    
      current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
    }
    if (count == 10)
    {
      current_system_memory_usage = get_program_memory_usage(process_id_file);
      if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
      {
        color_print("FAILED! append_string has not reset all variables allocated on the heap","red");
        settings2 = 0;
        break;
      }      
    }
    if (count == 100)
    {
      current_system_memory_usage = get_program_memory_usage(process_id_file);
      if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
      {
        color_print("FAILED! append_string has not reset all variables allocated on the heap","red");
        settings2 = 0;
        break;
      }  
    }
    if (count == 1000)
    {
      current_system_memory_usage = get_program_memory_usage(process_id_file);
      if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
      {
        color_print("FAILED! append_string has not reset all variables allocated on the heap","red");
        settings2 = 0;
        break;
      }
      else
      {
        color_print("PASSED! append_string has reset all variables allocated on the heap","green");
        count_test++;
      } 
    }    
  }




  // parse_json_data   
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
      memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
      append_string(result_test,GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA);
      parse_json_data(result_test,"blocktemplate_blob",data_test);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! parse_json_data has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! parse_json_data has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! parse_json_data has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! parse_json_data has reset all variables allocated on the heap","green");
          count_test++;
        } 
      }    
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // random_string   
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
      random_string(result_test,RANDOM_STRING_LENGTH);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! random_string has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! random_string has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! random_string has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! random_string has reset all variables allocated on the heap","green");
          count_test++;
        } 
      }    
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // varint_decode  
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      varint_decode(0xb2750199a302);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! varint_decode has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! varint_decode has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! varint_decode has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! varint_decode has reset all variables allocated on the heap","green");
          count_test++;
        } 
      }    
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // create_json_data_from_database_document_array   
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
      memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
      create_json_data_from_database_document_array(&database_data,result_test,"");
      create_json_data_from_database_multiple_documents_array(&database_multiple_documents_fields,data_test,"");
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! create_json_data_from_database_document_array has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! create_json_data_from_database_document_array has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! create_json_data_from_database_document_array has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! create_json_data_from_database_document_array has reset all variables allocated on the heap","green");
          count_test++;
        } 
      }    
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // string_count   
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
      memcpy(result_test,TEST_OUTLINE,strnlen(TEST_OUTLINE,BUFFER_SIZE));
      string_count(result_test,"-");
      string_count(result_test,"--");
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! string_count has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! string_count has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! string_count has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! string_count has reset all variables allocated on the heap","green");
          count_test++;
        } 
      }    
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // string_replace 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
      append_string(result_test,"{\r\n \"message_settings\": \"string_replace_test\",\r\n}");
      string_replace(result_test,"string_replace_test","string_replace");
      memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
      append_string(result_test,"{\r\n \"message_settings\": \"string_replace_test\",\r\n}");
      string_replace(result_test,"\"","\\\"");
      memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
      append_string(result_test,"{\r\n \"message_settings\": \"string_replace_test\",\r\n}");
      string_replace(result_test,"_test","");
      memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
      append_string(result_test,"{\r\n \"message_settings\": \"string_replace\",\r\n}");
      string_replace(result_test,"string_replace_test","");
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! string_replace has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! string_replace has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! string_replace has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! string_replace has reset all variables allocated on the heap","green");
          count_test++;
        } 
      }    
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // create_database_connection 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      mongoc_client_destroy(database_client);
      create_database_connection();
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! create_database_connection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! create_database_connection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! create_database_connection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! create_database_connection has reset all variables allocated on the heap","green");
          count_test++;
        }   
      }  
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // insert_document_into_collection_array 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      insert_document_into_collection_array(DATABASE_NAME,DATABASE_COLLECTION,data,settings,5);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! insert_document_into_collection_array has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! insert_document_into_collection_array has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! insert_document_into_collection_array has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! insert_document_into_collection_array has reset all variables allocated on the heap","green");
          count_test++;
        }   
      }  
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // insert_document_into_collection_json 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      insert_document_into_collection_json(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,0);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! insert_document_into_collection_json has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! insert_document_into_collection_json has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! insert_document_into_collection_json has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! insert_document_into_collection_json has reset all variables allocated on the heap","green");
          count_test++;
        }   
      }  
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // update_document_from_collection 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      update_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,MESSAGE_SETTINGS,0);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! update_document_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! update_document_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! update_document_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! update_document_from_collection has reset all variables allocated on the heap","green");
          count_test++;
        }   
      }  
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // read_document_from_collection 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
      read_document_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE_SETTINGS,data_test,0);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! read_document_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! read_document_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! read_document_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! read_document_from_collection has reset all variables allocated on the heap","green");
          count_test++;
        }  
      }
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }


  // read_document_field_from_collection 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
      read_document_field_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE_SETTINGS,"message_settings",data_test,0);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! read_document_field_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! read_document_field_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! read_document_field_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! read_document_field_from_collection has reset all variables allocated on the heap","green");
          count_test++;
        }   
      }  
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  delete_collection_from_database(DATABASE_NAME,DATABASE_COLLECTION,0);
  insert_document_into_collection_json(DATABASE_NAME,DATABASE_COLLECTION,DATABASE_COLLECTION_STATISTICS_DATA,0);  
  
  // read_document_all_fields_from_collection 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      for (count2 = 0; count2 < 14; count2++)
      {
        memset(database_data.item[count2],0,strnlen(database_data.item[count2],BUFFER_SIZE));
        memset(database_data.value[count2],0,strnlen(database_data.value[count2],BUFFER_SIZE));
      }
      read_document_all_fields_from_collection(DATABASE_NAME,DATABASE_COLLECTION,"{\"username\":\"XCASH\"}",&database_data,0);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! read_document_all_fields_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! read_document_all_fields_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! read_document_all_fields_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! read_document_all_fields_from_collection has reset all variables allocated on the heap","green");
          count_test++;
        }   
      }  
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  delete_collection_from_database(DATABASE_NAME,DATABASE_COLLECTION,0);
  insert_document_into_collection_json(DATABASE_NAME,DATABASE_COLLECTION,DATABASE_COLLECTION_STATISTICS_DATA,0);
  insert_document_into_collection_json(DATABASE_NAME,DATABASE_COLLECTION,DATABASE_COLLECTION_STATISTICS_DATA,0);
  
  // read_multiple_documents_all_fields_from_collection 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      for (count2 = 0; count2 < 2; count2++)
      {
        for (counter = 0; counter < 14; counter++)
        {
          memset(database_multiple_documents_fields.item[count2][counter],0,strnlen(database_multiple_documents_fields.item[count2][counter],BUFFER_SIZE));
          memset(database_multiple_documents_fields.value[count2][counter],0,strnlen(database_multiple_documents_fields.value[count2][counter],BUFFER_SIZE));
        }
      }
      read_multiple_documents_all_fields_from_collection(DATABASE_NAME,DATABASE_COLLECTION,"",&database_multiple_documents_fields,1,2,0);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! read_multiple_documents_all_fields_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! read_multiple_documents_all_fields_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! read_multiple_documents_all_fields_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! read_multiple_documents_all_fields_from_collection has reset all variables allocated on the heap","green");
          count_test++;
        }   
      }  
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // update_all_documents_from_collection 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      update_all_documents_from_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,0);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! update_all_documents_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! update_all_documents_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! update_all_documents_from_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! update_all_documents_from_collection has reset all variables allocated on the heap","green");
          count_test++;
        }   
      }  
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // count_documents_in_collection 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      count_documents_in_collection(DATABASE_NAME,DATABASE_COLLECTION,MESSAGE,0);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! count_documents_in_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! count_documents_in_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! count_documents_in_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! count_documents_in_collection has reset all variables allocated on the heap","green");
          count_test++;
        }   
      }  
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // count_all_documents_in_collection 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      count_all_documents_in_collection(DATABASE_NAME,DATABASE_COLLECTION,0);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! count_all_documents_in_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! count_all_documents_in_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! count_all_documents_in_collection has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! count_all_documents_in_collection has reset all variables allocated on the heap","green");
          count_test++;
        }   
      }  
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }


  delete_collection_from_database(DATABASE_NAME,DATABASE_COLLECTION,0);
  insert_document_into_collection_json(DATABASE_NAME,DATABASE_COLLECTION,DATABASE_COLLECTION_DELEGATES_DATA,0);

  // update_delegates_online_status 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      update_delegates_online_status(DATABASE_NAME,DATABASE_COLLECTION,0);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! update_delegates_online_status has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! update_delegates_online_status has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! update_delegates_online_status has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! update_delegates_online_status has reset all variables allocated on the heap","green");
          count_test++;
        }   
      }  
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // get_block_template 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      fprintf(stderr,"Current progress for get_block_template: %zu / 1000",count);
      fprintf(stderr,"\r");
      memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
      get_block_template(data_test,"0",0);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! get_block_template has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! get_block_template has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! get_block_template has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
        else
        {
          color_print("PASSED! get_block_template has reset all variables allocated on the heap","green");
          count_test++;
        }      
      } 
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // get_current_block_height 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      fprintf(stderr,"Current progress for get_current_block_height: %zu / 1000",count);
      fprintf(stderr,"\r");
      memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
      get_current_block_height(data_test,0);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! get_current_block_height has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! get_current_block_height has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! get_current_block_height has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
        else
        {
          color_print("PASSED! get_current_block_height has reset all variables allocated on the heap","green");
          count_test++;
        }      
      } 
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // get_previous_block_hash 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      fprintf(stderr,"Current progress for get_previous_block_hash: %zu / 1000",count);
      fprintf(stderr,"\r");
      memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
      get_previous_block_hash(data_test,0);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! get_previous_block_hash has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! get_previous_block_hash has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! get_previous_block_hash has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
        else
        {
          color_print("PASSED! get_previous_block_hash has reset all variables allocated on the heap","green");
          count_test++;
        }      
      } 
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // get_public_address 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      fprintf(stderr,"Current progress for get_previous_block_hash: %zu / 1000",count);
      fprintf(stderr,"\r");
      memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
      get_public_address(0);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! get_public_address has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! get_public_address has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! get_public_address has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
        else
        {
          color_print("PASSED! get_public_address has reset all variables allocated on the heap","green");
          count_test++;
        }      
      } 
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // data_verify 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      fprintf(stderr,"Current progress for get_previous_block_hash: %zu / 1000",count);
      fprintf(stderr,"\r");
      memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
      get_previous_block_hash(data_test,0);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! data_verify has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! data_verify has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! data_verify has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
        else
        {
          color_print("PASSED! data_verify has reset all variables allocated on the heap","green");
          count_test++;
        }      
      } 
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // set the current_round_part and current_round_part_backup_node
  memset(current_round_part,0,strnlen(current_round_part,BUFFER_SIZE));
  memset(current_round_part_backup_node,0,strnlen(current_round_part_backup_node,BUFFER_SIZE));
  memcpy(current_round_part,"1",1);
  memcpy(current_round_part_backup_node,"0",1); 

  // sign_data 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      fprintf(stderr,"Current progress for sign_data: %zu / 1000",count);
      fprintf(stderr,"\r");
      memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
      memcpy(data_test,"{\r\n \"message_settings\": \"XCASH_PROOF_OF_STAKE_TEST_DATA\",\r\n}",60);
      sign_data(data_test,0);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! sign_data has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! sign_data has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! sign_data has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
        else
        {
          color_print("PASSED! sign_data has reset all variables allocated on the heap","green");
          count_test++;
        }      
      } 
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // verify_data 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      fprintf(stderr,"Current progress for verify_data: %zu / 1000",count);
      fprintf(stderr,"\r");
      memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
      memcpy(data_test,"{\r\n \"message_settings\": \"XCASH_PROOF_OF_STAKE_TEST_DATA\",\r\n}",60);
      sign_data(data_test,0);
      verify_data(data_test,0,1,1);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! verify_data has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! verify_data has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! verify_data has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
        else
        {
          color_print("PASSED! verify_data has reset all variables allocated on the heap","green");
          count_test++;
        }      
      } 
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // set the server_message
  memset(server_message,0,strnlen(server_message,BUFFER_SIZE));
  memcpy(server_message,"XCASH_PROOF_OF_STAKE_TEST_DATA",30);
  // create the server
  pthread_create(&thread_id, NULL, &create_server_on_separate_thread,NULL);
  pthread_detach(thread_id);
  sleep(1);

  // get_delegate_online_status 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      get_delegate_online_status("127.0.0.1");
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! get_delegate_online_status has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! get_delegate_online_status has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! get_delegate_online_status has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
        else
        {
          color_print("PASSED! get_delegate_online_status has reset all variables allocated on the heap","green");
          count_test++;
        }      
      } 
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // send_and_receive_data_socket 
  // read the current system memory usage
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      fprintf(stderr,"Current progress for send_and_receive_data_socket: %zu / 1000",count);
      fprintf(stderr,"\r");
      memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
      memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
      memcpy(data_test,"{\r\n \"message_settings\": \"XCASH_PROOF_OF_STAKE_TEST_DATA\",\r\n}",60);
      sign_data(data_test,0);
      send_and_receive_data_socket(result_test,"127.0.0.1",SEND_DATA_PORT,data_test,TOTAL_CONNECTION_TIME_SETTINGS,"XCASH_PROOF_OF_STAKE_TEST_DATA",0);
      verify_data(result_test,0,1,1);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! send_and_receive_data_socket has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! send_and_receive_data_socket has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      } 
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! send_and_receive_data_socket has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
        else
        {
          color_print("PASSED! send_and_receive_data_socket has reset all variables allocated on the heap","green");
          count_test++;
        }      
      } 
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }*/



  // create_random_VRF_keys 
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      create_random_VRF_keys((unsigned char*)vrf_public_key,(unsigned char*)vrf_secret_key);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! create_random_VRF_keys has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! create_random_VRF_keys has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! create_random_VRF_keys has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! create_random_VRF_keys has reset all variables allocated on the heap","green");
          count_test++;
        }   
      }  
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }



  // crypto_vrf_is_valid_key 
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      count2 = crypto_vrf_is_valid_key((const unsigned char*)vrf_public_key);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! crypto_vrf_is_valid_key has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! crypto_vrf_is_valid_key has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! crypto_vrf_is_valid_key has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! crypto_vrf_is_valid_key has reset all variables allocated on the heap","green");
          count_test++;
        }   
      }  
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }


  // crypto_vrf_keypair_from_seed 
  if (settings2 == 1)
  {
    previous_system_memory_usage = get_program_memory_usage(process_id_file);
    for (count = 0; count <= 1000; count++)
    {
      crypto_vrf_keypair_from_seed((unsigned char*)vrf_public_key, (unsigned char*)vrf_secret_key, (const unsigned char*)data2);
      if (count == 0)
      {    
        current_memory_usage = get_program_memory_usage(process_id_file) - previous_system_memory_usage;
      }
      if (count == 10)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 9 && current_memory_usage > 0)
        {
          color_print("FAILED! crypto_vrf_keypair_from_seed has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }      
      }
      if (count == 100)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 50 && current_memory_usage > 0)
        {
          color_print("FAILED! crypto_vrf_keypair_from_seed has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }  
      }
      if (count == 1000)
      {
        current_system_memory_usage = get_program_memory_usage(process_id_file);
        if ((current_system_memory_usage - previous_system_memory_usage) > current_memory_usage * 100 && current_memory_usage > 0)
        {
          color_print("FAILED! crypto_vrf_keypair_from_seed has not reset all variables allocated on the heap","red");
          settings2 = 0;
          break;
        }
        else
        {
          color_print("PASSED! crypto_vrf_keypair_from_seed has reset all variables allocated on the heap","green");
          count_test++;
        }   
      }  
    }
  }
  else
  {
    color_print("All other test will not be run","red");
  }

  delete_collection_from_database(DATABASE_NAME,DATABASE_COLLECTION,0);

  for (count = 0; count < 14; count++)
  {
    pointer_reset(database_data.item[count]);
    pointer_reset(database_data.value[count]);
  }

  for (count = 0; count < 2; count++)
  {
    for (counter = 0; counter < 14; counter++)
    {
      pointer_reset(database_multiple_documents_fields.item[count][counter]);
      pointer_reset(database_multiple_documents_fields.value[count][counter]);
    }
  }

  for (count = 0; count < 5; count++)
  {
    pointer_reset(data[count]);
    pointer_reset(settings[count]);
  }
  pointer_reset(data);
  pointer_reset(settings);

  

  // write the end test message
  if (count_test == RESET_VARAIBLES_ALLOCATED_ON_THE_HEAP_TEST)
  {
    printf("\n");
    color_print(TEST_OUTLINE,"green");
    printf("\033[1;32mreset_variables_allocated_on_the_heap test - Passed test: %d, Failed test: 0\033[0m\n",RESET_VARAIBLES_ALLOCATED_ON_THE_HEAP_TEST);
    color_print(TEST_OUTLINE,"green");
    printf("\n\n");
  }
  else
  {
    printf("\n");
    color_print(TEST_OUTLINE,"red");
    printf("\033[1;31mreset_variables_allocated_on_the_heap test - Passed test: %d, Failed test: 1\033[0m\n",count_test);
    color_print(TEST_OUTLINE,"red");
    printf("\n\n");
    exit(0);
  }  
  pointer_reset(process_id_file);
  return count_test;

  #undef RESET_VARAIBLES_ALLOCATED_ON_THE_HEAP_TEST
  #undef GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA
  #undef DATA1
  #undef DATA2
  #undef DATABASE_COLLECTION
  #undef MESSAGE
  #undef MESSAGE_SETTINGS
  #undef DATABASE_COLLECTION_STATISTICS_DATA
  #undef DATABASE_COLLECTION_DELEGATES_DATA
}