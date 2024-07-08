/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:59:26 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/08 15:33:57 by mfeldman         ###   ########.fr       */
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

/* 333 */

/* 403 */
std::string	ERR_NOSUCHCHANNEL(Client const *client, std::string const &channel_name)
{return (client->get_prefix() + " 403 " + channel_name + " :No such channel");}

/* 405 */
std::string ERR_TOOMANYCHANNELS(Client const *client, std::string const &channel_name)
{return (client->get_prefix() + " 405 " + channel_name + " :You have joined too many channels");}

/* 431 */
std::string	ERR_NONICKNAMEGIVEN(Client const *client) 
{return (client->get_prefix() + " 431 :No nickname given");}

/* 432 */
std::string	ERR_ERRONEUSNICKNAME(Client const *client, std::string const &nick)
{return (client->get_prefix() + " 432 " + nick + " :Erroneus nickname");}

/* 433 */
std::string	ERR_NICKNAMEINUSE(Client const *client, std::string const &nick)
{return (client->get_prefix() + " 433 " + nick + " :Nickname is already in use");}

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

/* Personal RPL */

/* 1111 */
std::string	NEW_NICK(std::vector<std::string> const &reply_arg)
{return (reply_arg[0] + " NICK " +  reply_arg[1]);}

std::string Server::wich_rpl(int client_socket, uint16_t rpl, std::vector<std::string> const &reply_arg)
{
	std::string reply;
	
	switch (rpl)
	{
        case   1: reply = RPL_WELCOME(_clients[client_socket], _networkname, _servername);    break;
        case   2: reply = RPL_YOURHOST(_clients[client_socket], _servername, _version);       break;
        case   3: reply = RPL_CREATED(_clients[client_socket], _start_time, _servername);     break;
        case   4: reply = RPL_MYINFO(_clients[client_socket], _servername, _version);         break;

		case 332: reply = RPL_TOPIC(_clients[client_socket], reply_arg[1], reply_arg[2]);	break;
		
		// case 333: reply = RPL_TOPICWHOTIME(_clients[client_socket], reply_arg[1], )
		
		case 403: reply = ERR_NOSUCHCHANNEL(_clients[client_socket], reply_arg[1]);			break;
		case 405: reply = ERR_TOOMANYCHANNELS(_clients[client_socket], reply_arg[1]);				break;

		case 431: reply = ERR_NONICKNAMEGIVEN(_clients[client_socket]);						break;
        case 432: reply = ERR_ERRONEUSNICKNAME(_clients[client_socket], reply_arg[1]);		break;
        case 433: reply = ERR_NICKNAMEINUSE(_clients[client_socket], reply_arg[1]);			break;
		
		case 451: reply = ERR_NOTREGISTERED(_clients[client_socket]);						break;
		
        case 461: reply = ERR_NEEDMOREPARAMS(_clients[client_socket], reply_arg[0]);		break;
        case 462: reply = ERR_ALREADYREGISTERED(_clients[client_socket]);           		break;
        case 464: reply = ERR_PASSWDMISMATCH(_clients[client_socket]);						break;
		
		case 471: reply = ERR_CHANNELISFULL(_clients[client_socket], reply_arg[1]);			break;
		case 475: reply = ERR_BADCHANNELKEY(_clients[client_socket], reply_arg[1]);			break;
		case 476: reply = ERR_BADCHANMASK(reply_arg[1]);									break;
		
		case 1111: reply = NEW_NICK(reply_arg);												break;
    }
	
	return (reply);
}

void Server::send_reply(int client_socket, uint16_t rpl, std::vector<std::string> const  &reply_arg) 
{
	std::string message = wich_rpl(client_socket, rpl, reply_arg) + "\r\n";

    if (send(client_socket, message.c_str(), message.length(), 0) == -1)
		return ;
}