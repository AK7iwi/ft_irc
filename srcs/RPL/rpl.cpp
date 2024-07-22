/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:59:26 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/22 18:47:16 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rpl.hpp"

/* 001 */
std::string	RPL_WELCOME(Client const *client, std::string const &networkname, std::string const &servername) 
{return (":" + servername + " 001 " + client->get_nickname() + " :Welcome to the " + networkname + " Network, " + client->get_nickname() + "[!" + client->get_username() + "@" + client->get_hostname() + "]");}

/* 002 */
std::string	RPL_YOURHOST(Client const *client, std::string const &servername, std::string const &version) 
{return (":" + servername + " 002 " + client->get_nickname() + " :Your host is "+ servername + ", running version " + version);}

/* 003 */
std::string	RPL_CREATED(Client const *client, std::string const &start_time, std::string const &servername) 
{return (":" + servername + " 003 " + client->get_nickname() + " :This server was created " + start_time);}

/* 004 */
std::string	RPL_MYINFO(Client const *client, std::string const &servername, std::string const &version) 
{return (":" + servername + " 004 " + client->get_nickname() + " " + servername + " " + version + "\n[ -k -i -o -t -l ] [ -k -o -l ]");}

/* 332 */
std::string RPL_TOPIC(Client const *client, std::string const &channel_name, std::string const &topic)
{return (":" + client->get_hostname() + " 332 " + client->get_nickname() + " " + channel_name + " :" + topic);}

/* 341 */
std::string RPL_INVITING(Client const *client, std::string const &client_to_invite, std::string const &channel_name)
{return (client->get_prefix() + " 341 " + client->get_nickname() + " " + client_to_invite + " " + channel_name);}

/* 401 */
std::string	ERR_NOSUCHNICK(Client const *client, std::string const &nickname)
{return (client->get_prefix() + " 401 " + nickname + " :No such nick/channel");}

/* 403 */
std::string	ERR_NOSUCHCHANNEL(Client const *client, std::string const &channel_name)
{return (client->get_prefix() + " 403 " + channel_name + " :No such channel");}

/* 404 */
std::string	ERR_CANNOTSENDTOCHAN(Client const *client, std::string const &channel_name)
{return (client->get_prefix() + " 404 " + channel_name + " :Cannot send to channel");}

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
std::string	ERR_ERRONEUSNICKNAME(Client const *client, std::string const &nick)
{return (client->get_prefix() + " 432 " + nick + " :Erroneus nickname");}

/* 433 */
std::string	ERR_NICKNAMEINUSE(Client const *client, std::string const &nick)
{return (client->get_prefix() + " 433 " + nick + " :Nickname is already in use");}

/* 441 */
std::string	ERR_USERNOTINCHANNEL(Client const *client, std::string const &client_to_kick, std::string const &channel_name)
{return (client->get_prefix() + " 441 " + client_to_kick + " " + channel_name + " :They aren't on that channel");}

/* 442 */
std::string	ERR_NOTONCHANNEL(Client const *client, std::string const &channel_name)
{return (client->get_prefix() + " 442 " + channel_name + " :You're not on that channel");}

/* 443 */
std::string	ERR_USERONCHANNEL(Client const *client, std::string const &client_to_kick, std::string const &channel_name)
{return (client->get_prefix() + " 443 " + client_to_kick + " " + channel_name + " :is already on channel");}

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
std::string	ERR_CHANNELISFULL(Client const *client, std::string const &channel_name)
{return (":" + client->get_hostname() + " 471 " + client->get_nickname() + " " + channel_name + " :Cannot join channel (+l)");}

/* 475 */
std::string	ERR_BADCHANNELKEY(Client const *client, std::string const &channel_name)
{return (":" + client->get_hostname() + " 475 " + client->get_nickname() + " " + channel_name + " :Cannot join channel (+k)");}

/* 476 */
std::string	ERR_BADCHANMASK(std::string const &channel_name)
{return ("476 " + channel_name + " :Bad Channel Mask");}

/* 1111 */
std::string	NEW_NICK(std::string const &client_prefix, std::string const &new_nick)
{return (client_prefix + " NICK " + new_nick);}

