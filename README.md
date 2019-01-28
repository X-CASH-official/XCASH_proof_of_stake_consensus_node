# X-CASH Proof of stake - consensus node

More details will be released on the consensus node soon!



## Installation

This program will only run on a Linux/Unix OS at this time. We recommend installing this on a Ubuntu VPS/Server (16.04 or 18.04) for the best compatibility.

You will also need to run an X-CASH Daemon and X-CASH RPC wallet on the server. You can either download the latest X-CASH [release](https://github.com/X-CASH-official/X-CASH/releases) or build from [source](https://github.com/X-CASH-official/X-CASH#compiling-x-cash-from-source)



## Compiling X-CASH Proof of stake - consensus node from source



### Dependencies

The following table summarizes the tools and libraries required to build. 

| Dependencies                                 | Min. version  | Ubuntu package            |
| -------------------------------------------- | ------------- | ------------------------- |
| GCC                                          | 4.7.3         | `build-essential`         | 
| CMake                                        | 3.0.0         | `cmake`                   | 
| pkg-config                                   | any           | `pkg-config`              | 
| OpenSSL      		                       | any           | `libssl-dev`              |
| Git      		                       | any           | `git`                     |
| MongoDB C Driver (includes BSON libary)      | 1.13.1        |  build from source        |



### Building the MongoDB C driver from source

Visit the offical websites installation instructions at [http://mongoc.org/libmongoc/current/installing.html](http://mongoc.org/libmongoc/current/installing.html)
You will need to follow the instructions for [Building from a release tarball](http://mongoc.org/libmongoc/current/installing.html#building-from-a-release-tarball) or [Building from git](http://mongoc.org/libmongoc/current/installing.html#building-from-git) since you need the header files, not just the library files.

After you have built the MongoDB C driver from source, you will need to run  
`sudo ldconfig`



### Cloning the repository

`$ git clone https://github.com/X-CASH-official/XCASH_proof_of_stake_consensus_node.git`



### Build instructions

X-CASH Proof of stake - consensus node uses a Make file.

After cloning the repository, navigate to the folder  
`cd XCASH_proof_of_stake_consensus_node`

Then use the make file to build the binary file  
`make clean ; make`



## Setting up the xcashd and xcash-wallet-RPC

First you will need to run xcashd in the background. Navigate to the folder that contains the xcash binaries, then run  
`screen -dmS ./xcashd`

Next you need to run a xcash-wallet-rpc. Depending on if this is the consensus node or the consensus backup node, you will need to the run the wallet that contains the public address in the [Proof of stake](https://github.com/X-CASH-official/Proof_of_stake) for the CONSENSUS_NODE_PUBLIC_ADDRESS or CONSENSUS_BACKUP_NODE_PUBLIC_ADDRESS



## Running X-CASH Proof of stake test
It is recomeneded to run the X-CASH Proof of stake test before you run the main program. The test will ensure that your system is compatbile, and that you have setup your system correctly.

To run the X-CASH Proof of stake test, Navigate to the folder that contains the binary, then run  
`./xcash_proof_of_stake_consensus_node --test`

The test will return the number of passed and failed test on the bottom of the console. The failed test need to be 0 before you run the node. If the output is not showing 0 for failed test, then you need to scroll through the testing output and find what test failed (It will be red instead of green). If this is a system compatibility test, then you will need to fix the system. If this is a core test that has failed, then you need to possibly rebuild, or contact us with your OS version, and we can look into it.



## Running X-CASH Proof of stake - consensus node

Then you will need to run the xcash_proof_of_stake_consensus_node. Navigate to the folder that contains the binary, then run  
`./xcash_proof_of_stake_consensus_node`