#pragma once
#include "ft_irc.hpp"
#include "Channel.hpp"
#include "User.hpp"


class Command{
    public:
        Command();
        ~Command();

        static int  indexer(Channel *channel, User *user = 0); //client facultatif suivant la command demandée
        static void me(Channel *channel, User *user, std::string args);
        static void nick(User *user, std::string args);
        static void user(User *user, std::string args);
        static void join(Channel *channel, User *user, std::string args);
        static void part(User *user);
        static void quit(User *user, int log);
        static void msg(User *user, std::string args);
        static void privmsg(User *user, std::string args);

		// not working
        static void notice(User *user);

		// system
		static void whois(User *user, std::string args);
		static void pass(User *user, std::string args);
        static void ping(User *user);

		// op
		static void oper(User *user);
        static void kick(User *user, std::string args);
		static void topic(User *user, std::string args);

    private:
        /*nothing needed here*/
};
