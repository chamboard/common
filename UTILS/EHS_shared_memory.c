//
// char* shm
// shmkey =0x00001971
//
char* setup_shared_memory(key_t key,uint32_t shmsz)
{
	//char c;
	char* shm;
    int shmid;
    //key_t key;
    char *s;
    //key = _DAEMON_SHM_KEY;// magic me
    if ((shmid = shmget(key, shmsz, IPC_CREAT | 0666)) < 0 ) { // was : ,IPC_CREAT | 0666)) < 0) {
		#ifdef _DEBUG_SHM
			printf("shmget error\n");
			//printf("shmget error (%d)\n",errno);
		#endif
        exit(0);
		
    }
    else {
			// attach the segment to the data space.
			if ((shm =(char*) shmat(shmid, NULL, 0)) == (char *) -1) // 
			{
				#ifdef _DEBUG_SHM
					printf("shmat Error");
				#endif
				exit(1);
			}
	}
   //
	//s=shm;
	//sprintf(s,"A");						// *=means initializing signal
    s = &shm[0];//_DAEMON_SLOT0+_DAEMON_SLOT_BUFFER];
    sprintf(s,"voix activée.");						// *=means initializing signal
	return shm;
}