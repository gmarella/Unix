/* Author: Gopi Krishna Marella.
 * Date : 08/25/2016.
 *
 * File name: server_socket.c
 *
 * A simple server side application code to demonstrate the Unix domain sockets(IPC).
 */

#include <my_socket_common.h>

void handle_incoming_request(int sd)
{
    char recv_buff[1024];
    int recv_bytes = 0;
    int close_conn = 0;

    while(!close_conn) {
        recv_bytes = recv(sd, recv_buff, sizeof(recv_buff), 0);
        if (recv_bytes <= 0) {
            close_conn = 1;
        }

        if (!close_conn) {
            /* Let's send a message back to the client */
            recv_bytes = sprintf(recv_buff, "I hear you!!, let me get back to you.");
            if (send(sd, recv_buff, recv_bytes, 0) < 0) {
                perror("send");
                close_conn = 1;
            }
        }
    }
}

int main()
{
    int local_sock_desc;
    int remote_sock_desc;
    int len;
    struct sockaddr_un local_sock_addr;
    struct sockaddr_un remote_sock_addr;

    local_sock_desc = socket(AF_UNIX, SOCK_STREAM, 0);
    if (-1 == local_sock_desc) {
        perror("Socket creation:socket");
        exit(-1);
    }

    memset(&local_sock_addr, 0, sizeof(struct sockaddr_un));
    local_sock_addr.sun_family = AF_UNIX;
    len = sprintf(local_sock_addr.sun_path, GOPI_SERV_SOCKET_PATH);
    len += sizeof(local_sock_addr.sun_family);

    /* Bind the socket descriptor to the socket address. This creates a named socket.
     * First unlink if there already exits one for the given path.*/
    unlink(local_sock_addr.sun_path);

    if (bind(local_sock_desc, (struct sockaddr *)&local_sock_addr, len) == -1) {
        perror("Socket bind:bind");
        exit(-1);
    }

    /* Since our socket is of type SOCK_STREAM, let's set the outstanding connect requests */
    if (listen(local_sock_desc, CLI_MAX_QUEUE_REQS) == -1) {
        perror("Listen");
        exit(-1);
    }

    while(1) {
        /* Wait for the incoming connections */
        printf("Waiting for the connections.\n");
        remote_sock_desc = accept(local_sock_desc, (struct sockaddr *)&remote_sock_addr, (socklen_t *)&len);
        if (remote_sock_desc == -1) {
            perror("Accept");
            exit(-1);
        }

        printf("Connection is succesful.\n");
        /* Let's hear out this client */
        handle_incoming_request(remote_sock_desc);
        shutdown(remote_sock_desc, SHUT_RDWR);
    }

    return 0;
}

