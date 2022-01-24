#include "Command.hpp"
#include "ft_irc.hpp"
#include "Utils.hpp"

extern Data *g_ptr;
//client facultatif suivant la command demandée
Command::Command(){

}

Command::~Command(){

}

	// ************************************ //
	//										//
	//	   			   UTILS				//
	//										//
	// ************************************ //

int get_command_arg(char *str);

void    psend(int fd, const void *buffer, size_t buff_len, int nullified = 0){
    std::cout << blue << static_cast<const char *>(buffer) << ncolor;
    send(fd, buffer, buff_len, nullified);
}

std::vector<std::string> parse_cmd(std::string s, char c){
    std::vector<std::string> vect;
    size_t i = 0, len = 0, old_i = 0;
    while (!s.empty() && s.at(s.size() - 1) == c)
        s.erase(s.end() - 1);
    while (s[i] && s[i] == c)
        i++;
    while (s[i]){
        while (s[i] && s[i] == c)
            i++;
        len = 0;
        old_i = i;
        while (s[i] && s[i] != c){
            i++;
            len++;
        }
        vect.push_back(s.substr(old_i, len));
    }
    return (vect);
}

Channel *new_channel(Data const &data, std::string name, std::string password);

Channel *find_channel(char *channel_name){
    std::string chanS(channel_name);
    for (unsigned int j = 0; j < g_ptr->getChannels().size(); j++){
        if (chanS == g_ptr->getChannels()[j]->getHostName()){
            return (g_ptr->getChannels()[j]);
        }
    }
    channel_name[0] == '#' ? channel_name++ : channel_name-=0;
    Channel *chan = new_channel(*g_ptr, std::string(channel_name + 1), std::string("undefined"));
    g_ptr->getChannels().push_back(chan);
    return (chan);
}

std::string	fuck_backslash_n(std::string s) {
	std::string::iterator it = s.begin();
	while (it != s.end()) {
		//if (*it == '\n' || *it == '\r')
		if (isspace(*it))
			s.erase(it);
		if (*it == 0 || it == s.end())
			break ;
		it++;
	}
	return s;
}


void    Command::privmsg(User *user, std::string args){
    std::string format(":" + user->getNickname() + "!" + user->getUsername() + "@" + "localhost\n\r" + user->getBuffer());
    std::vector<std::string> a = parse_cmd(args, ' ');
    User *temp = 0;
    for (unsigned int i = 0; g_ptr->getUsers().size(); i++){
        for (unsigned int j = 0; j < a.size(); j++){
			if (a[j] == "bot") {
				srand(time(NULL));
				std::string insulte;
				int val = rand() % 5;
				if (val == 0)
					insulte = "Les serveurs IRC c'est naze";
				else if (val == 1)
					insulte = "IRC servers are bullshit";
				else if (val == 2)
					insulte = "tabban laka ya irc thakalatka omouka";
				else if (val == 3)
					insulte = "jebem ti picku maternu, IRC server";
				else
					insulte = "los servidores irc apestan";
				std::string format2 = ":bot!bot@localhost\n\r PRIVMSG " + user->getNickname() + " :" + insulte;
				psend(user->getSocket(), format2.c_str(), format2.size(), 0);
				return ;
			}

            if (a[j] == g_ptr->getUsers()[i]->getNickname())
                temp = g_ptr->getUsers()[i];
        }
        if (temp)
            break ;
    }
    if (temp){
        std::cout << "hello " << temp->getSocket();
        psend(temp->getSocket(), format.c_str(), format.size(), 0);
    }
}