/* 2222 */
std::string	NEW_MEMBER(std::string const &client_prefix, std::string const &channel_name)
{return (client_prefix + " JOIN " + channel_name + " :" + channel_name);}

/* 3333 */
std::string NEW_PING(std::string const &client_prefix)
{return ("PONG " + client_prefix);} 

/* 4444 */
std::string GOODBYE(std::string const &client_prefix, std::string const &channel_name, std::string const &reason)
{return(client_prefix + " PART " + channel_name + " :" + reason);}

/* 5555 */
std::string GET_OUT_OF_HERE(std::string const &client_prefix, std::string const &channel_name, std::string const &client_to_kick, std::string const &comment)
{return (client_prefix + " KICK " + channel_name + " " + client_to_kick + " :" + comment);}

/* 6666 */
std::string MSGS(std::string const &client_prefix, std::string const &name, std::string const &message)
{return (client_prefix + " PRIVMSG " + name + " :" + message);}

std::string Server::wich_rpl(Client *client, uint16_t rpl, std::vector<std::string> const &reply_arg)
{
	std::string reply;
	
	switch (rpl)
	{
        case   1: reply = RPL_WELCOME(client, _networkname, _servername);							break;
        case   2: reply = RPL_YOURHOST(client, _servername, _version);								break;
        case   3: reply = RPL_CREATED(client, _start_time, _servername);							break;
        case   4: reply = RPL_MYINFO(client, _servername, _version);								break;

		case 332: reply = RPL_TOPIC(client, reply_arg[2], reply_arg[3]);							break;
		case 341: reply = RPL_INVITING(client, reply_arg[3], reply_arg[2]);							break;
		
		case 401: reply = ERR_NOSUCHNICK(client, reply_arg[2]);										break;
		case 403: reply = ERR_NOSUCHCHANNEL(client, reply_arg[2]);									break;
		case 404: reply = ERR_CANNOTSENDTOCHAN(client, reply_arg[2]); 								break;
		case 411: reply = ERR_NORECIPIENT(client);													break;
		case 412: reply = ERR_NOTEXTTOSEND(client);													break;
		
		case 431: reply = ERR_NONICKNAMEGIVEN(client);												break;
        case 432: reply = ERR_ERRONEUSNICKNAME(client, reply_arg[1]);								break;
        case 433: reply = ERR_NICKNAMEINUSE(client, reply_arg[1]);									break;

		case 441: reply = ERR_USERNOTINCHANNEL(client, reply_arg[3], reply_arg[2]);					break;
		case 442: reply = ERR_NOTONCHANNEL(client, reply_arg[2]);									break;
		case 443: reply = ERR_USERONCHANNEL(client, reply_arg[3], reply_arg[2]);					break;
		
		case 451: reply = ERR_NOTREGISTERED(client);												break;
		
        case 461: reply = ERR_NEEDMOREPARAMS(client, reply_arg[0]);									break;
        case 462: reply = ERR_ALREADYREGISTERED(client);           									break;
        case 464: reply = ERR_PASSWDMISMATCH(client);												break;
		
		case 471: reply = ERR_CHANNELISFULL(client, reply_arg[2]);									break;
		case 475: reply = ERR_BADCHANNELKEY(client, reply_arg[2]);									break;
		case 476: reply = ERR_BADCHANMASK(reply_arg[2]);											break;
		
		case 1111: reply = NEW_NICK(reply_arg[0], reply_arg[1]);									break;
		case 2222: reply = NEW_MEMBER(reply_arg[1], reply_arg[2]);									break;
		case 3333: reply = NEW_PING(reply_arg[1]);													break;
		case 4444: reply = GOODBYE(reply_arg[1], reply_arg[2], reply_arg[3]);						break;
		case 5555: reply = GET_OUT_OF_HERE(reply_arg[1], reply_arg[2], reply_arg[3], reply_arg[4]); break;
		case 6666: reply = MSGS(reply_arg[1], reply_arg[2], reply_arg[3]); 							break;
    }
	
	return (reply);
}

void Server::send_reply(int client_socket, uint16_t rpl, std::vector<std::string> const  &reply_arg) 
{
	std::string message = wich_rpl(_clients[client_socket], rpl, reply_arg) + "\r\n";

    if (send(client_socket, message.c_str(), message.length(), 0) == -1)
		return ;
}