/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trofidal <trofidal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 02:07:21 by trofidal          #+#    #+#             */
/*   Updated: 2022/01/09 09:57:54 by trofidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"
#include "Server.hpp"

/*
./ircserv [host:port_network:password_network] <port> <password>
*/

class User;

Data::Data() : _host(0), _portNetwork(0), _passwordNetwork("undefined"), _port(0), _password("undefined"), _server(0){
    std::cout << red << "/!\\ Default Constructor used, private values set to 'undefined' or 0" << ncolor;
}

Data::Data(std::string const &host, unsigned int portNetwork, std::string const &passwordNetwork, unsigned int port, std::string const &password){
    this->_host = host;
    this->_portNetwork = portNetwork;
    this->_passwordNetwork = passwordNetwork;
    this->_port = port;
    this->_password = password;
}

Data::~Data(){
    return ;
}


void    Data::setHost(std::string const &host){
    this->_host = host;
}

void    Data::setPortNetwork(unsigned int portNetwork){
    this->_portNetwork = portNetwork;
}

void    Data::setPasswordNetwork(std::string const &passwordNetwork){
    this->_passwordNetwork = passwordNetwork;
}

void    Data::setPort(unsigned int port){
    this->_port = port;
}

void    Data::setPassword(std::string const &password){
    this->_password = password;
}

void    Data::setSocket(int socket){
    this->_socketFd = socket;
}

void    Data::setServer(Server *server){
    this->_server = server;
}

std::string Data::getHost() const{
    return (this->_host);
}

Server*     Data::getServer(){
    return (this->_server);
}

std::vector<Channel *>  &Data::getChannels(){
    return (this->_channels);
}

std::vector<int> &Data::getClientsFDs(){
    return (this->_ClientFDs);
}

std::vector<User *>           &Data::getUsers(){
    return (this->_users);
}

int         Data::getPortNetwork() const{
    return (this->_portNetwork);
}

std::string Data::getPasswordNetwork() const{
    return (this->_passwordNetwork);
}

int         Data::getPort() const{
    return (this->_port);
}

std::string Data::getPassword() const{
    return (this->_password);
}

int Data::getSocket() const{
    return (this->_socketFd);
}

std::ostream &operator<<(std::ostream &lhs, const Data &rhs){
    lhs << 
    "Host : [" << rhs.getHost() << "]" << std::endl <<
    "Port Network : [" << rhs.getPortNetwork() << "]" << std::endl <<
    "Network Password : [" << rhs.getPasswordNetwork() << "] " << std::endl << 
    "Port : [" << rhs.getPort() << "]" << std::endl << 
    "Password : [" << rhs.getPassword() << "]";
    return (lhs);
}