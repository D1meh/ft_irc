/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trofidal <trofidal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 02:07:19 by trofidal          #+#    #+#             */
/*   Updated: 2022/01/05 03:17:50 trofidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
# define DATA_HPP

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "Server.hpp"
/*
./ircserv [host:port_network:password_network] <port> <password>
*/

class Server;
class User;
class Channel;

class Data{
    public:
        Data(std::string const &, unsigned int, std::string const &, unsigned int, std::string const &); /* constructor setting on construction */
        ~Data();

        /* setters */
        void        setHost(std::string const &);
        void        setPortNetwork(unsigned int);
        void        setPasswordNetwork(std::string const &);
        void        setPort(unsigned int);
        void        setPassword(std::string const &);
        void        setServer(Server *);
        void        setSocket(int);
        /* getters */
        std::string getHost() const;
        int         getPortNetwork() const;
        std::string getPasswordNetwork() const;
        int         getPort() const;
        std::string getPassword() const;
        int         getSocket() const;
        Server*     getServer();
        std::vector<Channel *>      &getChannels();
        std::vector<User *>           &getUsers();
        std::vector<int>           &getClientsFDs();

    private:
        Data(); /* default constructor, will cout a warning message for not setting default parameters */
        /* private members sorted in the main arguments order */
        std::string     _host;
        unsigned int    _portNetwork; //port must be a positive integer so i use unsigned
        std::string     _passwordNetwork;
        unsigned int    _port;
        std::string     _password;
        int             _socketFd;
        Server * _server;
        std::vector<Channel *> _channels;
        std::vector<User *> _users;
        std::vector<int> _ClientFDs;

};

std::ostream &operator<<(std::ostream &lhs, const Data &rhs);

#endif