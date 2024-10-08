/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:59:26 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/03 14:34:10 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"

/* 001 */
std::string	RPL_WELCOME(Client const *client, std::string const &server_name, std::string const &network_name) 
{return (":" + server_name + " 001 " + client->get_nickname() + " :Welcome to the " + network_name + " Network " + client->get_prefix());}

/* 002 */
std::string	RPL_YOURHOST(Client const *client, std::string const &server_name, std::string const &version) 
{return (":" + server_name + " 002 " + client->get_nickname() + " :Your host is " + server_name + ", running version " + version);}

/* 003 */
std::string	RPL_CREATED(Client const *client, std::string const &server_name, std::string const &start_time) 
{return (":" + server_name + " 003 " + client->get_nickname() + " :This server was created " + start_time);}

/* 004 */
std::string	RPL_MYINFO(Client const *client, std::string const &server_name, std::string const &version) 
{return (":" + server_name + " 004 " + client->get_nickname() + " " + server_name + " " + version + "\n[ -k -i -o -t -l ] [ -k -o -l ]");}

/* 324 */
std::string RPL_CHANNELMODEIS(Client const *client, std::string const &channel_name, std::string const &modes)
{return (":" + client->get_prefix() + " 324 " + client->get_nickname() + " " + channel_name + " " + modes);}

/* 332 */
std::string RPL_TOPIC(Client const *client, std::string const &channel_name, std::string const &topic)
{return (":" + client->get_prefix() + " 332 " + client->get_nickname() + " " + channel_name + " :" + topic);}

/* 341 */
std::string RPL_INVITING(Client const *client, std::string const &client_to_invite, std::string const &channel_name)
{return (client->get_prefix() + " 341 " + client->get_nickname() + " " + client_to_invite + " :" + channel_name);}

/* 401 */
std::string ERR_NOSUCHNICK(Client const *client, std::string const &nickname)
{return ("401 " + client->get_nickname() + " " + nickname + " :No such nick/channel");}

/* 403 */
std::string ERR_NOSUCHCHANNEL(Client const *client, std::string const &channel_name)
{return ("403 " + client->get_nickname() + " " + channel_name + " :No such channel");}

/* 411 */
std::string	ERR_NORECIPIENT(Client const *client)
{return (client->get_prefix() + " 411 :No recipient given (PRIVMSG)");}

/* 412 */
std::string	ERR_NOTEXTTOSEND(Client const *client)
{return (client->get_prefix() + " 412 :No text to send");}

/* 431 */
std::string	ERR_NONICKNAMEGIVEN(Client const *client) 
{return (client->get_prefix() + " 431 :No nickname given");}

/* 432 */
std::string	ERR_ERRONEUSNICKNAME(Client const *client, std::string const &nickname)
{return (client->get_prefix() + " 432 " + nickname + " :Erroneus nickname");}

/* 433 */
std::string	ERR_NICKNAMEINUSE(Client const *client, std::string const &nickname)
{return (client->get_prefix() + " 433 " + nickname + " :Nickname is already in use");}

/* 441 */
std::string	ERR_USERNOTINCHANNEL(Client const *client, std::string const &client_to_kick, std::string const &channel_name)
{return (client->get_prefix() + " 441 " + client_to_kick + " " + channel_name + " :They aren't on that channel");}

/* 442 */
std::string ERR_NOTONCHANNEL(Client const *client, std::string const &channel_name)
{ return ("442 " + client->get_nickname() + " " + channel_name + " :You're not on that channel");}

/* 443 */
std::string ERR_USERONCHANNEL(Client const *client, std::string const &nickname, std::string const &channel_name)
{return (client->get_prefix() + " 443 " + client->get_nickname() + " " + nickname + " " + channel_name + " :is already on channel");}

/* 451 */
std::string	ERR_NOTREGISTERED(Client const *client)
{return (client->get_prefix() + " 451 :You have not registered");}

/* 461 */
std::string	ERR_NEEDMOREPARAMS(Client const *client, std::string const &command)
{return (client->get_prefix() + " 461 " + command + " :Not enough parameters");}

/* 462 */
std::string	ERR_ALREADYREGISTERED(Client const *client)
{return (client->get_prefix() + " 462 :You may not reregister");}

/* 464 */
std::string	ERR_PASSWDMISMATCH(Client const *client)
{return (client->get_prefix() + " 464 :Password incorrect");}

/* 471 */
std::string ERR_CHANNELISFULL(Client const *client, std::string const &channel_name)
{return ("471 " + client->get_nickname() + " " + channel_name + " :Cannot join channel (+l)");}

/* 473 */
std::string ERR_INVITEONLYCHAN(Client const *client, std::string const &channel_name)
{return ("473 " + client->get_nickname() + " " + channel_name + " :Cannot join channel (+i)");}

/* 475 */
std::string ERR_BADCHANNELKEY(Client const *client, std::string const &channel_name)
{return ("475 " + client->get_nickname() + " " + channel_name + " :Cannot join channel (+k)");}

/* 476 */
std::string ERR_BADCHANMASK(Client const *client, std::string const &channel_name)
{return (client->get_prefix() + " 476 " + channel_name + " :Bad Channel Mask");}

/* 482 */
std::string ERR_CHANOPRIVSNEEDED(Client const *client, std::string const &channel_name)
{return (client->get_prefix() + " 482 " + channel_name + " :You're not channel operator");}

/* 501 */
std::string ERR_UMODEUNKNOWNFLAG(Client const *client)
{return (client->get_prefix() + " 501 " + client->get_nickname() + " :Unknown MODE flag");}

/* 696 */
std::string ERR_INVALIDMODEPARAM(Client const *client, std::string const &channel_name, std::string const &mode, std::string const &parameter, std::string const &error_msg)
{return (client->get_prefix() + " 696 " + channel_name + " " + mode + " " + parameter + " :Invalid mode parameter. " + error_msg);}

/* 1111 */
std::string	NEW_NICK(std::string const &client_prefix, std::string const &new_nickname)
{return (client_prefix + " NICK " + new_nickname);}

/* 2222 */
std::string	NEW_MEMBER(std::string const &client_prefix, std::string const &channel_name)
{return (client_prefix + " JOIN " + channel_name + " :" + channel_name);}

/* 3333 */
std::string RPL_PONG(std::string const &server_name, std::string const &ping_token)
{return ("PONG " + server_name + " :" + ping_token);}

/* 4444 */
std::string GOODBYE(std::string const &client_prefix, std::string const &channel_name, std::string const &reason)
{return(client_prefix + " PART " + channel_name + " :" + reason);}

/* 5555 */
std::string GET_OUT_OF_HERE(std::string const &client_prefix, std::string const &channel_name, std::string const &client_to_kick, std::string const &comment)
{return (client_prefix + " KICK " + channel_name + " " + client_to_kick + " :" + comment);}

/* 6666 */
std::string MSGS(std::string const &client_prefix, std::string const &name, std::string const &message)
{return (client_prefix + " PRIVMSG " + name + " :" + message);}
