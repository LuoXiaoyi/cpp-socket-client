/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   epoll_client.h
 * Author: xiaoyiluo
 *
 * Created on June 24, 2018, 9:32 PM
 */

#ifndef EPOLL_CLIENT_H
#define EPOLL_CLIENT_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define MAXSIZE     1024
#define IPADDRESS   "127.0.0.1"
#define SERV_PORT   8080
#define FDSIZE        1024
#define EPOLLEVENTS 20

class epoll_client {
public:
    epoll_client();
    epoll_client(const epoll_client& orig);
    virtual ~epoll_client();

    void do_connect(const char* ip, int port);
    void handle_connection();
    void handle_events(int epollfd, struct epoll_event *events, int num, int sockfd, char *buf);
    void do_read(int epollfd, int fd, int sockfd, char *buf);
    void do_write(int epollfd, int fd, int sockfd, char *buf);
    void add_event(int epollfd, int fd, int state);
    void delete_event(int epollfd, int fd, int state);
    void modify_event(int epollfd, int fd, int state);
private:
    int client_fd;
};

#endif /* EPOLL_CLIENT_H */

