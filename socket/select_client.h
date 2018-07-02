/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   select_client.h
 * Author: xiaoyiluo
 *
 * Created on June 23, 2018, 9:27 PM
 */

#ifndef SELECT_CLIENT_H
#define SELECT_CLIENT_H
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <arpa/inet.h>

#define MAX_LINE 1024
#define IP_ADDRESS "127.0.0.1"
#define SERV_PORT 8080

#define max(a,b) (a > b) ? a : b

class select_client {
public:
    select_client();
    select_client(const select_client& orig);
    virtual ~select_client();

    void get_response_from_server();
    int connect_server();
    int send_msg(const char* msg);
private:
    int client_fd;
};

#endif /* SELECT_CLIENT_H */

