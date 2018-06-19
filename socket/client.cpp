/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   client.cpp
 * Author: xiaoyiluo
 * 
 * Created on June 19, 2018, 12:56 PM
 */

#include "client.h"

client::client() {
}

client::client(const client& orig) {
}

int client::open_clientfd(string path) {
    // create socket
    int client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    printf("client_fd %d \n", client_fd);

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, path.data());

    int res = connect(client_fd, (struct sockaddr*) &addr, sizeof (addr));
    printf("connect res: %d \n", res);

    return client_fd;
}

client::~client() {
}

