#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mongoc/mongoc.h>
#include <bson/bson.h>

#include "define_macro_functions.h"
#include "define_macros.h"
#include "variables.h"
#include "structures.h"

#include "blockchain_functions.h"

#include "define_macros_test.h"
#include "variables_test.h"
#include "blockchain_functions_test.h"

/*
-----------------------------------------------------------------------------------------------------------
Functions
-----------------------------------------------------------------------------------------------------------
*/

/*
-----------------------------------------------------------------------------------------------------------
Name: blockchain_functions_test
Description: Test the blockchain_functions
Return: The number of passed blockchain test
-----------------------------------------------------------------------------------------------------------
*/

int blockchain_functions_test()
{ 
  // Variables
  size_t count;

  // define macros
  #define BLOCKCHAIN_TEST 5
  #define NETWORK_BLOCK "0d0da5d5f1e00500000000000000000000000000000000000000000000000000000000000000050000000002b5d9ab0101fff9d8ab0101b2cce199a30202b1ae08c48f3b3e9ba6e22d9fdaf289eda8565179ebff7787883ecaf49f1ebdfbd81801159a7ed6a1065b708355d900b06e4e1c47238397723f4d379945b3bcdf10f09702b4187c424c4f434b434841494e5f52455345525645445f42595445535f53544152547c64656c65676174656e616d65317c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c5843413176313851736635504b4c723847467231346a486b6a6766336d506d314d4156627377427339515037467747544c434534537759693831425270327672635631326d614d744377395445314e5a525679796e51336532633362376d785277337c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c307c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c64656c65676174655f6261636b75705f312c64656c65676174655f6261636b75705f322c64656c65676174655f6261636b75705f332c64656c65676174655f6261636b75705f342c64656c65676174655f6261636b75705f357c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c64656c65676174656e616d65327c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c58434131675463557337443761486f32756f533239474445706a4d576b52357a7a514a43337a78437742315231674d4c594263736d70414267575a394d5776764c57585633516868595a39376d63787356383854665a725032564d416d6152514a347c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c307c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c64656c65676174655f6261636b75705f312c64656c65676174655f6261636b75705f322c64656c65676174655f6261636b75705f332c64656c65676174655f6261636b75705f342c64656c65676174655f6261636b75705f357c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c64656c65676174656e616d65337c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c584341313036674d4a6a6e59706b4c70533768546f6544375443625531796464475263427a7173416b35425447327643776e4d7536504c5a6232385a36644543566853587038374d374865505369624c444b4777363433696a4b6e4d774c303536327c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c307c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c64656c65676174655f6261636b75705f312c64656c65676174655f6261636b75705f322c64656c65676174655f6261636b75705f332c64656c65676174655f6261636b75705f342c64656c65676174655f6261636b75705f357c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c7c73a5031d645004add8a0360f3a01302cd7e0a1125842e50b7deca371cf67237c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c7c73a5031d645004add8a0360f3a01302cd7e0a1125842e50b7deca371cf67237c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c5b951935c5066c51f1beef7295aba6856ef5a1c85a2ca14c98a4f8745626a1313a2efab73f452334f3c36aac626b4c12296b1d84925b61831ebeba96b464da6158455118474e7dbeb0234680fba587097c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c310f13ef35d48748ad7057fe55861912fc153221b10633ebdb79460db8dbaa5a2a82796702b2eeef6b3355ebcbb1b8f65a62837d9bb5f64383722ac20f308e5c7c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c747275657c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c05f1c69a16ac265377454395bd133c9072b59fa3e0cd652f6f8e8d55fbff19927c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c30303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303035363536676635676866696a64696f76644a4450494f53677a663534683477363532343567643573313032316430673635316466383467643531363531663635643467353836343136643566345a36643534673635643473363534673635346673646734357c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c7f78db0d006639548c88fa9685ba3d0fa64e626d426c37e28ad442f74cb80e39a5ed9b4fb397f01bfbc8f54dd8aea7590d0408ae433d4d111eaef0ed97b9074f608bbb1722abaafa8734616ce7e4350b7c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c414079410cb5ed29a0f331a79cbf898d62b1f94c4d4752d4b9519668ada04f2201a277d60f09f8e50a5e4b0342aafdbd718a0761da52f3f7d3f0a38cc8cb05737c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c747275657c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c7c73a5031d645004add8a0360f3a01302cd7e0a1125842e50b7deca371cf67237c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c30303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303035363536676635676866696a64696f76644a4450494f53677a663534683477363532343567643573313032316430673635316466383467643531363531663635643467353836343136643566345a36643534673635643473363534673635346673646734357c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477cf7b2033fae04e087bd39478c6e5795bbf4f68a51c79bb6d7c085f86770b57a59ef8e61441ac6f67efa6c5f8286a02922f3fa91fd0d74d036462cc9e9f53ee0f4c8e63375b2b48af034591ba864ee260d7c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c0162fc911133879a42732ae5dc6bec484e0a8ad77cba4a8b6af260c84f6c6e42af3d21caee35b78a8a89ea7d88efd877724fc6d493059f4824dd40e866f4941a7c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c747275657c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c747275657c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c00000000000000000000000000000000000000000000000000000000000000057c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c5369675631346d3250624c4832597436693672546734574d6a5a4b3842324850624e69347a47464d56534534724362673444634a6e3138486b734e5a58513936557451615272766639757532794a6f376571437a5a57326a6641566e597c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c536967563151615254743652347737365a4c67534a58444d71684561506d4b6b3371414b4e7665524b34486578716e45755557776255626254373241524a683371376a5a7a614345486b54787246593570794d61476942595557426d517c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c5369675631616d716e55546263386448656243535a6b77414362445435434b6e6345555070594743786b4a317861586f393451794b586b685037634258327a616b796434466e7a34617757724834374c3878524e366553376d6f3942727c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c53696756316436315035577774726a54527a4237784850735436676a61476844763539596a6a52477066413863626d38576667687570634b6d637258387171444e43396a4646334b6d46527a7a675845336b36474c314d796d467439627c424c4f434b434841494e5f444154415f5345474d454e545f535452494e477c536967563155483236544230354133446441634659574355706d4850394863456e5a577731635645543973576e7a717130353644313175393773374e51694659524b34644866695774624d53614361394d31504d41705854784834564d7c424c4f434b434841494e5f52455345525645445f42595445535f454e447c000500000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000002000000000000000000000000000000000000000000000000000000000000000300000000000000000000000000000000000000000000000000000000000000040000000000000000000000000000000000000000000000000000000000000005"
  #define NETWORK_BLOCK_HEIGHT "2813049"
  #define BLOCK_REWARD_TRANSACTION_VERSION "02"
  #define BLOCK_REWARD_INPUT "01"
  #define VIN_TYPE "ff"
  #define BLOCK_REWARD_OUTPUT "01"
  #define STEALTH_ADDRESS_OUTPUT_TAG "02"
  #define TRANSACTION_PUBLIC_KEY_TAG "01"
  #define EXTRA_NONCE_TAG "02"
  #define RINGCT_VERSION "00"
  #define VARINT_ENCODED_VALUE_1 0xb2f58199a302 // random value
  #define VARINT_ENCODED_VALUE_TEXT_1 "b2f58199a302" // random value
  #define VARINT_DECODED_VALUE_1 78167177906 // random value
  #define VARINT_ENCODED_VALUE_2 0x7d // no encoding or decoding
  #define VARINT_ENCODED_VALUE_TEXT_2 "7d" // no encoding or decoding
  #define VARINT_DECODED_VALUE_2 125 // no encoding or decoding
  #define VARINT_ENCODED_VALUE_3 0x8002 // start of 1 byte length
  #define VARINT_ENCODED_VALUE_TEXT_3 "8002" // start of 1 byte length
  #define VARINT_DECODED_VALUE_3 256 // start of 1 byte length
  #define VARINT_ENCODED_VALUE_4 0xff7f // end of 1 byte length
  #define VARINT_ENCODED_VALUE_TEXT_4 "0xff7f" // end of 1 byte length
  #define VARINT_DECODED_VALUE_4 16383 // end of 1 byte length
  #define VARINT_ENCODED_VALUE_5 0x808001 // start of 2 byte length
  #define VARINT_ENCODED_VALUE_TEXT_5 "808001" // start of 2 byte length
  #define VARINT_DECODED_VALUE_5 16384 // start of 2 byte length
  #define VARINT_ENCODED_VALUE_6 0xffff7f // end of 2 byte length
  #define VARINT_ENCODED_VALUE_TEXT_6 "ffff7f" // end of 2 byte length
  #define VARINT_DECODED_VALUE_6 2097151 // end of 2 byte length
  #define VARINT_ENCODED_VALUE_7 0x80808001 // start of 3 byte length
  #define VARINT_ENCODED_VALUE_TEXT_7 "80808001" // start of 3 byte length
  #define VARINT_DECODED_VALUE_7 2097152 // start of 3 byte length
  #define VARINT_ENCODED_VALUE_8 0xffffff7f // end of 3 byte length
  #define VARINT_ENCODED_VALUE_TEXT_8 "ffffff7f" // end of 3 byte length
  #define VARINT_DECODED_VALUE_8 268435455 // end of 3 byte length
  #define VARINT_ENCODED_VALUE_9 0x8080808001 // start of 4 byte length
  #define VARINT_ENCODED_VALUE_TEXT_9 "8080808001" // start of 4 byte length
  #define VARINT_DECODED_VALUE_9 268435456 // start of 4 byte length
  #define VARINT_ENCODED_VALUE_10 0xffffffff7f // end of 4 byte length
  #define VARINT_ENCODED_VALUE_TEXT_10 "ffffffff7f" // end of 4 byte length
  #define VARINT_DECODED_VALUE_10 34359738367 // end of 4 byte length
  #define VARINT_ENCODED_VALUE_11 0x808080808001 // start of 5 byte length
  #define VARINT_ENCODED_VALUE_TEXT_11 "808080808001" // start of 5 byte length
  #define VARINT_DECODED_VALUE_11 34359738368 // start of 5 byte length
  #define VARINT_ENCODED_VALUE_12 0xffffffffff7f // end of 5 byte length
  #define VARINT_ENCODED_VALUE_TEXT_12 "ffffffffff7f" // end of 5 byte length
  #define VARINT_DECODED_VALUE_12 4398046511103 // end of 5 byte length
  #define VARINT_ENCODED_VALUE_13 0x80808080808001 // start of 6 byte length
  #define VARINT_ENCODED_VALUE_TEXT_13 "80808080808001" // start of 6 byte length
  #define VARINT_DECODED_VALUE_13 4398046511104 // start of 6 byte length
  #define VARINT_ENCODED_VALUE_14 0xffffffffffff7f // end of 6 byte length
  #define VARINT_ENCODED_VALUE_TEXT_14 "ffffffffffff7f" // end of 6 byte length
  #define VARINT_DECODED_VALUE_14 562949953421311 // end of 6 byte length
  #define VARINT_ENCODED_VALUE_15 0x8080808080808001 // start of 7 byte length
  #define VARINT_ENCODED_VALUE_TEXT_15 "8080808080808001" // start of 7 byte length
  #define VARINT_DECODED_VALUE_15 562949953421312 // start of 7 byte length
  #define VARINT_ENCODED_VALUE_16 0xffffffffffffff7f // end of 7 byte length
  #define VARINT_ENCODED_VALUE_TEXT_16 "ffffffffffffff7f" // end of 7 byte length
  #define VARINT_DECODED_VALUE_16 72057594037927935 // end of 7 byte length

  // reset the variables
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  count_test = 0;

  // write the start test message
  color_print(TEST_OUTLINE,"blue");
  printf("\033[1;34mblockchain functions test - Total test: %d\033[0m\n",BLOCKCHAIN_TEST);
  color_print(TEST_OUTLINE,"blue");
  printf("\n");

  // run the varint_decode test
  if (varint_decode(VARINT_ENCODED_VALUE_1) == VARINT_DECODED_VALUE_1 ||
      varint_decode(VARINT_ENCODED_VALUE_2) == VARINT_DECODED_VALUE_2 ||
      varint_decode(VARINT_ENCODED_VALUE_3) == VARINT_DECODED_VALUE_3 ||
      varint_decode(VARINT_ENCODED_VALUE_4) == VARINT_DECODED_VALUE_4 ||
      varint_decode(VARINT_ENCODED_VALUE_5) == VARINT_DECODED_VALUE_5 ||
      varint_decode(VARINT_ENCODED_VALUE_6) == VARINT_DECODED_VALUE_6 ||
      varint_decode(VARINT_ENCODED_VALUE_7) == VARINT_DECODED_VALUE_7 ||
      varint_decode(VARINT_ENCODED_VALUE_8) == VARINT_DECODED_VALUE_8 ||
      varint_decode(VARINT_ENCODED_VALUE_9) == VARINT_DECODED_VALUE_9 ||
      varint_decode(VARINT_ENCODED_VALUE_10) == VARINT_DECODED_VALUE_10 ||
      varint_decode(VARINT_ENCODED_VALUE_11) == VARINT_DECODED_VALUE_11 ||
      varint_decode(VARINT_ENCODED_VALUE_12) == VARINT_DECODED_VALUE_12 ||
      varint_decode(VARINT_ENCODED_VALUE_13) == VARINT_DECODED_VALUE_13 ||
      varint_decode(VARINT_ENCODED_VALUE_14) == VARINT_DECODED_VALUE_14 ||
      varint_decode(VARINT_ENCODED_VALUE_15) == VARINT_DECODED_VALUE_15 ||
      varint_decode(VARINT_ENCODED_VALUE_16) == VARINT_DECODED_VALUE_16)
  {
    color_print("PASSED! Test for varint decode","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for varint decode","red");
  }

  // run the varint_encode test
  if ((varint_encode(VARINT_DECODED_VALUE_1,data_test) == 1 && strncmp(data_test,VARINT_ENCODED_VALUE_TEXT_1,BUFFER_SIZE) == 0) ||
      (varint_encode(VARINT_DECODED_VALUE_2,data_test) == 1 && strncmp(data_test,VARINT_ENCODED_VALUE_TEXT_2,BUFFER_SIZE) == 0) ||
      (varint_encode(VARINT_DECODED_VALUE_3,data_test) == 1 && strncmp(data_test,VARINT_ENCODED_VALUE_TEXT_3,BUFFER_SIZE) == 0) ||
      (varint_encode(VARINT_DECODED_VALUE_4,data_test) == 1 && strncmp(data_test,VARINT_ENCODED_VALUE_TEXT_4,BUFFER_SIZE) == 0) ||
      (varint_encode(VARINT_DECODED_VALUE_5,data_test) == 1 && strncmp(data_test,VARINT_ENCODED_VALUE_TEXT_5,BUFFER_SIZE) == 0) ||
      (varint_encode(VARINT_DECODED_VALUE_6,data_test) == 1 && strncmp(data_test,VARINT_ENCODED_VALUE_TEXT_6,BUFFER_SIZE) == 0) ||
      (varint_encode(VARINT_DECODED_VALUE_7,data_test) == 1 && strncmp(data_test,VARINT_ENCODED_VALUE_TEXT_7,BUFFER_SIZE) == 0) ||
      (varint_encode(VARINT_DECODED_VALUE_8,data_test) == 1 && strncmp(data_test,VARINT_ENCODED_VALUE_TEXT_8,BUFFER_SIZE) == 0) ||
      (varint_encode(VARINT_DECODED_VALUE_9,data_test) == 1 && strncmp(data_test,VARINT_ENCODED_VALUE_TEXT_9,BUFFER_SIZE) == 0) ||
      (varint_encode(VARINT_DECODED_VALUE_10,data_test) == 1 && strncmp(data_test,VARINT_ENCODED_VALUE_TEXT_10,BUFFER_SIZE) == 0) ||
      (varint_encode(VARINT_DECODED_VALUE_11,data_test) == 1 && strncmp(data_test,VARINT_ENCODED_VALUE_TEXT_11,BUFFER_SIZE) == 0) ||
      (varint_encode(VARINT_DECODED_VALUE_12,data_test) == 1 && strncmp(data_test,VARINT_ENCODED_VALUE_TEXT_12,BUFFER_SIZE) == 0) ||
      (varint_encode(VARINT_DECODED_VALUE_13,data_test) == 1 && strncmp(data_test,VARINT_ENCODED_VALUE_TEXT_13,BUFFER_SIZE) == 0) ||
      (varint_encode(VARINT_DECODED_VALUE_14,data_test) == 1 && strncmp(data_test,VARINT_ENCODED_VALUE_TEXT_14,BUFFER_SIZE) == 0) ||
      (varint_encode(VARINT_DECODED_VALUE_15,data_test) == 1 && strncmp(data_test,VARINT_ENCODED_VALUE_TEXT_15,BUFFER_SIZE) == 0) ||
      (varint_encode(VARINT_DECODED_VALUE_16,data_test) == 1 && strncmp(data_test,VARINT_ENCODED_VALUE_TEXT_16,BUFFER_SIZE) == 0))
  {
    color_print("PASSED! Test for varint encode","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for varint encode","red");
  }

  // run the network_block_string_to_blockchain_data test
  if (network_block_string_to_blockchain_data(NETWORK_BLOCK,NETWORK_BLOCK_HEIGHT) == 1)
  {
    color_print("PASSED! Test for converting a network_block_string to a blockchain_data struct","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for converting a network_block_string to a blockchain_data struct","red");
  }

  // verify the blockchain_data
  if (verify_network_block_data(0,0,0,NETWORK_BLOCK_HEIGHT) == 1)
  {
    color_print("PASSED! Test for verifying the blockchain_data struct","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for verifying the blockchain_data struct","red");
  }

  // run the blockchain_data_to_network_block_string test and verify the network_block_string
  // reset the blockchain_data
  memset(blockchain_data.network_version_data,0,strnlen(blockchain_data.network_version_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.timestamp_data,0,strnlen(blockchain_data.timestamp_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.previous_block_hash_data,0,strnlen(blockchain_data.previous_block_hash_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.nonce_data,0,strnlen(blockchain_data.nonce_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.block_reward_transaction_version_data,0,strnlen(blockchain_data.block_reward_transaction_version_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.unlock_block_data,0,strnlen(blockchain_data.unlock_block_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.block_reward_input_data,0,strnlen(blockchain_data.block_reward_input_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.vin_type_data,0,strnlen(blockchain_data.vin_type_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.block_height_data,0,strnlen(blockchain_data.block_height_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.block_reward_output_data,0,strnlen(blockchain_data.block_reward_output_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.block_reward_data,0,strnlen(blockchain_data.block_reward_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.stealth_address_output_tag_data,0,strnlen(blockchain_data.stealth_address_output_tag_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.stealth_address_output_data,0,strnlen(blockchain_data.stealth_address_output_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.extra_bytes_size_data,0,strnlen(blockchain_data.extra_bytes_size_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.transaction_public_key_tag_data,0,strnlen(blockchain_data.transaction_public_key_tag_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.transaction_public_key_data,0,strnlen(blockchain_data.transaction_public_key_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.extra_nonce_tag_data,0,strnlen(blockchain_data.extra_nonce_tag_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.reserve_bytes_size_data,0,strnlen(blockchain_data.reserve_bytes_size_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.block_producer_delegates_name_data,0,strnlen(blockchain_data.blockchain_reserve_bytes.block_producer_delegates_name_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.block_producer_delegates_name,0,strnlen(blockchain_data.blockchain_reserve_bytes.block_producer_delegates_name,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.block_producer_public_address_data,0,strnlen(blockchain_data.blockchain_reserve_bytes.block_producer_public_address_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.block_producer_public_address,0,strnlen(blockchain_data.blockchain_reserve_bytes.block_producer_public_address,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.block_producer_node_backup_count_data,0,strnlen(blockchain_data.blockchain_reserve_bytes.block_producer_node_backup_count_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.block_producer_node_backup_count,0,strnlen(blockchain_data.blockchain_reserve_bytes.block_producer_node_backup_count,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.block_producer_backup_nodes_names_data,0,strnlen(blockchain_data.blockchain_reserve_bytes.block_producer_backup_nodes_names_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.block_producer_backup_nodes_names,0,strnlen(blockchain_data.blockchain_reserve_bytes.block_producer_backup_nodes_names,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_delegates_name_data,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_delegates_name_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_delegates_name,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_delegates_name,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_public_address_data,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_public_address_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_public_address,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_public_address,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_node_backup_count_data,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_node_backup_count_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_node_backup_count,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_node_backup_count,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_backup_nodes_names_data,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_backup_nodes_names_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_backup_nodes_names,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_backup_nodes_names,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_delegates_name_data,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_delegates_name_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_delegates_name,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_delegates_name,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_public_address_data,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_public_address_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_public_address,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_public_address,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_node_backup_count_data,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_node_backup_count_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_node_backup_count,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_node_backup_count,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_backup_nodes_names_data,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_backup_nodes_names_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_backup_nodes_names,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_backup_nodes_names,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_public_key_data_round_part_1,0,strlen(blockchain_data.blockchain_reserve_bytes.vrf_public_key_data_round_part_1));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_public_key_round_part_1,0,strlen(blockchain_data.blockchain_reserve_bytes.vrf_public_key_round_part_1));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_data_round_part_1,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_data_round_part_1,BUFFER_SIZE));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_round_part_1,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_round_part_1,BUFFER_SIZE));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_proof_data_round_part_1,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_proof_data_round_part_1,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_proof_round_part_1,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_proof_round_part_1,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_beta_string_data_round_part_1,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_beta_string_data_round_part_1,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_beta_string_round_part_1,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_beta_string_round_part_1,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_data_round_part_1,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_data_round_part_1,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_public_key_data_round_part_2,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_public_key_data_round_part_2,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_public_key_round_part_2,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_public_key_round_part_2,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_data_round_part_2,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_data_round_part_2,BUFFER_SIZE));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_round_part_2,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_round_part_2,BUFFER_SIZE));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_proof_data_round_part_2,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_proof_data_round_part_2,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_proof_round_part_2,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_proof_round_part_2,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_beta_string_data_round_part_2,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_beta_string_data_round_part_2,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_beta_string_round_part_2,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_beta_string_round_part_2,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_data_round_part_2,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_data_round_part_2,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_public_key_data_round_part_3,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_public_key_data_round_part_3,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_public_key_round_part_3,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_public_key_round_part_3,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_data_round_part_3,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_data_round_part_3,BUFFER_SIZE));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_round_part_3,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_round_part_3,BUFFER_SIZE));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_proof_data_round_part_3,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_proof_data_round_part_3,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_proof_round_part_3,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_proof_round_part_3,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_beta_string_data_round_part_3,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_beta_string_data_round_part_3,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_beta_string_round_part_3,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_beta_string_round_part_3,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.vrf_data_round_part_3,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_data_round_part_3,BUFFER_SIZE_NETWORK_BLOCK_DATA));  
  memset(blockchain_data.blockchain_reserve_bytes.vrf_data,0,strnlen(blockchain_data.blockchain_reserve_bytes.vrf_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.blockchain_reserve_bytes.previous_block_hash_data,0,strnlen(blockchain_data.blockchain_reserve_bytes.previous_block_hash_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  for (count = 0; count < BLOCK_VALIDATION_NODES_TOTAL_AMOUNT; count++)
  {
    memset(blockchain_data.blockchain_reserve_bytes.block_validation_node_signature_data[count],0,strnlen(blockchain_data.blockchain_reserve_bytes.block_validation_node_signature_data[count],BUFFER_SIZE_NETWORK_BLOCK_DATA));
    memset(blockchain_data.blockchain_reserve_bytes.block_validation_node_signature[count],0,strnlen(blockchain_data.blockchain_reserve_bytes.block_validation_node_signature[count],BUFFER_SIZE_NETWORK_BLOCK_DATA));
  }
  memset(blockchain_data.ringct_version_data,0,strnlen(blockchain_data.ringct_version_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  memset(blockchain_data.transaction_amount_data,0,strnlen(blockchain_data.transaction_amount_data,BUFFER_SIZE_NETWORK_BLOCK_DATA));
  for (count = 0; count < MAXIMUM_TRANSACATIONS_PER_BLOCK; count++)
  {
    memset(blockchain_data.transactions[count],0,strnlen(blockchain_data.transactions[count],BUFFER_SIZE_NETWORK_BLOCK_DATA));
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  count = 0;

  // create the block data
  memcpy(blockchain_data.network_version_data,NETWORK_VERSION,4);
  blockchain_data.timestamp = 1545366181;
  memcpy(blockchain_data.previous_block_hash_data,"0000000000000000000000000000000000000000000000000000000000000005",64);
  memcpy(blockchain_data.nonce_data,BLOCK_PRODUCER_NETWORK_BLOCK_NONCE,8);
  memcpy(blockchain_data.block_reward_transaction_version_data,BLOCK_REWARD_TRANSACTION_VERSION,2);
  blockchain_data.unlock_block = 2813109;
  memcpy(blockchain_data.block_reward_input_data,BLOCK_REWARD_INPUT,2);
  memcpy(blockchain_data.vin_type_data,VIN_TYPE,2);
  blockchain_data.block_height = 2813049;
  memcpy(blockchain_data.block_reward_output_data,BLOCK_REWARD_OUTPUT,2);
  blockchain_data.block_reward = 78168745522;
  memcpy(blockchain_data.stealth_address_output_tag_data,STEALTH_ADDRESS_OUTPUT_TAG,2);
  memcpy(blockchain_data.stealth_address_output_data,"b1ae08c48f3b3e9ba6e22d9fdaf289eda8565179ebff7787883ecaf49f1ebdfb",64);
  memcpy(blockchain_data.transaction_public_key_tag_data,TRANSACTION_PUBLIC_KEY_TAG,2);
  memcpy(blockchain_data.transaction_public_key_data,"159a7ed6a1065b708355d900b06e4e1c47238397723f4d379945b3bcdf10f097",64);
  memcpy(blockchain_data.extra_nonce_tag_data,EXTRA_NONCE_TAG,2);
  memcpy(blockchain_data.blockchain_reserve_bytes.block_producer_delegates_name,"delegatename1",13);
  memcpy(blockchain_data.blockchain_reserve_bytes.block_producer_public_address,"XCA1v18Qsf5PKLr8GFr14jHkjgf3mPm1MAVbswBs9QP7FwGTLCE4SwYi81BRp2vrcV12maMtCw9TE1NZRVyynQ3e2c3b7mxRw3",XCASH_WALLET_LENGTH);
  memcpy(blockchain_data.blockchain_reserve_bytes.block_producer_node_backup_count,"0",1);
  memcpy(blockchain_data.blockchain_reserve_bytes.block_producer_backup_nodes_names,"delegate_backup_1,delegate_backup_2,delegate_backup_3,delegate_backup_4,delegate_backup_5",89);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_delegates_name,"delegatename2",13);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_public_address,"XCA1gTcUs7D7aHo2uoS29GDEpjMWkR5zzQJC3zxCwB1R1gMLYBcsmpABgWZ9MWvvLWXV3QhhYZ97mcxsV88TfZrP2VMAmaRQJ4",XCASH_WALLET_LENGTH);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_node_backup_count,"0",1);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_node_public_and_secret_key_backup_nodes_names,"delegate_backup_1,delegate_backup_2,delegate_backup_3,delegate_backup_4,delegate_backup_5",89);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_delegates_name,"delegatename3",13);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_public_address,"XCA106gMJjnYpkLpS7hToeD7TCbU1yddGRcBzqsAk5BTG2vCwnMu6PLZb28Z6dECVhSXp87M7HePSibLDKGw643ijKnMwL0562",XCASH_WALLET_LENGTH);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_node_backup_count,"0",1);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_node_random_data_backup_nodes_names,"delegate_backup_1,delegate_backup_2,delegate_backup_3,delegate_backup_4,delegate_backup_5",89);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_public_key_data_round_part_1,"7c73a5031d645004add8a0360f3a01302cd7e0a1125842e50b7deca371cf6723",64);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_data_round_part_1,"7c73a5031d645004add8a0360f3a01302cd7e0a1125842e50b7deca371cf6723",64);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_proof_data_round_part_1,"5b951935c5066c51f1beef7295aba6856ef5a1c85a2ca14c98a4f8745626a1313a2efab73f452334f3c36aac626b4c12296b1d84925b61831ebeba96b464da6158455118474e7dbeb0234680fba58709",160);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_beta_string_data_round_part_1,"310f13ef35d48748ad7057fe55861912fc153221b10633ebdb79460db8dbaa5a2a82796702b2eeef6b3355ebcbb1b8f65a62837d9bb5f64383722ac20f308e5c",128);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_public_key_data_round_part_2,"05f1c69a16ac265377454395bd133c9072b59fa3e0cd652f6f8e8d55fbff1992",64);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_data_round_part_2,"30303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303035363536676635676866696a64696f76644a4450494f53677a663534683477363532343567643573313032316430673635316466383467643531363531663635643467353836343136643566345a3664353467363564347336353467363534667364673435",328);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_proof_data_round_part_2,"7f78db0d006639548c88fa9685ba3d0fa64e626d426c37e28ad442f74cb80e39a5ed9b4fb397f01bfbc8f54dd8aea7590d0408ae433d4d111eaef0ed97b9074f608bbb1722abaafa8734616ce7e4350b",160);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_beta_string_data_round_part_2,"414079410cb5ed29a0f331a79cbf898d62b1f94c4d4752d4b9519668ada04f2201a277d60f09f8e50a5e4b0342aafdbd718a0761da52f3f7d3f0a38cc8cb0573",128);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_public_key_data_round_part_3,"7c73a5031d645004add8a0360f3a01302cd7e0a1125842e50b7deca371cf6723",64);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_alpha_string_data_round_part_3,"30303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303035363536676635676866696a64696f76644a4450494f53677a663534683477363532343567643573313032316430673635316466383467643531363531663635643467353836343136643566345a3664353467363564347336353467363534667364673435",328);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_proof_data_round_part_3,"f7b2033fae04e087bd39478c6e5795bbf4f68a51c79bb6d7c085f86770b57a59ef8e61441ac6f67efa6c5f8286a02922f3fa91fd0d74d036462cc9e9f53ee0f4c8e63375b2b48af034591ba864ee260d",160);
  memcpy(blockchain_data.blockchain_reserve_bytes.vrf_beta_string_data_round_part_3,"0162fc911133879a42732ae5dc6bec484e0a8ad77cba4a8b6af260c84f6c6e42af3d21caee35b78a8a89ea7d88efd877724fc6d493059f4824dd40e866f4941a",128);
  memcpy(blockchain_data.blockchain_reserve_bytes.previous_block_hash_data,"0000000000000000000000000000000000000000000000000000000000000005",64);
  memcpy(blockchain_data.blockchain_reserve_bytes.block_validation_node_signature[0],"SigV14m2PbLH2Yt6i6rTg4WMjZK8B2HPbNi4zGFMVSE4rCbg4DcJn18HksNZXQ96UtQaRrvf9uu2yJo7eqCzZW2jfAVnY",93);
  memcpy(blockchain_data.blockchain_reserve_bytes.block_validation_node_signature[1],"SigV1QaRTt6R4w76ZLgSJXDMqhEaPmKk3qAKNveRK4HexqnEuUWwbUbbT72ARJh3q7jZzaCEHkTxrFY5pyMaGiBYUWBmQ",93);
  memcpy(blockchain_data.blockchain_reserve_bytes.block_validation_node_signature[2],"SigV1amqnUTbc8dHebCSZkwACbDT5CKncEUPpYGCxkJ1xaXo94QyKXkhP7cBX2zakyd4Fnz4awWrH47L8xRN6eS7mo9Br",93);
  memcpy(blockchain_data.blockchain_reserve_bytes.block_validation_node_signature[3],"SigV1d61P5WwtrjTRzB7xHPsT6gjaGhDv59YjjRGpfA8cbm8WfghupcKmcrX8qqDNC9jFF3KmFRzzgXE3k6GL1MymFt9b",93);
  memcpy(blockchain_data.blockchain_reserve_bytes.block_validation_node_signature[4],"SigV1UH26TB05A3DdAcFYWCUpmHP9HcEnZWw1cVET9sWnzqq056D11u97s7NQiFYRK4dHfiWtbMSaCa9M1PMApXTxH4VM",93);
  memcpy(blockchain_data.ringct_version_data,RINGCT_VERSION,2);
  blockchain_data.transaction_amount = 5;
  memcpy(blockchain_data.transactions[0],"0000000000000000000000000000000000000000000000000000000000000001",64);
  memcpy(blockchain_data.transactions[1],"0000000000000000000000000000000000000000000000000000000000000002",64);
  memcpy(blockchain_data.transactions[2],"0000000000000000000000000000000000000000000000000000000000000003",64);
  memcpy(blockchain_data.transactions[3],"0000000000000000000000000000000000000000000000000000000000000004",64);
  memcpy(blockchain_data.transactions[4],"0000000000000000000000000000000000000000000000000000000000000005",64);

  if (blockchain_data_to_network_block_string(data_test) == 1)
  {
    // verify the network_block_string
    if (strncmp(NETWORK_BLOCK,data_test,BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for converting a blockchain_data struct to a network_block_string","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for converting a blockchain_data struct to a network_block_string","red");
    }
  }
  else
  {
    color_print("FAILED! Test for converting a blockchain_data struct to a network_block_string","red");
  }



  // write the end test message
  if (count_test == BLOCKCHAIN_TEST)
  {
    printf("\n");
    color_print(TEST_OUTLINE,"green");
    printf("\033[1;32mblockchain functions test - Passed test: %d, Failed test: 0\033[0m\n",BLOCKCHAIN_TEST);
    color_print(TEST_OUTLINE,"green");
    printf("\n\n");
  }
  else
  {
    printf("\n");
    color_print(TEST_OUTLINE,"red");
    printf("\033[1;31mblockchain functions test - Passed test: %d, Failed test: %d\033[0m\n",count_test,BLOCKCHAIN_TEST-count_test);
    color_print(TEST_OUTLINE,"red");
    printf("\n\n");
  } 
  return count_test;

  #undef BLOCKCHAIN_TEST
  #undef NETWORK_BLOCK
  #undef NETWORK_BLOCK_HEIGHT
  #undef BLOCK_REWARD_TRANSACTION_VERSION
  #undef BLOCK_REWARD_INPUT
  #undef VIN_TYPE
  #undef BLOCK_REWARD_OUTPUT
  #undef STEALTH_ADDRESS_OUTPUT_TAG
  #undef TRANSACTION_PUBLIC_KEY_TAG
  #undef EXTRA_NONCE_TAG
  #undef RINGCT_VERSION
  #undef VARINT_ENCODED_VALUE_1
  #undef VARINT_ENCODED_VALUE_TEXT_1
  #undef VARINT_DECODED_VALUE_1
  #undef VARINT_ENCODED_VALUE_2
  #undef VARINT_ENCODED_VALUE_TEXT_2
  #undef VARINT_DECODED_VALUE_2
  #undef VARINT_ENCODED_VALUE_3
  #undef VARINT_ENCODED_VALUE_TEXT_3
  #undef VARINT_DECODED_VALUE_3
  #undef VARINT_ENCODED_VALUE_4
  #undef VARINT_ENCODED_VALUE_TEXT_4
  #undef VARINT_DECODED_VALUE_4
  #undef VARINT_ENCODED_VALUE_5
  #undef VARINT_ENCODED_VALUE_TEXT_5
  #undef VARINT_DECODED_VALUE_5
  #undef VARINT_ENCODED_VALUE_6
  #undef VARINT_ENCODED_VALUE_TEXT_6
  #undef VARINT_DECODED_VALUE_6
  #undef VARINT_ENCODED_VALUE_7
  #undef VARINT_ENCODED_VALUE_TEXT_7
  #undef VARINT_DECODED_VALUE_7
  #undef VARINT_ENCODED_VALUE_8
  #undef VARINT_ENCODED_VALUE_TEXT_8
  #undef VARINT_DECODED_VALUE_8
  #undef VARINT_ENCODED_VALUE_9
  #undef VARINT_ENCODED_VALUE_TEXT_9
  #undef VARINT_DECODED_VALUE_9
  #undef VARINT_ENCODED_VALUE_10
  #undef VARINT_ENCODED_VALUE_TEXT_10
  #undef VARINT_DECODED_VALUE_10
  #undef VARINT_ENCODED_VALUE_11
  #undef VARINT_ENCODED_VALUE_TEXT_11
  #undef VARINT_DECODED_VALUE_11
  #undef VARINT_ENCODED_VALUE_12
  #undef VARINT_ENCODED_VALUE_TEXT_12
  #undef VARINT_DECODED_VALUE_12
  #undef VARINT_ENCODED_VALUE_13
  #undef VARINT_ENCODED_VALUE_TEXT_13
  #undef VARINT_DECODED_VALUE_13
  #undef VARINT_ENCODED_VALUE_14
  #undef VARINT_ENCODED_VALUE_TEXT_14
  #undef VARINT_DECODED_VALUE_14
  #undef VARINT_ENCODED_VALUE_15
  #undef VARINT_ENCODED_VALUE_TEXT_15
  #undef VARINT_DECODED_VALUE_15
  #undef VARINT_ENCODED_VALUE_16
  #undef VARINT_ENCODED_VALUE_TEXT_16
  #undef VARINT_DECODED_VALUE_16
}