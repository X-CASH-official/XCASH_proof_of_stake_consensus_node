CPP=gcc
CFLAGS= -I/usr/local/include/libbson-1.0 -I/usr/local/include/libmongoc-1.0

LDFLAGS= -lmongoc-1.0 -lbson-1.0 -lpthread

all: xcash_proof_of_stake_consensus_node

xcash_proof_of_stake_consensus_node:
	gcc -o xcash_proof_of_stake_consensus_node xcash_proof_of_stake_consensus_node.c xcash_proof_of_stake_consensus_node_functions_and_macros.c xcash_proof_of_stake_consensus_node_test.c $(CFLAGS) $(LDFLAGS)

clean:
	rm xcash_proof_of_stake_consensus_node