int  Command::indexer(Channel *channel, User *user){
    std::vector<std::string> args(parse_cmd(std::string(user->getBuffer()), '\n'));
    bool found = false;
    //std::cout << "input [[[" << user->getBuffer() << "]]]" << std::endl << std::endl << std::endl << std::endl;
    for (unsigned int i = 0; i < args.size(); i++){
        if (!strncmp(args[i].c_str(), "ME ", 3)){
            Command::me(channel, user, args[i]);
            found = true;}
        else if (!strncmp(args[i].c_str(), "JOIN ", 5)){
            Command::join(channel, user, args[i]);
            found = true;}
        else if (!strncmp(args[i].c_str(), "NICK ", 5)){
            Command::nick(user, args[i]);
            found = true;}
        else if (!strncmp(args[i].c_str(), "USER ", 5)){
            Command::user(user, args[i]);
            found = true;}
        else if (!strncmp(args[i].c_str(), "PART ", 5)){
            Command::part(user);
            found = true;}
        else if (!strncmp(args[i].c_str(), "PASS ", 5)){
            Command::pass(user, args[i]);
            found = true;
        }
        else if (!strncmp(args[i].c_str(), "PING ", 5)){
            Command::ping(user);
            found = true;
        }
		else if (!strncmp(args[i].c_str(), "MODE ", 5)){
			found = true;
        }
		else if (!strncmp(args[i].c_str(), "OPER ", 5)) {
			Command::oper(user);
			found = true;
		}
		else if (!strncmp(args[i].c_str(), "WHOIS ", 6)) {
			Command::whois(user, args[i]);
			found = true;
		}
		else if (!strncmp(args[i].c_str(), "TOPIC ", 6) && user->getNickname()[0] != '@') {
			Command::topic(user, args[i]);
			found = true;
		}
		else if (!strncmp(args[i].c_str(), "KICK ", 5)) {
			Command::kick(user, args[i]);
			found = true;
		}
        else if (!strncmp(args[i].c_str(), "PRIVMSG ", 5) && !user->getChannel()){
            Command::privmsg(user, args[i]);
            found = true;
        }
        //std::cout << "User overload [" << *user << "] User overload" << std::endl;
    }
    if (user->getAccepted() == false){
        return (false);
    }
    return (found); //was a command
}

	// ************************************ //
	//										//
	//	   			   CMD					//
	//										//
	// ************************************ //

void Command::me(Channel *channel, User *user, std::string args){
    unsigned int i = 3;
    unsigned int j = 0; 
    while (args.c_str()[i] && isspace(args.c_str()[i]))
        i++;
    if (!args.c_str()[i])
        return ;
    while (j < channel->getMembers().size()){
        std::string ret(user->getNickname().c_str() + std::string("* ") + (args.c_str() + i));
         psend(channel->getMembers()[j]->getSocket(), ret.c_str(), ret.length(), 0);
        j++;
    }
}

void    Command::nick(User *user, std::string args){
    std::string a(args.c_str() + get_command_arg((char *)args.c_str()));
	a = fuck_backslash_n(a);
    if (a.size() <= 9) {
		if (user->getSocket() == 4)
			user->setNickname("@" + a);
		else
        	user->setNickname(a);
	}
    else
         psend(user->getSocket(), "No name specified or name is too long, 9 char maximum.\n", 59, 0);
}

void    Command::user(User *user, std::string args){
    std::vector<std::string> vect(parse_cmd(args, ' '));
    if (vect.size() >= 5){
        user->setUsername(vect[1]);
        user->setPassword(std::string("undefined"));
    }
    else {
        for (unsigned int i = 0; i < vect.size(); i++){
            std::cout << red << vect[i] << ncolor << std::endl;
        }
        throw (std::runtime_error("CRITICAL ERROR FROM IRSSI THROWN\n"));
    }
    std::string rpl_welcome_message(utils::get_protocole_message(RPL_WELCOME, user->getChannel(), user));
    psend(user->getSocket(), rpl_welcome_message.c_str(), rpl_welcome_message.size(), 0);
}

void    Command::quit(User *user, int log){
    std::vector<User *>::iterator it = g_ptr->getUsers().begin(), ite = g_ptr->getUsers().end();
    while (it != ite && user != *it)
        it++;
    if (*it == user){
        g_ptr->getUsers().erase(it);
        if (user->getChannel()){
			std::string msg = user->getNickname() + " left the server\n";
			for (unsigned int i = 0; i < user->getChannel()->getMembers().size(); i++) {
				if (user->getChannel()->getMembers()[i]->getSocket() != user->getSocket())
					psend(user->getChannel()->getMembers()[i]->getSocket(), msg.c_str(), msg.size(), 0);
			}

            std::vector<User *>::iterator itc = user->getChannel()->getMembers().begin(), itec = user->getChannel()->getMembers().end();
            while (itc != itec && *itc != user)
                itc++;
            if (*itc == user)
                user->getChannel()->getMembers().erase(itc);
        }
        user->setChannel(0);
		shutdown(user->getSocket(), SHUT_RDWR);
        close(user->getSocket());
		if (log)
        	std::cout << yellow << user->getNickname() << " has left" << ncolor << std::endl;
        return ;
    }
    std::cout << red << "Couldn't find user" << user->getSocket() << ncolor << std::endl;
}

