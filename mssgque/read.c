#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSGSZ 128

typedef struct msgbuf {
    long mtype;
    char mtext[MSGSZ];
} message_buf;

int main() {
    int msqid2;
    key_t key2;
    message_buf rbuf, sbuf;
    FILE *file;
    size_t buf_length;

    key2 = 5678;

    // Get the message queue id for msgq2
    if ((msqid2 = msgget(key2, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    while (1) {
        // Receive a request from the server
        if (msgrcv(msqid2, &rbuf, MSGSZ, 1, 0) < 0) {
            perror("msgrcv");
            exit(1);
        }

        printf("Read process received request: %s\n", rbuf.mtext);

        // Extract filename from the request
        char filename[MSGSZ];
        sscanf(rbuf.mtext, "read %s", filename);

        // Read the file
        file = fopen(filename, "r");
        if (file == NULL) {
            perror("fopen");
            sprintf(sbuf.mtext, "Error opening file %s", filename);
        } else {
            fread(sbuf.mtext, sizeof(char), MSGSZ, file);
            fclose(file);
        }

        // Send the result back to the server
        sbuf.mtype = 2;
        buf_length = strlen(sbuf.mtext) + 1;

        if (msgsnd(msqid2, &sbuf, buf_length, 0) < 0) {
            printf("%d, %ld, %s, %zu\n", msqid2, sbuf.mtype, sbuf.mtext, buf_length);
            perror("msgsnd");
            exit(1);
        }
    }

    return 0;
}
