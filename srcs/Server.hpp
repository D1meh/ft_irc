#pragma once

#include "ft_irc.hpp"
#include "Data.hpp"
#include "Server.hpp"

class Channel;
class User;

enum protocole_code{
    RPL_WELCOME = 1, //sent on accepted user joining.
    RPL_TRYAGAIN = 263, //on error encountered by lib functions
    RPL_TOPIC = 332,
    RPL_NAMREPLY = 353,
    ERR_TOOMANYCHANNELS = 405, //too many channel
    ERR_NOSUCHNICK = 401, //for no such nick channel
    ERR_NOSUCHCHANNEL = 403, //no such channel
    ERR_PASSWDMISMATCH = 464 //wrong password
};

class Server{
    public:
        Server();
        ~Server();

    /* usefull functions */
    static bool    isSocketReady(int socketfd);

    /* setters */
    void    setSocket(int socketFD);
    /* getters */
    int getSocket() const;
    struct sockaddr_in *getSockAddr() const;
    struct hostent *getHost() const;
    struct addrinfo *getAddrinfo() const;
    struct pollfd *getPollfd() const;

    private:
    int             _socketFD;
    struct sockaddr_in *_name;
    struct hostent  *_host;
    struct addrinfo *_addrinfo; //utiliser bind(this->_socketFD, this->_addrinfo, this->_socketLen)
    struct pollfd   *_pollfd; //used only with the poll function so far
};

std::ostream &operator<<(std::ostream &lhs, const Server &rhs);