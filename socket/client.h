/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   client.h
 * Author: xiaoyiluo
 *
 * Created on June 19, 2018, 12:56 PM
 */

#ifndef CLIENT_H
#define CLIENT_H


#ifndef UNIX_PATH_MAX
#define UNIX_PATH_MAX   sizeof(((struct sockaddr_un *)0)->sun_path)
#endif

#include <netinet/in.h>    // for sockaddr_in  
#include <sys/types.h>    // for socket  
#include <sys/socket.h>    // for socket  
#include <stdio.h>        // for printf  
#include <stdlib.h>        // for exit  
#include <string.h>        // for bzero 
#include <sys/un.h>
#include <cstring>
#include <string>
#include <errno.h>

using namespace std;

class client {
public:
    client();
    client(const client& orig);
    virtual ~client();
    int open_clientfd(string path);
private:

};

#endif /* CLIENT_H */

