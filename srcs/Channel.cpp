#include "Channel.hpp"

Channel::Channel(){
    return ;
}

Channel::~Channel(){
    return ;
}

Channel::Channel(int socketFD, int port, std::string hostname, std::string password){
    this->_socketFD = socketFD;
    this->_port = port;
    this->_hostname = hostname;
    this->_password = password;
	this->_topic = "";
}

void    Channel::setSocket(int socket){
    this->_socketFD = socket;
}

void    Channel::setPort(int port){
    this->_port = port;
}

void    Channel::setHostName(std::string hostname){
    this->_hostname = hostname;
}

void    Channel::setPassword(std::string password){
    this->_password = password;
}

void	Channel::setTopic(std::string topic){
	this->_topic = topic;
}

int     Channel::getSocket() const{
    return (this->_socketFD);
}

int     Channel::getPort() const{
    return (this->_port);
}

std::string Channel::getHostName() const{
    return (this->_hostname);
}

std::string Channel::getPassword() const{
    return (this->_password);
}

std::string Channel::getTopic() const{
	return (this->_topic);
}

std::vector<User *> &Channel::getMembers(){
    return (this->_members);
}