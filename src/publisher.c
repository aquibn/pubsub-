#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/common.h"
#include <sys/stat.h>


int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <pub_id> <topic> <message>\n", argv[0]);
        return 1;
    }

    char fifo_path[128];
    snprintf(fifo_path, sizeof(fifo_path), "%spub_fifo", FIFO_DIR);
    mkfifo(fifo_path, 0666);

    int fd = open(fifo_path, O_WRONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    message_t msg;
    printf("[Publisher] message_t size: %lu bytes\n", sizeof(msg));

    strcpy(msg.sender, argv[1]);
    strcpy(msg.topic, argv[2]);
    strcpy(msg.message, argv[3]);

    ssize_t written = write(fd, &msg, sizeof(msg));
    printf("[Publisher] Wrote %ld bytes\n", written);
    fsync(fd); // ensure flush

    close(fd);

    printf("[Publisher] Sent [%s]: %s\n", msg.topic, msg.message);
    return 0;
}
