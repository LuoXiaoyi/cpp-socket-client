/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   poll_client.cpp
 * Author: xiaoyiluo
 * 
 * Created on June 24, 2018, 5:40 PM
 */

#include "poll_client.h"

poll_client::poll_client() {
}

int poll_client::socket_bind(const char* ip, int port) {
    printf("%d client begin to connect to: %s:%d. \n", getpid(), ip, port);
    int sockfd;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof (servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &servaddr.sin_addr);
    int ret = connect(sockfd, (struct sockaddr*) &servaddr, sizeof (servaddr));

    if (ret == -1) {
        perror("connect error");
        return -1;
    }
    printf("%d client connect to: %s:%d success. \n", getpid(), ip, port);
    return sockfd;
}

void poll_client::handle_connection(int sockfd) {
    char sendline[MAXLINE], recvline[MAXLINE];
    struct pollfd pfds[2];
    int n;
    //添加连接描述符
    pfds[0].fd = sockfd;
    pfds[0].events = POLLIN;
    //添加标准输入描述符
    pfds[1].fd = STDIN_FILENO;
    pfds[1].events = POLLIN;
    for (;;) {
        poll(pfds, 2, -1);
        if (pfds[0].revents & POLLIN) {
            n = read(sockfd, recvline, MAXLINE);
            if (n == 0) {
                fprintf(stderr, "client: server is closed.\n");
                close(sockfd);
            }
            write(STDOUT_FILENO, recvline, n);
        }
        //测试标准输入是否准备好
        if (pfds[1].revents & POLLIN) {
            n = read(STDIN_FILENO, sendline, MAXLINE);
            if (n == 0) {
                shutdown(sockfd, SHUT_WR);
                continue;
            }
            write(sockfd, sendline, n);
        }
    }
}

poll_client::poll_client(const poll_client& orig) {
}

poll_client::~poll_client() {
}

