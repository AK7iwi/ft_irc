/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:59:26 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/26 18:05:45 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rpl.hpp"

// /* 001 */
// std::string	RPL_WELCOME(Client const *client, std::string const &networkname, std::string const &servername) 
// {return (":" + _servername + " 001 " + client->get_nickname() + " :Welcome to the " + _networkname + " Network, " + client->get_nickname() + "[!" + client->get_clientname() + "@" + client->get_hostname() + "]");}

// /* 002 */
// std::string	RPL_YOURHOST(Client const *client, std::string const &servername, std::string const &version) 
// {return (":" + _servername + " 002 " + client->get_nickname() + " :Your host is "+ _servername + ", running version " + _version);}

// /* 003 */
// std::string	RPL_CREATED(Client const *client, std::string const &start_time, std::string const &servername) 
// {return (":" + _servername + " 003 " + client->get_nickname() + " :This server was created " + _start_time);}

// /* 004 */
// std::string	RPL_MYINFO(Client const *client, std::string const &servername, std::string const &version) 
// {return (":" + _servername + " 004 " + client->get_nickname() + " " + _servername + " " + _version + "\n[ -k -i -o -t -l ] [ -k -o -l ]");}

/* 431 */
std::string	ERR_NONICKNAMEGIVEN(Client const *client) 
{return (client->get_prefix() + " 431 :No nickname given");}

/* 432 */
std::string	ERR_ERRONEUSNICKNAME(Client const *client, std::string const &nick)
{return (client->get_prefix() + " 432 " + nick + " :Erroneus nickname");}

/* 433 */
std::string	ERR_NICKNAMEINUSE(Client const *client, std::string const &nick)
{return (client->get_prefix() + " 433 " + nick + " :Nickname is already in use");}

/* 461 */
std::string	ERR_NEEDMOREPARAMS(Client const *client)
{return (client->get_prefix() + " 461 PASS :Not enough parameters");}

/* 462 */
std::string	ERR_ALREADYREGISTERED(Client const *client)
{return (client->get_prefix() + " 462 :You may not reregister");}

/* 464 */
std::string	ERR_PASSWDMISMATCH(Client const *client)
{return (client->get_prefix() + " 464 :Password incorrect");}

/* Personal RPL */

/* 1111 */

std::string	NEW_NICK(std::vector<std::string> const &reply_arg)
{return (reply_arg[1] + " NICK " +  reply_arg[0]);}

std::string Server::wich_rpl(int client_socket, uint16_t rpl, std::vector<std::string> const &reply_arg)
{
	std::string reply;
	
	switch (rpl)
	{
        // case   1: reply = RPL_WELCOME(_client[client_socket], _networkname, _servername);    break;
        // case   2: reply = RPL_YOURHOST(_client[client_socket], _servername, _version);       break;
        // case   3: reply = RPL_CREATED(_client[client_socket], _start_time, _servername);     break;
        // case   4: reply = RPL_MYINFO(_client[client_socket], _servername, _version);         break;

		case 431: reply = ERR_NONICKNAMEGIVEN(_clients[client_socket]);						break;
        case 432: reply = ERR_ERRONEUSNICKNAME(_clients[client_socket], reply_arg[0]);		break;
        case 433: reply = ERR_NICKNAMEINUSE(_clients[client_socket], reply_arg[0]);			break;
        case 461: reply = ERR_NEEDMOREPARAMS(_clients[client_socket]);						break;
        case 462: reply = ERR_ALREADYREGISTERED(_clients[client_socket]);           		break;
        case 464: reply = ERR_PASSWDMISMATCH(_clients[client_socket]);						break;
		
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