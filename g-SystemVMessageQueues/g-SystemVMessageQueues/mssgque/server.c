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
    int msqid1, msqid2;
    key_t key1, key2;
    message_buf sbuf, rbuf;
    size_t buf_length;

    key1 = 1234;
    key2 = 5678;

    // Create the first message queue
    if ((msqid1 = msgget(key1, IPC_CREAT | 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    // Create the second message queue
    if ((msqid2 = msgget(key2, IPC_CREAT | 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    while (1) {
        // Receive a request from a client
        if (msgrcv(msqid1, &rbuf, MSGSZ, 1, 0) < 0) {
            perror("msgrcv");
            exit(1);
        }

        printf("Server received request: %s\n", rbuf.mtext);

        // Forward the request to the appropriate process (Read/Write) via msgq2
        sbuf.mtype = 1;
        strcpy(sbuf.mtext, rbuf.mtext);
        buf_length = strlen(sbuf.mtext) + 1;

        if (msgsnd(msqid2, &sbuf, buf_length, 0) < 0) {
            printf("%d, %ld, %s, %zu\n", msqid2, sbuf.mtype, sbuf.mtext, buf_length);
            perror("msgsnd");
            exit(1);
        }

        // Receive the result from the Read/Write process via msgq2
        if (msgrcv(msqid2, &rbuf, MSGSZ, 2, 0) < 0) {
            perror("msgrcv");
            exit(1);
        }

        printf("Server received result: %s\n", rbuf.mtext);

        // Send the result back to the client via msgq1
        sbuf.mtype = 2;
        strcpy(sbuf.mtext, rbuf.mtext);
        buf_length = strlen(sbuf.mtext) + 1;

        if (msgsnd(msqid1, &sbuf, buf_length, 0) < 0) {
            printf("%d, %ld, %s, %zu\n", msqid1, sbuf.mtype, sbuf.mtext, buf_length);
            perror("msgsnd");
            exit(1);
        }
    }

    return 0;
}
