#include <iostream>
#include <fcntl.h> // O_* constants
#include <sys/mman.h> // shm_open, mmap
#include <unistd.h> // close, sleep
#include <cstring> // memcpy
#include <semaphore.h> // sem_open, sem_post, sem_wait

const char* SHARED_MEMORY_NAME = "/my_shared_memory";
const char* SEMAPHORE_NAME = "/my_semaphore";
const size_t SHARED_MEMORY_SIZE = sizeof(int);

int main() {
    // Open the shared memory object
    int shm_fd = shm_open(SHARED_MEMORY_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        std::cerr << "Failed to open shared memory object\n";
        return 1;
    }

    // Map the shared memory object into the process's address space
    void* ptr = mmap(nullptr, SHARED_MEMORY_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        std::cerr << "Failed to map shared memory object\n";
        return 1;
    }

    // Open the semaphore
    sem_t* semaphore = sem_open(SEMAPHORE_NAME, 0);
    if (semaphore == SEM_FAILED) {
        std::cerr << "Failed to open semaphore\n";
        return 1;
    }

    // Read from the shared memory
    while (true) {
        sleep(1);

        // Lock the semaphore
        sem_wait(semaphore);

        int value;
        memcpy(&value, ptr, sizeof(int));
        std::cout << "Reader: read " << value << " from shared memory\n";

        // Unlock the semaphore
        sem_post(semaphore);
    }

    // Cleanup
    munmap(ptr, SHARED_MEMORY_SIZE);
    close(shm_fd);
    sem_close(semaphore);

    return 0;
}
