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
#include "server_functions.h"
#include "string_functions.h"
#include "thread_functions.h"

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
    return 0;
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
  pthread_t thread_id;
  int settings2 = 1;

  // define macros
  #define RESET_VARAIBLES_ALLOCATED_ON_THE_HEAP_TEST 23
  #define GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA "{\r\n  \"id\": \"0\",\r\n  \"jsonrpc\": \"2.0\",\r\n  \"result\": {\r\n    \"blockhashing_blob\": \"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\",\r\n    \"blocktemplate_blob\": \"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\",\r\n    \"difficulty\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,\r\n    \"expected_reward\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,\r\n    \"height\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,\r\n    \"prev_hash\": \"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\",\r\n    \"reserved_offset\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,\r\n    \"status\": \"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\",\r\n    \"untrusted\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\r\n  }\r\n}"
  #define DATA1 "{\"username\":\"XCASH\",\"most_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_total_rounds\":\"5\",\"best_block_verifier_online_percentage_delegate_name\":\"DELEGATE_NAME\",\"best_block_verifier_online_percentage\":\"10\",\"most_block_producer_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_block_producer_total_rounds\":\"15\",\"most_VRF_node_public_and_private_key_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_public_and_private_key_total_rounds\":\"5\",\"most_VRF_node_random_data_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_random_data_total_rounds\":\"10\",\"total_XCASH_proof_of_stake_rounds\":\"15\",\"total_coins_in_proof_of_stake\":\"5\",\"total_circulating_supply_percentage_in_proof_of_stake\":\"10\"}"
  #define DATA2 "[{\"username\":\"XCASH\",\"most_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_total_rounds\":\"5\",\"best_block_verifier_online_percentage_delegate_name\":\"DELEGATE_NAME\",\"best_block_verifier_online_percentage\":\"10\",\"most_block_producer_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_block_producer_total_rounds\":\"15\",\"most_VRF_node_public_and_private_key_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_public_and_private_key_total_rounds\":\"5\",\"most_VRF_node_random_data_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_random_data_total_rounds\":\"10\",\"total_XCASH_proof_of_stake_rounds\":\"15\",\"total_coins_in_proof_of_stake\":\"5\",\"total_circulating_supply_percentage_in_proof_of_stake\":\"10\"},{\"username\":\"XCASH\",\"most_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_total_rounds\":\"5\",\"best_block_verifier_online_percentage_delegate_name\":\"DELEGATE_NAME\",\"best_block_verifier_online_percentage\":\"10\",\"most_block_producer_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_block_producer_total_rounds\":\"15\",\"most_VRF_node_public_and_private_key_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_public_and_private_key_total_rounds\":\"5\",\"most_VRF_node_random_data_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_random_data_total_rounds\":\"10\",\"total_XCASH_proof_of_stake_rounds\":\"15\",\"total_coins_in_proof_of_stake\":\"5\",\"total_circulating_supply_percentage_in_proof_of_stake\":\"10\"}]" 
  #define DATABASE_COLLECTION "XCASH_PROOF_OF_STAKE_TEST_DATA"
  #define MESSAGE "{\"message_settings\": \"XCASH_PROOF_OF_STAKE_TEST_DATA\"}"
  #define MESSAGE_SETTINGS "{\"message_settings\": \"XCASH_PROOF_OF_STAKE_DATA\"}"
  #define DATABASE_COLLECTION_STATISTICS_DATA "{\"username\":\"XCASH\",\"most_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_total_rounds\":\"5\",\"best_block_verifier_online_percentage_delegate_name\":\"DELEGATE_NAME\",\"best_block_verifier_online_percentage\":\"10\",\"most_block_producer_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_block_producer_total_rounds\":\"15\",\"most_VRF_node_public_and_private_key_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_public_and_private_key_total_rounds\":\"5\",\"most_VRF_node_random_data_total_rounds_delegate_name\":\"DELEGATE_NAME\",\"most_VRF_node_random_data_total_rounds\":\"10\",\"total_XCASH_proof_of_stake_rounds\":\"15\",\"total_coins_in_proof_of_stake\":\"5\",\"total_circulating_supply_percentage_in_proof_of_stake\":\"10\"}"
  
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
    return 0;
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

  // append_string   
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
      read_multiple_documents_all_fields_from_collection(DATABASE_NAME,DATABASE_COLLECTION,&database_multiple_documents_fields,1,2,0);
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
      get_block_template(data_test,0);
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
}