# milestone writeup

**Progress to date**

- For now we have established a simple NFS, which can basically realize some basic remote process call of fuse program. The functions are: 
  - getattr -- get attribute of a file or a directory
  - mkdir -- make directory
  - rmdir  -- remove directory
  - opendir -- open directory
  - readdir -- read directory 
  - open -- open file
  - read -- read to buffer
  - write -- write to file
- Currently we only test our programme on the same machine so the RPC API's host is set to be localhost.

**Changes to the schedule established in the proposal, with discussions of any shortfalls or changed designs**

- Since it's our first time play with the RPC, we spent much time on researching for workable library/API on C. And we also spent much time on figuring out how to wrap our data correctly. For example, we spent most time on figuring out how to make readdir() work, for the original function has a function pointer which points to a function called filler, and the filler would fill the buffer with the file name in the directory. We faild to import the function directly from <fuse.h> and had to make up a function that did identical thing. But it also rose a problem with the buffer ... It's really a long story to tell.
- So I'd say that we were kind of underestimating the workload of our milestone1(build a well functional NFS). For now we have realized most of the basic functions in a fuse program but not all of them, let alone lots of mess of debugging code and comment wi
- thin it. We may need a few more days to achieve a so-called "well-functioned" NFS program. 
- We may need to cut the feature of cache. So the milestone2 would be a well functional NFS and the final goal would be a more secured NFS with TLS encryptying the communication.

**A brief summary of each team member's specific contributions**

- The work we did together: 
  - we  built the function frame and wrote the IDL.x file together at the beginning. 
- Jiateng Mao: Did a lot research toward RPC and guided us to rpcbind. Wrote the directory-related functions.
- Haimeng Zhang: Wrote the open/read/write functions. 

- Yuecomng Lou: Reviewed the fuse program and debugging with the other two. 