/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 01:54:19 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/12 17:19:43 by mfeldman         ###   ########.fr       */
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
/* 332 */
std::string RPL_TOPIC(Client const *client, std::string const &channel_name, std::string const &topic);
/* 403 */
std::string	ERR_NOSUCHCHANNEL(Client const *client, std::string const &channel_name);
/* 405 */
// std::string ERR_TOOMANYCHANNELS(Client const *client, std::string const &channel_name);
/* 431 */
std::string	ERR_NONICKNAMEGIVEN(Client const *client);
/* 432 */
std::string	ERR_ERRONEUSNICKNAME(Client const *client, std::string const &nick);
/* 433 */
std::string	ERR_NICKNAMEINUSE(Client const *client, std::string const &nick);
/* 442 */
std::string	ERR_NOTONCHANNEL(Client const *client,  std::string const &channel_name);
/* 451 */
std::string	ERR_NOTREGISTERED(Client const *client);
/* 461 */
std::string	ERR_NEEDMOREPARAMS(Client const *client, std::string const &command);
/* 462 */
std::string	ERR_ALREADYREGISTERED(Client const *client);
/* 464 */
std::string	ERR_PASSWDMISMATCH(Client const *client);
/* 471 */
std::string	ERR_CHANNELISFULL(Client const *client, std::string const &channel_name);
/* 475 */
std::string	ERR_BADCHANNELKEY(Client const *client, std::string const &channel_name);
/* 476 */
std::string	ERR_BADCHANMASK(std::string const &channel_name);

/* 1111 */
std::string	NEW_NICK(std::string const &client_prefix, std::string const &new_nick);
/* 2222 */
std::string	NEW_MEMBER(std::string const &client_prefix, std::string const &channel_name);
/* 3333 */
std::string NEW_PING(std::string const &client_prefix);
/* 4444 */
std::string GOODBYE(std::string const &client_prefix, std::string const &channel_name, std::string const &message);

#endif /* RPL_HPP */