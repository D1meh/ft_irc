/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trofidal <trofidal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 02:07:22 by trofidal          #+#    #+#             */
/*   Updated: 2022/01/09 05:40:18 by trofidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

#include "Data.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include <iostream>
#include <time.h>
#include <vector>
#include <cstring>
#include <exception>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <poll.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <stdio.h>

#define MAIN_SERVER 0 //index of the main server in info.getServers()[MAIN_SERVER]
#define LISTENING 256 //numbers of total fds openable and listenable
#define BUFF_SIZE 1024 //max buff size for messages

void    psend(int fd, const void *buffer, size_t buff_len, int nullified);

#define black "\e[1;30m"
#define red "\e[1;31m"
#define green "\e[1;32m"
#define yellow "\e[1;33m"
#define blue "\e[1;34m"
#define magenta "\e[1;35m"
#define cyan "\e[1;36m"
#define white "\e[1;37m"

#define bg_black "\e[40m"
#define bg_red "\e[41m"
#define bg_green "\e[42m"
#define bg_yellow "\e[43m"
#define bg_blue "\e[44m"
#define bg_magenta "\e[45m"
#define bg_cyan "\e[46m"
#define bg_white "\e[47m"

#define ncolor "\e[0m"
#endif