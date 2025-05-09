#ifndef COMMON_H
#define COMMON_H

#define FIFO_DIR "/tmp/pubsub/"
#define MAX_MSG_LEN 1024
#define LOG_FILE "logs/pubsub.log"

typedef struct {
    char sender[64];
    char topic[64];
    char message[MAX_MSG_LEN];
} message_t;

#endif
