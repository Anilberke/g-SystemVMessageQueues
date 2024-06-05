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
    int msqid1;
    key_t key1;
    message_buf sbuf, rbuf;
    size_t buf_length;
    char operation[10], filename[MSGSZ], data[MSGSZ];

    key1 = 1234;

    // Get the message queue id for msgq1
    if ((msqid1 = msgget(key1, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    printf("Enter operation (read/write): ");
    scanf("%s", operation);
    printf("Enter filename: ");
    scanf("%s", filename);

    if (strcmp(operation, "write") == 0) {
        printf("Enter data to write: ");
        scanf("%s", data);
        sprintf(sbuf.mtext, "write %s %s", filename, data);
    } else {
        sprintf(sbuf.mtext, "read %s", filename);
    }

    sbuf.mtype = 1;
    buf_length = strlen(sbuf.mtext) + 1;

    // Send the request to the server
    if (msgsnd(msqid1, &sbuf, buf_length, 0) < 0) {
        printf("%d, %ld, %s, %zu\n", msqid1, sbuf.mtype, sbuf.mtext, buf_length);
        perror("msgsnd");
        exit(1);
    }

    // Receive the response from the server
    if (msgrcv(msqid1, &rbuf, MSGSZ, 2, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    printf("Client received: %s\n", rbuf.mtext);

    return 0;
}
