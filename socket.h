#ifndef BS1SS17KLIMMSTRUTZWOLF_SOCKET_H
#define BS1SS17KLIMMSTRUTZWOLF_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h> //FÜR UNIX
#include <netinet/in.h> //FÜR UNIX
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include "store_tools.h"
#include <sys/sem.h>
#include <string.h>

int start();
int pid;


#endif //BS1SS17KLIMMSTRUTZWOLF_SOCKET_H
