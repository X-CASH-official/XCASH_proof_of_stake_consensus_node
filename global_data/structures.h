#ifndef STRUCTURES_H_   /* Include guard */
#define STRUCTURES_H_

/*
-----------------------------------------------------------------------------------------------------------
Global Structures
-----------------------------------------------------------------------------------------------------------
*/

// database struct
struct database_document_fields {
    size_t count;
    char* item[100];
    char* value[100];
};

struct database_multiple_documents_fields {
    size_t document_count;
    size_t database_fields_count;
    char* item[DATABASE_ARRAY_COUNT][DATABASE_ARRAY_COUNT];
    char* value[DATABASE_ARRAY_COUNT][DATABASE_ARRAY_COUNT];
};



 // Thread functions
 struct read_file_thread_parameters {
    char* result; // The data read from the file
    const char* FILE_NAME; // The file name
};

 struct write_file_thread_parameters {
    const char* DATA; // The data to write to the file
    const char* FILE_NAME; // The file name
};

struct insert_document_into_collection_json_thread_parameters {
    const char* DATABASE; // The database name
    const char* COLLECTION; // The collection name
    const char* DATA; // The json data to insert into the collection
};

struct read_document_from_collection_thread_parameters {
    const char* DATABASE; // The database name
    const char* COLLECTION; // The collection name
    const char* DATA; // The json data to use to search the collection for
    char *result; // The document read from the collection
};

struct read_document_field_from_collection_thread_parameters {
    const char* DATABASE; // The database name
    const char* COLLECTION; // The collection name
    const char* DATA; // The json data to use to search the collection for
    const char* FIELD_NAME; // The field of the document data to read
    char *result; // The document data read from the collection
};

struct read_document_all_fields_from_collection_thread_parameters {
    const char* DATABASE; // The database name
    const char* COLLECTION; // The collection name
    const char* DATA; // The json data to use to search the collection for
    struct database_document_fields* result; // A pointer to the database_document_fields struct
};

struct read_multiple_documents_all_fields_from_collection_thread_parameters {
    const char* DATABASE; // The database name
    const char* COLLECTION; // The collection name,
    const char* DATA; // The data to search for in each document, set to "" for all items
    struct database_multiple_documents_fields* result; // A pointer to the database_multiple_documents_fields struct
    const size_t DOCUMENT_COUNT_START; // The document to start at when reading the data
    const size_t DOCUMENT_COUNT_TOTAL; // The total amount of documents to read
};

struct update_document_from_collection_thread_parameters {
    const char* DATABASE; // The database name
    const char* COLLECTION; // The collection name
    const char* DATA; // The json data to use to search the collection for
    const char* FIELD_NAME_AND_DATA; // The json data to use to update the document
};

struct update_all_documents_from_collection_thread_parameters {
    const char* DATABASE; // The database name
    const char* COLLECTION; // The collection name
    const char* DATA; // The json data to use to update the documents
};

struct delete_document_from_collection_thread_parameters {
    const char* DATABASE; // The database name
    const char* COLLECTION; // The collection name
    const char* DATA; // The json data to use to delete the document
};

struct delete_collection_from_database_thread_parameters {
    const char* DATABASE; // The database name
    const char* COLLECTION; // The collection name
};

struct count_documents_in_collection_thread_parameters {
    const char* DATABASE; // The database name
    const char* COLLECTION; // The collection name
    const char* DATA; // The json data to use to search the collection for
};

struct count_all_documents_in_collection_thread_parameters {
    const char* DATABASE; // The database name
    const char* COLLECTION; // The collection name
};

struct update_delegates_online_status_thread_parameters {
    const char* DATABASE; // The database name
    const char* COLLECTION; // The collection name
};



 // Server thread functions
 struct total_connection_time_thread_parameters {
    pid_t process_id; // Holds the forked process ID that the client is connected to
    char* client_address; // Holds the IP address of the client
    char* port; // Holds the port number of the client 
    int data_received; // 1 if the server has received data from the client, otherwise 0
    int message_settings; // 1 to print the messages, otherwise 0. This is used for the testing flag to not print any success or error messages
};

 struct mainnode_timeout_thread_parameters {
    const pid_t process_id; // Holds the forked process ID that the client is connected to
    int data_received; // 1 if the node has received data from the main node, otherwise 0
    const char* main_node; // The main node (VRF_PUBLIC_AND_PRIVATE_KEY, VRF_RANDOM_DATA, BLOCK_PRODUCER)
    const char* current_round_part; // The current round part (1-4).
    const char* current_round_part_backup_node; // The current main node in the current round part (0-5)
};
#endif