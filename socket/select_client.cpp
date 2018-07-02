/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   select_client.cpp
 * Author: xiaoyiluo
 * 
 * Created on June 23, 2018, 9:27 PM
 */

#include "select_client.h"

select_client::select_client() : client_fd(-1) {
    
}

void select_client::get_response_from_server() {
    char recv_content[MAX_LINE];

    int max_fd = this->client_fd;
    fd_set read_fds;
    int n;
    timeval tv;
    int ret_val = 0;
    while (1) {
        FD_ZERO(&read_fds);
        
        FD_SET(max_fd, &read_fds);
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        ret_val = select(max_fd + 1, &read_fds, NULL, NULL, &tv);

        if (ret_val == -1) {
            break;
        }

        if (ret_val == 0) {
            printf("process %d client select timeout.\n",getpid());
            continue;
        }

        if (FD_ISSET(this->client_fd, &read_fds)) {
            n = read(this->client_fd, recv_content, MAX_LINE);
            if (n < 0) {
                fprintf(stderr, "client: server is closed.\n");
                FD_CLR(this->client_fd, &read_fds);
                break;
            }

            printf("client recv msg is:%s\n", recv_content);
            break;
            //write(this->client_fd, recv_content, strlen(recv_content) + 1);
        }
    }


}

int select_client::connect_server() {
    struct sockaddr_in servaddr;
    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof (servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, IP_ADDRESS, &servaddr.sin_addr);

    int retval = 0;
    retval = connect(client_fd, (struct sockaddr*) &servaddr, sizeof (servaddr));
    if (retval < 0) {
        fprintf(stdout, "connect fail,error:%s\n", strerror(errno));
        return 0;
    }
    printf("process %d client connect to server success.\n",getpid());
    return 1;
}

int select_client::send_msg(const char* msg) {
    if (msg == NULL) return 0;
    write(this->client_fd, msg, strlen(msg));
    printf("process: %d client send msg [ %s ] to server .\n",getpid(), msg);
    return 1;
}

select_client::select_client(const select_client& orig) {
}

select_client::~select_client() {
    if (client_fd > 0) {
        close(client_fd);
        client_fd = -1;
    }
}

