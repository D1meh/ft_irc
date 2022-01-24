#pragma once

#include "ft_irc.hpp"

namespace utils
{
    
    std::string get_protocole_message(int protocole, Channel *channel, User *user);

    void   protocole(int protocole, Channel *channel, User *user);

} // namespace utils
