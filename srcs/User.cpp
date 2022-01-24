#include "User.hpp"

User::User(){
    this->_socketFD = 0;
    this->_username = "User";
    this->_nickname = "Nick";
    this->_accepted = true;
    bzero(this->_buffer, BUFF_SIZE);
    return ;
}

User::~User(){
    std::cout << cyan << "User " << getNickname() << " has left." << ncolor << std::endl;
}

User::User(int socketFD) : _channel(0), _password("undefined"), _permLevel(0){
    this->_socketFD = socketFD;
    this->_username = "User";
    this->_nickname = "Nick";
    this->_accepted = true;
    bzero(this->_buffer, BUFF_SIZE);
	// if (socketFD == 4)
	//  	this->_username = "@" + this->_username;
}

std::ostream &operator<<(std::ostream &lhs, const User &rhs){
    lhs << 
    "Is accepted :" << (rhs.getAccepted() ? "true" : "false") << std::endl <<
    "Socket :" << rhs.getSocket() << std::endl <<
    "Nick :" << rhs.getNickname() << std::endl <<
    "Username :" << rhs.getUsername() << std::endl << 
    "Password :" << rhs.getPassword() << std::endl <<
    "Perm level :" << rhs.getPermLevel() << std::endl;
    return (lhs);
}

void    User::setAccepted(bool accepted){
    this->_accepted = accepted;
}

void    User::setSocket(int socket){
    this->_socketFD = socket;
}

void    User::setChannel(Channel *channel){
    this->_channel = channel;
}

void    User::setUsername(std::string username){
    this->_username = username;
} 

void    User::setNickname(std::string nickname){
    this->_nickname = nickname;
}

void    User::setPassword(std::string password){
    this->_password = password;
}

void    User::setPermLevel(int level){
    this->_permLevel = level;
}

char *  User::getBuffer(){
    return (this->_buffer);
}

int    User::getSocket() const{
    return (this->_socketFD);
}
Channel    *User::getChannel(){
    return (this->_channel);
}

std::string    User::getUsername() const{
    return (this->_username);
}

std::string    User::getNickname() const{
    return (this->_nickname);
}

std::string    User::getPassword() const{
    return (this->_password);
}
int    User::getPermLevel() const{
    return (this->_permLevel);
}

bool    User::getAccepted() const{
    return (this->_accepted);
}