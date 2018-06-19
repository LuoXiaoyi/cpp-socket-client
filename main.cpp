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

#define BUFFER_SIZE 1024

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    string path = "/tmp/socket/socket.tmp";
    client c;
    int client_fd = c.open_clientfd(path);
    if (client_fd < 0) {
        cerr << "client created error." << endl;
        return -1;
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
        return -1;
    }

    cout << "receive count: " << count << endl;

    str = "";
    str.append(buffer, count);
    cout << "client receive response: " << str << endl;

    return 0;
}

