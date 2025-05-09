#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/common.h"
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <topic>\n", argv[0]);
        return 1;
    }

    char *topic_filter = argv[1];
    char fifo_path[128];
    snprintf(fifo_path, sizeof(fifo_path), "%ssub_fifo", FIFO_DIR);
    mkfifo(fifo_path, 0666);

    int fd = open(fifo_path, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    message_t msg;
    printf("[Subscriber] message_t size: %lu bytes\n", sizeof(msg));

    while (1) {
        ssize_t bytes_read = read(fd, &msg, sizeof(msg));
        if (bytes_read > 0) {
            printf("[Subscriber] Read %ld bytes\n", bytes_read);
            if (strcmp(msg.topic, topic_filter) == 0) {
                printf("[Subscriber] Received [%s]: %s\n", msg.topic, msg.message);
            } else {
                printf("[Subscriber] Ignored topic: %s\n", msg.topic);
            }
        } else {
            sleep(1);
        }
    }

    close(fd);
    return 0;
}
