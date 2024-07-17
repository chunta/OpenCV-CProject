#include <iostream>
#include <fcntl.h> // O_* constants
#include <sys/mman.h> // shm_open, mmap
#include <unistd.h> // ftruncate, sleep
#include <cstring> // memcpy
#include <semaphore.h> // sem_open, sem_post, sem_wait

const char* SHARED_MEMORY_NAME = "/my_shared_memory";
const char* SEMAPHORE_NAME = "/my_semaphore";
const size_t SHARED_MEMORY_SIZE = sizeof(int);

int main() {
    // Create or open the shared memory object
    int shm_fd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        std::cerr << "Failed to create shared memory object\n";
        return 1;
    }

    // Set the size of the shared memory object
    if (ftruncate(shm_fd, SHARED_MEMORY_SIZE) == -1) {
        std::cerr << "Failed to set the size of shared memory object\n";
        return 1;
    }

    // Map the shared memory object into the process's address space
    void* ptr = mmap(nullptr, SHARED_MEMORY_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        std::cerr << "Failed to map shared memory object\n";
        return 1;
    }

    // Create or open the semaphore
    sem_t* semaphore = sem_open(SEMAPHORE_NAME, O_CREAT, 0666, 1);
    if (semaphore == SEM_FAILED) {
        std::cerr << "Failed to create semaphore\n";
        return 1;
    }

    // Write to the shared memory
    int counter = 0;
    while (true) {
        sleep(1);

        // Lock the semaphore
        sem_wait(semaphore);

        memcpy(ptr, &counter, sizeof(int));
        std::cout << "Writer: wrote " << counter << " to shared memory\n";
        counter++;

        // Unlock the semaphore
        sem_post(semaphore);
    }

    // Cleanup
    munmap(ptr, SHARED_MEMORY_SIZE);
    shm_unlink(SHARED_MEMORY_NAME);
    sem_close(semaphore);
    sem_unlink(SEMAPHORE_NAME);

    return 0;
}
