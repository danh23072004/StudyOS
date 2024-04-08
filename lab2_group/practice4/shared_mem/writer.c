#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>  // shared memory
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * Writer.c using the pre-shared key SHM_KEY 0x123
 *
 */

// Shared memory key
#define SHM_KEY 0x123

int main(int argc, char *argv[])
{
	int shmid;
	char *shm;

	// Create a shared memory segment
	// Explain the parameters of shmget
	// shmget(SHM_KEY, 1000, 0644 | IPC_CREAT) creates a new shared memory segment or opens an existing segment.
	// The first parameter is the key that identifies the shared memory segment. This key is used to identify the segment when attaching to it.
	// The second parameter is the size of the shared memory segment in bytes.
	// The third parameter is a set of flags that control the operation of the call. The flags are specified by ORing together the following values:
	// 0644: The owner can read and write to the shared memory segment, and others can read from it.
	// IPC_CREAT: Create a new shared memory segment if one with the given key does not already exist.
	shmid = shmget(SHM_KEY, 1000, 0644 | IPC_CREAT);

	// Check if the shared memory segment was created successfully
	if (shmid < 0)
	{
		perror("Shared-memory");
		return 1;
	}
	else
	{
		printf("Shared-memory ID:  %d\n", shmid);
	}

	// Attach the shared memory segment
	shm = (char *)shmat(shmid, 0, 0);
	// explain the parameter of shmat
	// shmat(shmid, 0, 0) attaches the shared memory segment identified by shmid to the address space of the calling process.
	// The second parameter is the address at which the shared memory segment should be attached. If this parameter is 0, the system chooses a suitable (unused) address at which to attach the segment.
	// The third parameter is a set of flags that control the operation of the call. The flags are specified by ORing together the following values:

	if (shm == (char *)-1)
	{
		perror("shmat");
		exit(1);
	}
	printf("shared memory mm:  %p\n", shm);
	sprintf(shm, "hello DANH\n");
	printf("shared memory content:  %s\n", shm);
	sleep(10);

	// detach from the shared memory
	if (shmdt(shm) == -1)
	{
		perror("shmdt");
		return 1;
	}

	// Mark the shared segment to be destroyed.
	// Explain the parameters of shmctl
	// shmctl(shmid, IPC_RMID, 0) marks the shared memory segment identified by shmid to be destroyed.
	// The second parameter is the command to be performed on the shared memory segment. In this case, IPC_RMID marks the segment to be destroyed.
	// The third parameter is a pointer to a shmid_ds structure that contains information about the shared memory segment. This parameter is not used when the command is IPC_RMID.

	if (shmctl(shmid, IPC_RMID, 0) == -1)
	{
		perror("shmctl");
		return 1;
	}
	return 0;
}
