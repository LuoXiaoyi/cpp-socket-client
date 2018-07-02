/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   poll_client.h
 * Author: xiaoyiluo
 *
 * Created on June 24, 2018, 5:40 PM
 */

#ifndef POLL_CLIENT_H
#define POLL_CLIENT_H
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define MAXLINE     1024
#define IPADDRESS   "127.0.0.1"
#define SERV_PORT   8080

#define max(a,b) (a > b) ? a : b

class poll_client {
public:
    poll_client();
    poll_client(const poll_client& orig);
    virtual ~poll_client();
    int socket_bind(const char* ip, int port);
    void handle_connection(int sockfd);
};

#endif /* POLL_CLIENT_H */

