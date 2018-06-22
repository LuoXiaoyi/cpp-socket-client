/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: xiaoyiluo
 *
 * Created on June 19, 2018, 12:55 PM
 */

#include <cstdlib>
#include <iostream>
#include "socket/client.h"
#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<errno.h>  
#include<sys/types.h>
#include<sys/socket.h>  
#include<netinet/in.h>
#include <unistd.h> 
#include <arpa/inet.h> 
  
#define MAXLINE 4096 
#define BUFFER_SIZE 1024

using namespace std;

void internet_socket_client(int argc, char** argv){
    int sockfd, n,rec_len;  
    char recvline[4096], sendline[4096];  
    char buf[MAXLINE];  
    struct sockaddr_in servaddr;  
  
    if( argc != 2){  
        printf("usage: ./client <ipaddress>\n");  
        exit(0);  
    }  
  
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){  
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);  
        exit(0);  
    }  
  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(8000);  
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){ //inet_pton是Linux下IP地址转换函数，将IP地址在“点分十进制”和“整数”之间转换
        printf("inet_pton error for %s\n",argv[1]);  
        exit(0);  
    }  
   
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){  
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
    }  
  
    printf("send msg to server: \n");  
    fgets(sendline, 4096, stdin);  
    if( send(sockfd, sendline, strlen(sendline), 0) < 0)  {  
        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);  
        exit(0);  
    }  
    if((rec_len = recv(sockfd, buf, MAXLINE,0)) == -1) {  
       perror("recv error");  
       exit(1);  
    }  
    buf[rec_len]  = '\0';  
    printf("Received : %s ",buf);  
    close(sockfd);
}

void file_socket_client(){
    string path = "/tmp/socket/socket.tmp";
    client c;
    int client_fd = c.open_clientfd(path);
    if (client_fd < 0) {
        cerr << "client created error." << endl;
        return;
    }

    cout << "client_fd: " << client_fd << endl;
    string str = "hello world";
    send(client_fd, str.data(), strlen(str.data()), 0);
    cout << "send: " << str << " to the server" << endl;

    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);
    // 阻塞在这里
    ssize_t count = recv(client_fd, buffer, BUFFER_SIZE, 0);

    if (count < 0) {
        cout << "Client Recieve Data Failed!" << endl;
        return;
    }

    cout << "receive count: " << count << endl;

    str = "";
    str.append(buffer, count);
    cout << "client receive response: " << str << endl;
}
/*
 * 
 */
int main(int argc, char** argv) {
    // file_socket_client();
    internet_socket_client(argc,argv);
    return 0;
}

