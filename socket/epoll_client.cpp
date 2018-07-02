/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   epoll_client.cpp
 * Author: xiaoyiluo
 * 
 * Created on June 24, 2018, 9:32 PM
 */

#include "epoll_client.h"

epoll_client::epoll_client() {
}

void epoll_client::do_connect(const char * ip, int port) {
    this->client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->client_fd < 0) {
        perror("create socket error.");
        exit(1);
    }

    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof (server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    int ret = connect(client_fd, (sockaddr*) & server_addr, sizeof (sockaddr_in));
    if (ret < 0) {
        perror("connect error");
        fprintf(stderr, "connect to server [%s:%d] error \n", ip, port);
        exit(1);
    }

    fprintf(stdout, "connect to server [%s:%d] success. \n", ip, port);
}

void epoll_client::handle_connection() {
    int epoll_fd = epoll_create(FDSIZE);
    if (epoll_fd < 0) {
        perror("create epoll fd error");
        exit(1);
    }

    epoll_event events[EPOLLEVENTS];
    char buf[MAXSIZE];
    // 添加 标准输入流 的读事件
    add_event(epoll_fd, STDIN_FILENO, EPOLLIN);
    while (1) {
        //获取已经准备好的描述符事件
        int ret = epoll_wait(epoll_fd, events, EPOLLEVENTS, -1);
        if (ret < 0) {
            perror("epoll_wait error");
            continue;
        }
        this->handle_events(epoll_fd, events, ret, this->client_fd, buf);
    }

    close(epoll_fd);
}

void epoll_client::add_event(int epollfd, int fd, int eve) {
    epoll_event event;
    event.events = eve;
    event.data.fd = fd;
    int res = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);

    if (res < 0) {
        fprintf(stderr, "Adding event[%d] of fd[%d] to epoll_fd[%d] error \n", eve, fd, epollfd);
        perror("event add error");
        exit(1);
    }

    fprintf(stdout, "Adding event[%d] of fd[%d] to epoll_fd[%d] success \n", eve, fd, epollfd);
}

void epoll_client::delete_event(int epollfd, int fd, int eve) {
    epoll_event event;
    event.events = eve;
    event.data.fd = fd;
    int res = epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &event);

    if (res < 0) {
        fprintf(stderr, "Deleting event[%d] of fd[%d] to epoll_fd[%d] error \n", eve, fd, epollfd);
        perror("event delete error");
        exit(1);
    }

    fprintf(stdout, "Deleting event[%d] of fd[%d] to epoll_fd[%d] success \n", eve, fd, epollfd);
}

void epoll_client::modify_event(int epollfd, int fd, int eve) {
    epoll_event event;
    event.events = eve;
    event.data.fd = fd;
    int res = epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);

    if (res < 0) {
        fprintf(stderr, "Modifing event[%d] of fd[%d] to epoll_fd[%d] error \n", eve, fd, epollfd);
        perror("event modify error");
        exit(1);
    }

    fprintf(stdout, "Modifing event[%d] of fd[%d] to epoll_fd[%d] success \n", eve, fd, epollfd);
}

void epoll_client::handle_events(int epollfd, struct epoll_event *events, int num, int sockfd, char *buf) {
    int fd;
    int i;
    for (i = 0; i < num; i++) {
        fd = events[i].data.fd;
        if (events[i].events & EPOLLIN)
            do_read(epollfd, fd, sockfd, buf);
        else if (events[i].events & EPOLLOUT)
            do_write(epollfd, fd, sockfd, buf);
    }
}

void epoll_client::do_read(int epollfd, int fd, int sockfd, char* buf) {
    int nread = read(fd, buf, MAXSIZE);
    if (nread == -1) {
        perror("read error");
        close(fd);
    } else if (nread == 0) {
        fprintf(stderr, "server close.\n");
        close(fd);
    } else {
        if (fd == STDIN_FILENO)
            add_event(epollfd, sockfd, EPOLLOUT);
        else {
            delete_event(epollfd, fd, EPOLLIN);
            add_event(epollfd, STDOUT_FILENO, EPOLLOUT);
        }
    }
}

void epoll_client::do_write(int epollfd, int fd, int sockfd, char *buf) {
    int nwrite;
    nwrite = write(fd, buf, strlen(buf));
    if (nwrite == -1) {
        perror("write error:");
        close(fd);
    } else if(nwrite == 0) {
        fprintf(stderr, "server close.\n");
        close(fd);
    } else{
        if (fd == STDOUT_FILENO)
            delete_event(epollfd, fd, EPOLLOUT);
        else
            modify_event(epollfd, fd, EPOLLIN);
    }
    memset(buf, 0, MAXSIZE);
}

epoll_client::epoll_client(const epoll_client& orig) {
}

epoll_client::~epoll_client() {
}

