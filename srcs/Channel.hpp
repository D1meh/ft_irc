#pragma once

#include "ft_irc.hpp"

class User;

class Channel{
    public:
        Channel(int socketFD, int port, std::string hostname, std::string password);
        Channel();
        ~Channel();

        void    setSocket(int);
        void    setPort(int);
        void    setHostName(std::string);
        void    setPassword(std::string);
		void	setTopic(std::string);

        int     getSocket() const;
        int     getPort() const;
        std::string getHostName() const;
        std::string getPassword() const;
		std::string getTopic() const;
        std::vector<User *> &getMembers();

    private:
        int                 _socketFD;
        int                 _port;
        std::string         _hostname;
        std::string         _password;
		std::string			_topic;
        std::vector<User *> _members;
};