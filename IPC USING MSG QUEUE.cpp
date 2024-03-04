#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Define the message structure
struct message {
    long mtype;
    char mtext[100];
};

int main() {
    // Create a unique key for the message queue
    key_t key = ftok("message_queue_example", 65);

    // Create a message queue, or get the ID if it already exists
    int msgid = msgget(key, 0666 | IPC_CREAT);

    // Define a message to send
    struct message msg;
    msg.mtype = 1;
    strcpy(msg.mtext, "Hello from Process 1");

    // Send the message to the queue
    msgsnd(msgid, &msg, sizeof(msg), 0);

    printf("Message sent: %s\n", msg.mtext);

    // Receive the message from the queue
    msgrcv(msgid, &msg, sizeof(msg), 1, 0);

    printf("Message received: %s\n", msg.mtext);

    // Destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
