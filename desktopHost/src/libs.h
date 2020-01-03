/*
//Author:Azfar C
//FileName:libs.h
//Purpose:collection of all external libraries required by the Limerick desktop host
*/
#ifndef LIBS_H
#define LIBS_H

#include <stdio.h> //basic i/o
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h> //POSIX used for sockets threading and i/o
#include <sys/ioctl.h>
#include <net/if.h>

#include <pthread.h>

#include <gtk/gtk.h>

#endif