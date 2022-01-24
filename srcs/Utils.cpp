#include "Utils.hpp"

std::string utils::get_protocole_message(int protocole, Channel *channel, User *user){
    static int i = 0;
    i++;
    if (protocole == RPL_WELCOME){
        return (std::string("001 " + user->getNickname() + "\n\"Welcome to the Internet Relay Chat Network\"\n" + user->getNickname() + 
        "!" + user->getUsername() + "@" + "localhost" + "\""));
    }
    if (protocole == RPL_NAMREPLY)
        return (std::string("Mehdi mets ta methode ici pour RPL_TOPIC\n")); //------------------------------------------------------------------------------------
    if (protocole == RPL_TOPIC)
        return (std::string("332 RPL_TOPIC\n\"we hate IRC\"\n"));
    if (protocole == ERR_PASSWDMISMATCH)
        return (std::string("464 ERR_PASSWDMISSMATCH\n\":Password incorrect\""));
    if (protocole == ERR_TOOMANYCHANNELS && channel)
        return (std::string("405 ERR_TOOMANYCHANNELS\n\"<" + channel->getHostName() + "> :You have joined too many channels\"\n"));
    
    return (std::string("Couldn't find  protocole !\n"));
}

void   protocole(int protocole, Channel *channel, User *user){
    std::string protocoleMessage(utils::get_protocole_message(protocole, channel, user));
} 