void Command::join(Channel *channel, User *user, std::string args){
    std::vector<std::string> passcheck(parse_cmd(args, ' '));
    std::string wrongPassword(utils::get_protocole_message(ERR_PASSWDMISMATCH, channel, user));
    std::string noChannel(utils::get_protocole_message(ERR_NOSUCHCHANNEL, channel, user));
	passcheck[1] = fuck_backslash_n(passcheck[1]);
    if (!channel)
        channel = find_channel((char *)passcheck[1].c_str());
    if (!channel){
        psend(user->getSocket(), noChannel.c_str() , noChannel.size(), 0);
        std::cout << yellow << "No such channel found for :" << passcheck[1] << ncolor << std::endl;
        return ;
    }

	// mdp
	if (passcheck.size() > 2) {
		passcheck[2] = fuck_backslash_n(passcheck[2]);
		if (passcheck.size() == 2)
			passcheck.push_back("undefined");
		else if (passcheck[2][passcheck[2].size() - 1] == '\n')
			passcheck[2].erase(passcheck[2].end() - 1);
		if (channel->getPassword() != "undefined"){
			if (channel->getPassword() != passcheck[2]){
				psend(user->getSocket(), wrongPassword.c_str(), wrongPassword.size(), 0);
				std::cout << yellow << "user:" << user->getBuffer() << "entered a wrong passeword for channel :" << channel->getHostName() << "Pass is :"<< channel->getPassword() << "Entered :" << wrongPassword << ncolor << std::endl;
				return ;
			}
			else
				std::cout << yellow << "user:" << user->getBuffer() << "entered correct password for " << channel->getHostName() << ncolor << std::endl;
		}
	}
    if (user->getChannel())
        Command::part(user);
    user->setChannel(channel);
    channel->getMembers().push_back(user);
    //:nick!user@host JOIN :#channel
	// rpl ta mere
    std::string on_join(":" + user->getNickname() + "!"  + user->getUsername()  + "@" + "localhost" + " JOIN :" + channel->getHostName() + "\r\n");
    for (unsigned int i = 0; i < channel->getMembers().size(); i++){
        if (user->getSocket() != user->getChannel()->getMembers()[i]->getSocket())
            psend(channel->getMembers()[i]->getSocket(), on_join.c_str(), on_join.size(), 0);
    }


	std::string test(":" + g_ptr->getHost() + " 332 " + user->getNickname() + " " + channel->getHostName()
    + (channel->getTopic() != "" ? channel->getTopic() + "\r\n" : " :No Topic set\r\n") );
    psend(user->getSocket(), test.c_str(), test.size(), 0);
    std::string test2(":" + g_ptr->getHost() + " 353 " + user->getNickname() + " = " + channel->getHostName() + " :");
    std::vector<User *>::iterator it = channel->getMembers().begin(), ite = channel->getMembers().end();
    while (it != ite){
        test2 += (*it)->getNickname() + " ";
        it++;
    }
    test2 += "\r\n";
    psend(user->getSocket(), test2.c_str(), test2.size(), 0);
    std::string test3(":" + g_ptr->getHost() + " 366 " + user->getNickname() + " " + channel->getHostName() + " :End of NAMES list\r\n");
    psend(user->getSocket(), test3.c_str(), test3.size(), 0);
}

void	Command::topic(User *user, std::string args) {
	(void)user;
	(void)args;
	return ;
}

void    Command::part(User *user){
    if (!user->getChannel()){
         psend(user->getSocket(), "Not in a channel\n", 18, 0);
        return ;
    }
    std::vector<User *>::iterator it = user->getChannel()->getMembers().begin(), ite = user->getChannel()->getMembers().end();
    while (it != ite && *it != user){
        it++;
    }
    std::string on_part(":" + user->getNickname() + "!"  + user->getUsername()  + "@" + "localhost" + " PART :" + user->getChannel()->getHostName() + " :left the channel." + "\r\n");
    for (unsigned int i = 0; i < user->getChannel()->getMembers().size(); i++){
        if (user->getSocket() != user->getChannel()->getMembers()[i]->getSocket()){
            psend(user->getChannel()->getMembers()[i]->getSocket(), on_part.c_str(), on_part.size(), 0);
            std::cout << yellow << user->getChannel()->getMembers()[i]->getSocket() << user->getChannel()->getMembers()[i]->getNickname() << ncolor;
        }
    }
    if (it != ite)
        user->getChannel()->getMembers().erase(it);
    user->setChannel(0);
}
/* EN TRAVAUX
void Command::msg(User *user){
    char *name = strtok(user->getBuffer(), " ");
    name = strtok(NULL, " ");
    if (!name){
         psend(user->getSocket(), "Missing arguments\n", 19, 0);
        return ;
    }
    std::vector<User *>::iterator it = g_ptr->getUsers().begin(), ite = g_ptr->getUsers().end();
    while (it != ite && *it != name){
        it++;
    }
}
*/

