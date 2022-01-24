/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trofidal <trofidal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 09:38:27 by trofidal          #+#    #+#             */
/*   Updated: 2022/01/09 08:29:38trofidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

extern Data *g_ptr;

Server::Server(){
    this->_addrinfo = new struct addrinfo;
    this->_host = new struct hostent;
    this->_name = new struct sockaddr_in;
    return ;
}

Server::~Server(){
    delete this->_addrinfo;
    delete this->_host;
    delete this->_name;
}

//"001 ft_irc.42.fr\n\"Welcome to the Internet Relay Chat Network\ntrofidal!trofidal@localhost\""



bool    Server::isSocketReady(int socketfd){
    fd_set sready;
    int res;
    struct timeval nowait;
    FD_ZERO(&sready);
    FD_SET((unsigned int)socketfd, &sready);
    nowait.tv_sec = 0;
    nowait.tv_usec = 0;
    memset((char *)&nowait, 0, sizeof(&sready));
    res = select(socketfd + 1, &sready, NULL, NULL, &nowait);
    if (res < 0){
        std::cout << red << "Error in isSocketReady, exiting." << ncolor << std::endl;
        fprintf(stderr, "\nErrno : [%s]\n", strerror(errno));
        throw(std::runtime_error("CRITICAL ERROR IN SOCKET READY\n"));
    }
    if (FD_ISSET(socketfd, &sready))
        return (true);
    return (false);
}

void    Server::setSocket(int socketFD){
    this->_socketFD = socketFD;
}
int     Server::getSocket() const{
    return (this->_socketFD);
}
/*
socklen_t   Server::getSocketLen() const{
    return (this->_socketLen);
}
*/
struct sockaddr_in *Server::getSockAddr() const{
    return (this->_name);
}

struct hostent *Server::getHost() const{
    return (this->_host);
}

struct addrinfo *Server::getAddrinfo() const{
    return (this->_addrinfo);
}

std::ostream &operator<<(std::ostream &lhs, const Server &rhs){
    lhs << 
    "Host : [" << rhs.getHost() << "]";
    return (lhs);
}