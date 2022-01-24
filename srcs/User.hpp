#pragma once

#include "ft_irc.hpp"

class Channel;

class User{
    public:
        User(int socketFd);
        User();
        ~User();
        /* setters */
        void    setSocket(int);
        void    setChannel(Channel *);
        void    setUsername(std::string);
        void    setNickname(std::string);
        void    setPassword(std::string);
        void    setPermLevel(int);
        void    setAccepted(bool);
        /* getters */
        int         getSocket() const;
        Channel     *getChannel();
        std::string getUsername() const;
        std::string getNickname() const;
        std::string getPassword() const;
        char *      getBuffer();
        int         getPermLevel() const;
        bool        getAccepted() const;
        /* public variable */
    public:
        pthread_t   thread;
		std::string	tmp_buffer;

    private:
        int         _socketFD;
        Channel     *_channel;
        std::string _username;
        std::string _nickname;
        std::string _password;
        char        _buffer[1024];
        int         _permLevel;// 0 for user 1 for operator 2 for admin everywhere
        bool        _accepted;
};

std::ostream &operator<<(std::ostream &lhs, const User &rhs);