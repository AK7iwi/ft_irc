/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 01:54:19 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/03 14:36:48 by mfeldman         ###   ########.fr       */
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
std::string	RPL_WELCOME(Client const *client, std::string const &server_name, std::string const &networ_kname);
/* 002 */
std::string	RPL_YOURHOST(Client const *client, std::string const &server_name, std::string const &version);
/* 003 */
std::string	RPL_CREATED(Client const *client, std::string const &server_name, std::string const &start_time);
/* 004 */
std::string	RPL_MYINFO(Client const *client, std::string const &server_name, std::string const &version);
/* 221 */
std::string RPL_UMODEIS(Client const *client);
/* 324 */
std::string RPL_CHANNELMODEIS(Client const *client, std::string const &channel_name, std::string const &modes);
/* 332 */
std::string RPL_TOPIC(Client const *client, std::string const &channel_name, std::string const &topic);
/* 341 */
std::string RPL_INVITING(Client const *client, std::string const &client_to_invite, std::string const &channel_name);
/* 401 */
std::string	ERR_NOSUCHNICK(Client const *client, std::string const &nickname);
/* 403 */
std::string	ERR_NOSUCHCHANNEL(Client const *client, std::string const &channel_name);
/* 411 */
std::string	ERR_NORECIPIENT(Client const *client); 
/* 412 */
std::string	ERR_NOTEXTTOSEND(Client const *client);
/* 431 */
std::string	ERR_NONICKNAMEGIVEN(Client const *client);
/* 432 */
std::string	ERR_ERRONEUSNICKNAME(Client const *client, std::string const &nickname);
/* 433 */
std::string	ERR_NICKNAMEINUSE(Client const *client, std::string const &nickname);
/* 441 */
std::string	ERR_USERNOTINCHANNEL(Client const *client, std::string const &client_to_kick, std::string const &channel_name);
/* 442 */
std::string	ERR_NOTONCHANNEL(Client const *client,  std::string const &channel_name);
/* 443 */
std::string ERR_USERONCHANNEL(Client const *client, std::string const &nickname, std::string const &channel_name);
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
/* 473 */
std::string ERR_INVITEONLYCHAN(Client const *client, std::string const &channel_name);
/* 475 */
std::string	ERR_BADCHANNELKEY(Client const *client, std::string const &channel_name);
/* 476 */
std::string ERR_BADCHANMASK(Client const *client, std::string const &channel_name);
/* 482 */
std::string ERR_CHANOPRIVSNEEDED(Client const *client, std::string const &channel_name);
/* 501 */
std::string ERR_UMODEUNKNOWNFLAG(Client const *client);
/* 502 */
std::string	ERR_USERSDONTMATCH(Client const *client);
/* 696 */
std::string ERR_INVALIDMODEPARAM(Client const *client, std::string const &channel_name, std::string const &mode, std::string const &parameter, std::string const &error_msg);
/* 1111 */
std::string	NEW_NICK(std::string const &client_prefix, std::string const &new_nickname);
/* 2222 */
std::string	NEW_MEMBER(std::string const &client_prefix, std::string const &channel_name);
/* 3333 */
std::string RPL_PONG(std::string const &server_name, std::string const &ping_token);
/* 4444 */
std::string GOODBYE(std::string const &client_prefix, std::string const &channel_name, std::string const &reason);
/* 5555 */
std::string GET_OUT_OF_HERE(std::string const &client_prefix, std::string const &channel_name, std::string const &client_to_kick, std::string const &comment);
/* 6666 */
std::string MSGS(std::string const &client_prefix, std::string const &name, std::string const &message);

#endif /* RPL_HPP */