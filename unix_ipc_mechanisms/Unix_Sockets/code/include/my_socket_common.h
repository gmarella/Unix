/* Author: Gopi Krishna Marella.
 * Date: 08/25/2016.
 */

#ifndef __MY_SOCKET_COMMON_H
#define __MY_SOCKET_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

#define GOPI_SERV_SOCKET_PATH   "gopi_socket"
#define CLI_MAX_QUEUE_REQS      (10)

#define CLI_PROMPT      ">> "
#define CLI_QUIT_STR    "quit"
#define CLI_EXIT_STR    "exit"


#endif
