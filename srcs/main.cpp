/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trofidal <trofidal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 02:07:24 by trofidal          #+#    #+#             */
/*   Updated: 2022/01/04 09:06:59idal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"
#include "Command.hpp"
#include "Utils.hpp"

/*              facultatif                      obligatoire ''
./ircserv [host:port_network:password_network] <port> <password>
*/
Data *g_ptr;

int get_command_arg(char *str){
    unsigned int i = 0;
    if (strlen(str) <= 0)
        return (0);
    if (str[0] == '/')
        i++;
    while (str[i] >= 'A' && str[i] <= 'Z')
        i++;
    while (isspace(str[i]))
        i++;
    return (i);
}

bool    isPortValid(std::string lhs){
    unsigned int i = 0;
    while (i < lhs.size()){
        if (!isdigit(lhs.c_str()[i]))
            return (false);
        i++;
    }
    return (true);
}

void    parseString(std::vector<std::string> &lhs, char **av, int ac){
    if (ac == 4){
        char *ptr = strtok(av[1], ":");
        int i = 0;
        while (ptr){
            if (i == 2 && !isPortValid(lhs[i - 1])){
                throw(std::runtime_error("Exception: Invalid port.\nUsage :./ircserv [host:port_network:password_network] <port> <password>"));
            }
            if (i > 3){
                throw(std::runtime_error("Exception: Too many arguments separated by ':' or not enough given.\nUsage :./ircserv [host:port_network:password_network] <port> <password>"));
            }
            lhs[i] = std::string(ptr);
            ptr = strtok(NULL, ":");
            i++;
        }
        lhs[3] = av[2];
        lhs[4] = av[3];
        if (!isPortValid(lhs[3])){
            throw(std::runtime_error("Exception: Invalid port.\nUsage :./ircserv [host:port_network:password_network] <port> <password>"));
        }
    }
    else{
        //string host, int portNetwork, string passwordNetwork, int port, string password
        if (!isPortValid(std::string(av[1]))){
            throw(std::runtime_error("Exception: Invalid port.\nUsage :./ircserv [host:port_network:password_network] <port> <password>"));
        }
        if (strlen(av[2]) <= 0){
            throw(std::runtime_error("Exception: Invalid password.\nUsage :./ircserv [host:port_network:password_network] <port> <password>"));
        }
        lhs[0] = "ft_irc.42.fr";
        lhs[1] = "6665";
        lhs[2] = "undefined";
        lhs[3] = av[1];
        lhs[4] = av[2];
    }
}

int error_handler(const char *__error){
    fprintf(stderr, "%s", __error);
    exit(EXIT_FAILURE);
    return (1);
}

void    send_message(User *user){
    if (!user->getChannel()){
        std::cout << yellow << "No channel assigned" << ncolor << std::endl;
        return ;
    }
    unsigned int total = user->getChannel()->getMembers().size();
    Channel *channel = user->getChannel();
    std::string message("error occured\n");
    for (unsigned int i = 0; i < total; i++){
        if (channel->getMembers()[i]->getSocket() != user->getSocket()){
            message = ":" + (user->getNickname()[0] == '@' ? std::string(user->getNickname().c_str()+1) : user->getNickname()) + " " + user->getBuffer();
            if (message.length() < BUFF_SIZE)
                 psend(channel->getMembers()[i]->getSocket(), message.c_str(), strlen(message.c_str()), 0);
            else
                 psend(user->getSocket(), "Message too long ! Maximum allowed is 1000 characters.\n", 56, 0);
        }
    }
}

Channel *new_channel(Data const &data, std::string name, std::string password){
    Channel *ret = new Channel;

    ret->setSocket(data.getSocket());
    ret->setHostName(std::string("#") + name);
    if (password.length() <= 0)
        ret->setPassword("undefined");
    else
        ret->setPassword(password);
    return (ret);
}

