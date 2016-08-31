/* Author: Gopi Krishna Marella.
 * Date : 08/25/2016.
 *
 * File name: client_socket.c
 *
 * A simple client side application code to demonstrate the Unix domain sockets(IPC).
 */

#include <my_socket_common.h>

static inline int is_quit_command(char *buff)
{
    if (!strcmp(buff, CLI_QUIT_STR)) {
        return 1;
    } else if (!strcmp(buff, CLI_EXIT_STR)) {
        return 1;
    } else if (strlen(buff) == 1) {
        if (buff[0] == 'q' || buff[0] == 'Q') {
            return 1;
        }
    }

    return 0;
}

int main()
{
    int socket_desc;
    int len;
    int read_bytes = 0;
    char buff[1024];
    struct sockaddr_un serv_addr;

    socket_desc = socket(AF_UNIX, SOCK_STREAM, 0);
    if (-1 == socket_desc) {
        perror("Socket creation");
        exit(-1);
    }

    memset(&serv_addr, 0, sizeof(struct sockaddr_un));
    serv_addr.sun_family = AF_UNIX;
    len = sprintf(serv_addr.sun_path, GOPI_SERV_SOCKET_PATH);
    len += sizeof(serv_addr.sun_family);

    if (connect(socket_desc, (struct sockaddr *)&serv_addr, len) == -1) {
        perror("Connection request:");
        exit(-1);
    }

    /* Socket connection is succesful */
    while(!feof(stdin)) {
        printf(CLI_PROMPT);
        fgets(buff, sizeof(buff), stdin);
        buff[strlen(buff)-1] = '\0';
        if (is_quit_command(buff)) {
            printf("Exiting the prompt and closing the application.\n");
            break;
        }

        /* Send the message to the server */
        if (send(socket_desc, buff, strlen(buff), 0) == -1) {
            perror("Socket send failed");
            exit(-1);
        }
        /* Wait for the reply */
        read_bytes = recv(socket_desc, buff, sizeof(buff), 0);
        if (read_bytes > 0) {
            printf("%sReceived: %s\n", CLI_PROMPT, buff);
        } else if (read_bytes < 0) {
            perror("Socket recv failed");
            exit(-1);
        } else {
            printf("Server closed the connection.");
            exit(1);
        }
    }
    return 0;
}
