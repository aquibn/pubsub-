#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../include/common.h"

int main() {
    printf("[Server] Starting server...\n");

    mkdir(FIFO_DIR, 0777);

    char pub_fifo[128], sub_fifo[128];
    snprintf(pub_fifo, sizeof(pub_fifo), "%spub_fifo", FIFO_DIR);
    snprintf(sub_fifo, sizeof(sub_fifo), "%ssub_fifo", FIFO_DIR);

    mkfifo(pub_fifo, 0666);
    mkfifo(sub_fifo, 0666);

    int pub_fd = open(pub_fifo, O_RDONLY);
    int sub_fd = open(sub_fifo, O_WRONLY);

    if (pub_fd < 0 || sub_fd < 0) {
        perror("[Server] Error opening FIFOs");
        return 1;
    }

    message_t msg;
    printf("[Server] message_t size: %lu bytes\n", sizeof(msg));

    while (1) {
        ssize_t bytes_read = read(pub_fd, &msg, sizeof(msg));
        if (bytes_read > 0) {
            printf("[Server] Read %ld bytes\n", bytes_read);
            printf("[Server] Message received: [%s] %s: %s\n", msg.topic, msg.sender, msg.message);
            ssize_t bytes_written = write(sub_fd, &msg, sizeof(msg));
            printf("[Server] Wrote %ld bytes\n", bytes_written);
        } else {
            sleep(1);
        }
    }

    close(pub_fd);
    close(sub_fd);
    return 0;
}