void    *user_thread(void *arg){
    User *user = static_cast<User *>(arg);

    //std::string rpl_welcome_message(get_protocole_message(RPL_WELCOME, 0, info.getUsers()[info.getUsers().size()-1]));
    if (Server::isSocketReady(user->getSocket())){
        recv(user->getSocket(), user->getBuffer(), BUFF_SIZE, 0);
        if (strlen(user->getBuffer()) > 0)
            std::cout << blue << user->getBuffer() << ncolor;
    }
    while (strlen(user->getBuffer()) > 0){
        Command::indexer(user->getChannel(), user);
        bzero(user->getBuffer(), BUFF_SIZE);
    }
    usleep(100);
    while (1){
        bzero(user->getBuffer(), BUFF_SIZE);
        if (Server::isSocketReady(user->getSocket())){

            if ((recv(user->getSocket(), user->getBuffer(), BUFF_SIZE, 0) == 0) || !strncmp(user->getBuffer(), "QUIT :leaving", 14)){
                Command::quit(user, 1);
                //std::cout << "User " << user->getSocket() << user->getUsername() << "has left." << std::endl;
                pthread_exit(&user->thread);
            }
            if (strlen(user->getBuffer()) > 0)
                std::cout << blue << user->getBuffer() << ncolor;
			user->tmp_buffer += user->getBuffer();
			if (!strchr(user->getBuffer(), '\n') && !strchr(user->getBuffer(), '\r'))	
				continue ;
			strcpy(user->getBuffer(), user->tmp_buffer.c_str());
			user->tmp_buffer.clear();
            if (Command::indexer(user->getChannel(), user) == false){
                if (user->getChannel()){
                    if (strlen(user->getBuffer()) > 0){
                        if (user->getAccepted() == false)
                            Command::quit(user, 1);
                        send_message(user);
                	}
                }
            }
        }
    }
    exit(0);
}

int main(int ac, char *av[]){
    int ret = 0;
    if (ac != 4 && ac != 3){ // && != 3
        std::cerr << "main(64): Error, invalid numbers of arguments" << std::endl;
        return (1);
    }
    std::vector<std::string> args(5);
    
    try {
        parseString(args, av, ac);
    } catch (std::exception &e){
        std::cerr << e.what() << std::endl;
        return (1);
    }
    /* initializing main server */
    //string host, int portNetwork, string passwordNetwork, int port, string password
    Data info(args[0], atoi(args[1].c_str()), args[2], atoi(args[3].c_str()), args[4]);
    std::cout << green << info << ncolor << std::endl;
    g_ptr = &info;
    info.setServer(new Server);
    Server *server = info.getServer();
    server->getSockAddr()->sin_addr.s_addr = htonl(INADDR_ANY);
    server->getSockAddr()->sin_family = PF_INET;
    server->getSockAddr()->sin_port = htons(info.getPort());
    server->setSocket(socket(PF_INET, SOCK_STREAM, 0));
    ret = bind(server->getSocket(), (struct sockaddr *)server->getSockAddr(), sizeof(*server->getSockAddr()));
    if (server->getSocket() < 0 || ret < 0){
        std::cerr << "main(86): Error occured in socket creation" << std::endl;
        return (1);
    }
    /* listening user input in main server */
    listen(server->getSocket(), LISTENING);
    int newfd, j = 0;
    info.getChannels().push_back(new_channel(info, "toto", "undefined"));
    info.getChannels().push_back(new_channel(info, "totopass", "1234"));
    while (1){
        unsigned int size = sizeof(*server->getSockAddr());
        if (Server::isSocketReady(server->getSocket())){
            newfd = accept(server->getSocket(), (struct sockaddr*)server->getSockAddr(), &size);
            info.getUsers().push_back(new User(newfd));
            info.getUsers()[info.getUsers().size()-1]->setAccepted(true);
            std::cout << info.getUsers()[info.getUsers().size()-1]->getSocket() << std::endl;
            std::cout << yellow << "A user joined with fd " << newfd << ncolor << std::endl;
            pthread_create(&info.getUsers()[info.getUsers().size()-1]->thread, NULL, user_thread, info.getUsers()[info.getUsers().size()-1]);
            j++;
        }
    }
}