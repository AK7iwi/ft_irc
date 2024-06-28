/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 01:54:19 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/28 11:16:42 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPL_HPP
#define RPL_HPP

#include "Client.hpp"
#include <string>
#include <stdint.h>
#include <vector>

class Server;
class Client;

/* 001 */
std::string	RPL_WELCOME(Client const *client, std::string const &networkname, std::string const &servername);
/* 002 */
std::string	RPL_YOURHOST(Client const *client, std::string const &servername, std::string const &version);
/* 003 */
std::string	RPL_CREATED(Client const *client, std::string const &start_time, std::string const &servername);
/* 004 */
std::string	RPL_MYINFO(Client const *client, std::string const &servername, std::string const &version);
/* 431 */
std::string	ERR_NONICKNAMEGIVEN(Client const *client);
/* 432 */
std::string	ERR_ERRONEUSNICKNAME(Client const *client, std::string const &nick);
/* 433 */
std::string	ERR_NICKNAMEINUSE(Client const *client, std::string const &nick);
/* 461 */
std::string	ERR_NEEDMOREPARAMS(Client const *client, std::string const &command);
/* 462 */
std::string	ERR_ALREADYREGISTERED(Client const *client);
/* 464 */
std::string	ERR_PASSWDMISMATCH(Client const *client);

/* Personal RPL */

/* 1111 */
std::string	NEW_NICK(std::vector<std::string> const &reply_arg);

#endif /* RPL_HPP */