void Command::notice(User *user){
    std::cout << "Dont use me i am not done yet" << user->getNickname() << std::endl;
    //Command::msg(user);
}

	// ************************************ //
	//										//
	//	   			   SYSTEM				//
	//										//
	// ************************************ //

void	Command::whois(User *user, std::string args) {
	unsigned int i = get_command_arg((char *)args.c_str());
	std::string given_nick = args.c_str()+i;
	std::vector<User *>::iterator it = g_ptr->getUsers().begin(), ite = g_ptr->getUsers().end();
    std::string first_line(":" + user->getNickname() + "!" + user->getUsername() + "@localhost" + user->getBuffer());

	given_nick = fuck_backslash_n(given_nick);
	while (it != ite && (*it)->getNickname() != given_nick)
		it++;
	if (it != ite) {
		std::string ret = ":" + g_ptr->getHost() + " 311 " + (*it)->getNickname() + " " + (*it)->getUsername() + " " + g_ptr->getHost() + " * :" + (*it)->getNickname() + "\r\n";
		std::string end = ":" + g_ptr->getHost() + " 318 " + (*it)->getNickname() + " :End of WHOIS list" + "\r\n";
		//std::string ret = "311 " + (*it)->getNickname() + " " + (*it)->getUsername() + " " + g_ptr->getHost() + " * :" + (*it)->getNickname() + "\r\n";
		//std::string end = "318 " + (*it)->getNickname() + " " + (*it)->getNickname() + " :End of WHOIS list\r\n";
		psend(user->getSocket(), ret.c_str(), ret.size(), 0);
		psend(user->getSocket(), end.c_str(), end.size(), 0);
	} else {
		std::string error = first_line + ": No such nick/channel";
		 psend(user->getSocket(), error.c_str(), error.size(), 0);
	}
}

void    Command::pass(User *user, std::string args){
	unsigned int i = get_command_arg((char *)args.c_str());
	std::string pwd = fuck_backslash_n(args.c_str()+i);
	if (!strcmp(pwd.c_str(), g_ptr->getPassword().c_str()))
		user->setAccepted(true);
	else {
		user->setAccepted(false);
		std::cout << yellow << user->getSocket() << " entered a bad password : [" << pwd << "] (expected: [" << g_ptr->getPassword() << "])" << ncolor << std::endl;
		std::string wrongPassword(utils::get_protocole_message(ERR_PASSWDMISMATCH, NULL, user));
		 psend(user->getSocket(), wrongPassword.c_str(), wrongPassword.size(), 0);
		Command::quit(user, 0);
		pthread_exit(&user->thread);
	}
}

void Command::ping(User *user){
    std::string ret;
    ret = "PONG ";
    ret += get_command_arg((char *)user->getUsername().c_str());
    ret += " ";
    ret += g_ptr->getHost();
     psend(user->getSocket(), ret.c_str(), ret.size(), 0);
}

	// ************************************ //
	//										//
	//	   			     OP					//
	//										//
	// ************************************ //

void Command::oper(User *user) {
	if (user->getPermLevel() < 1)
		return ;
	else {
		std::string error("491 ERR_NOOPERHOST\n\":No O-lines for your host\"");
		 psend(user->getSocket(), error.c_str(), error.size(), 0);
	}
}

void    Command::kick(User *user, std::string args){
    if (user->getNickname()[0] != '@'){
         psend(user->getSocket(), "You don't have the permission to do this.\n", 43, 0);
        return ;
    }
    //char * name = strtok((char *)args.c_str(), " ");
    //name = strtok(NULL, " ");

    // if (!name){
    //      psend(user->getSocket(), "Missing aguments\n", 19, 0);
    //     return ;
    // }
	std::vector<std::string> v = parse_cmd(args, ' ');
	if (v.size() < 2)
		return ;
	
	std::string name = v[2];
    std::vector<User *>::iterator it = user->getChannel()->getMembers().begin(), ite = user->getChannel()->getMembers().end();
    //while (it != ite && *it != name) PROBLEM WITH THIS STATEMENT AT '!= name'
    while (it != ite && (*it)->getNickname() != name){
		std::cout << (*it)->getNickname() << " " << name << std::endl;
        it++;
    }
	if (it == ite)
		return ;
    User *kicked_user = *it;
    if (!kicked_user){
        std::cout << yellow << "//DEBUG\\\\ERROR OCCURED AT 140 (Command.cpp)" << ncolor << std::endl;
        exit(1);
    }
    //if (it == ite){
        psend(kicked_user->getSocket(), "You have been kicked from this channel.\n", 38, 0);
        //kicked_user->getChannel()->getMembers().erase(it);
        //kicked_user->setChannel(0);
		Command::part(kicked_user);
    //}

}
