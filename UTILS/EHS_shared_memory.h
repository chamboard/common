// shared memory
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
//
char* setup_shared_memory(key_t shm_key,uint32_t shmsz);
