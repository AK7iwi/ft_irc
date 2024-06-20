/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:59:26 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/20 22:13:28 by mfeldman         ###   ########.fr       */
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

/* 461 */
std::string	ERR_NEEDMOREPARAMS(Client const *client)
{return (client->get_prefix() + " 461 PASS :Not enough parameters");}

/* 462 */
std::string	ERR_ALREADYREGISTERED(Client const *client)
{return (client->get_prefix() + " 462 :You may not reregister");}

/* 464 */
std::string	ERR_PASSWDMISMATCH(Client const *client)
{return (client->get_prefix() + " 464 :Password incorrect");}


std::string Server::wich_rpl(int client_socket, uint16_t rpl, std::string &reply_arg)
{
	std::string reply;
	(void)reply_arg;
	
	switch(rpl)
	{

        // case   1: reply = RPL_WELCOME(_users[fd], _networkname, _servername);    break;
        // case   2: reply = RPL_YOURHOST(_users[fd], _servername, _version);       break;
        // case   3: reply = RPL_CREATED(_users[fd], _start_time, _servername);     break;
        // case   4: reply = RPL_MYINFO(_users[fd], _servername, _version);         break;
        case 461: reply = ERR_NEEDMOREPARAMS(_clients[client_socket]);				break;
        // case 462: reply = ERR_ALREADYREGISTERED(_users[fd]);                     break;
        case 464: reply = ERR_PASSWDMISMATCH(_clients[client_socket]);               break;
    }
	
	return (reply);
}

void Server::send_reply(int client_socket, uint16_t rpl, std::string &reply_arg) 
{
	std::string message = wich_rpl(client_socket, rpl, reply_arg) + "\r\n";

    if (send(client_socket, message.c_str(), message.length(), 0) == -1)
		return ;
}