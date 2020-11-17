### Milestone2 Writeup



#### Progress to date

10/21 -- 10/23: Finished Write operation on NFS

10/24 -- 10/27: Got rid of "fake root" directory, made FUSE structure more reasonable.

​						   Implemented IO functions like link, unlink, chmod, chown, etc.

​						   Modified RPC setting to run client side and server side in different machine.

10/28 -- 11/02: Using scheme of FIFO, designed Read cache on client side, which helped to avoid every read 						   operation invoke RPC calls.

​						   Supported multi-clients read operations, but the concurrent write issues remains, need to 						   be discussed.



#### Changes to the schedule established in the proposal

1. Only implemented read cache on client side, while write back cache has not been implemented.



#### Brief summary of each team member's specific contributions

**Ether Lou:** 

Supported client and server running on different machines.

Implemented write IO operations.

**Haimeng Zhang:** 

Implemented write IO operations.

Designed and implemented read cache.

Modified main function of FUSE client, got rid of "fake root" directory

**Jiateng Mao:** 

Designed and implemented read cache.

Implemented previously remained IO functions.

Designed data structures to avoid race condition.



​						   

