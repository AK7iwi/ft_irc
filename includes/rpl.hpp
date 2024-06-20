/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 01:54:19 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/20 03:49:05 by mfeldman         ###   ########.fr       */
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

// std::string RPL_WELCOME(Client const *client, std::string const &networkname, std::string const &servername);
// std::string RPL_YOURHOST(Client const *client, std::string const &servername, std::string const &version);
// std::string RPL_CREATED(Client const *client, std::string const &start_time, std::string const &servername);
// std::string RPL_MYINFO(Client const *client, std::string const &servername, std::string  const &version);
// std::string RPL_UMODEIS(Client const *client, std::vector<std::string> const &reply_arg);
// std::string RPL_CHANNELMODEIS(std::vector<std::string> const &reply_arg);
// std::string RPL_TOPIC(Client const *client, std::vector<std::string> const &reply_arg);
// std::string RPL_INVITING(Client const *client, std::vector<std::string> const &reply_arg);
// std::string ERR_NOSUCHNICK(Client const *client, std::vector<std::string> const &reply_arg);
// std::string ERR_clientNOTINCHANNEL(Client const *client, std::vector<std::string> const &reply_arg);
// std::string ERR_NOTONCHANNEL(Client const *client, std::vector<std::string> const &reply_arg);
// std::string ERR_clientONCHANNEL(Client const *client, std::vector<std::string> const &reply_arg);
// std::string RPL_ENDOFNAMES(Client const *client, std::vector<std::string> const &reply_arg);
// std::string ERR_NOTREGISTERED(Client const *client);
// std::string ERR_NEEDMOREPARAMS(Client const *client, std::vector<std::string> const &reply_arg);
// std::string ERR_ALREADYREGISTERED(Client const *client);
// std::string ERR_PASSWDMISMATCH(Client const *client);
// std::string ERR_NOTEXTTOSEND(Client const *client);
// std::string ERR_NOSUCHCHANNEL(Client const *client, std::vector<std::string> const &reply_arg);
// std::string ERR_CANNOTSENDTOCHAN(Client const *client, std::vector<std::string> const &reply_arg);
// std::string ERR_NORECIPIENT(Client const *client, std::vector<std::string> const &reply_arg);
// std::string ERR_NONICKNAMEGIVEN(Client const *client);
// std::string ERR_ERRONEUSNICKNAME(Client const *client, std::vector<std::string> const &reply_arg);
// std::string ERR_NICKNAMEINUSE(Client const *client, std::vector<std::string> const &reply_arg);
// std::string ERR_CHANNELISFULL(Client const *client, std::vector<std::string> const &reply_arg);
// std::string ERR_INVITEONLYCHAN(Client const *client, std::vector<std::string> const &reply_arg);
// std::string ERR_BADCHANNELKEY(Client const *client, std::vector<std::string> const &reply_arg);
// std::string ERR_BADCHANMASK(std::vector<std::string> const &reply_arg);
// std::string ERR_CHANOPRIVSNEEDED(Client const *client, std::vector<std::string> const &reply_arg);
// std::string ERR_UMODEUNKNOWNFLAG(Client const *client);
// std::string ERR_clientSDONTMATCH(Client const *client);
// std::string ERR_INVALIDMODEPARAM(Client const *client, std::vector<std::string> const &reply_arg);
// std::string PER_NICKNAMECHANGE(std::vector<std::string> const &reply_arg);
// std::string PER_SENDMESSAGETOCHANNEL(std::vector<std::string> const &reply_arg);

#endif /* RPL_HPP */