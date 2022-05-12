#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>

#include <sys/stat.h>
#include <fcntl.h>


#define SHMKEY 69L
int main(){
	int shmid;		
	key_t key;		
	int size=50000;	
	int shmflg;	
	int ret;
	key = SHMKEY;
	struct vmi {
		int  hossz;
		char szoveg[50000-sizeof(int)]; 
	} *segm;
	shmflg = 0;
	if ((shmid=shmget(key, size, shmflg)) < 0) {
	   printf("Hiba\n");
	   
	   
	} else printf("Van mar ilyen shm szegmens!\n");

	printf("\nAz shm szegmens azonositoja %d: \n", shmid);
	shmflg = 00666 | SHM_RND;	
	segm = (struct vmi *)shmat(shmid, NULL, shmflg);
	if (segm == (void *)-1) {
		perror("Sikertelen attach!\n");
		exit(-1);
	}
	int fd=open("hvllib-7-01.txt",O_RDWR | O_CREAT, S_IRWXU);
	if (fd == -1) {
	    perror("Megnyitási hiba!");
	    exit(-1);
	}
	struct stat fileInfo;
	stat("hvllib-7-0.txt", &fileInfo);
	printf("File merete %d \n",fileInfo.st_size);
	
	ret=write(fd,segm->szoveg,fileInfo.st_size);

	int rtn = shmctl(shmid, IPC_RMID, NULL);
		printf("Szegmens torolve \n", rtn);
		return 0;
}
		
