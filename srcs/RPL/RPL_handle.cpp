/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_handle.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:33:52 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/03 14:34:13 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"

std::string Server::wich_rpl(Client *client, uint16_t rpl, std::vector<std::string> const &reply_arg)
{
	std::string reply;
	
	switch (rpl)
	{
		case   1: reply = RPL_WELCOME(client, _server_name, _network_name);											break;
        case   2: reply = RPL_YOURHOST(client, _server_name, _version);												break;
        case   3: reply = RPL_CREATED(client, _server_name, _start_time);											break;
        case   4: reply = RPL_MYINFO(client, _server_name, _version);												break;
		
		case 324: reply = RPL_CHANNELMODEIS(client, reply_arg[2], reply_arg[3]);									break;
		case 332: reply = RPL_TOPIC(client, reply_arg[2], reply_arg[3]);											break; 
		case 341: reply = RPL_INVITING(client, reply_arg[3], reply_arg[2]);											break; 
		
		case 401: reply = ERR_NOSUCHNICK(client, reply_arg[2]);														break;
		case 403: reply = ERR_NOSUCHCHANNEL(client, reply_arg[2]);													break;
		case 411: reply = ERR_NORECIPIENT(client);																	break;
		case 412: reply = ERR_NOTEXTTOSEND(client);																	break;
		
		case 431: reply = ERR_NONICKNAMEGIVEN(client);																break;
        case 432: reply = ERR_ERRONEUSNICKNAME(client, reply_arg[1]);												break;
        case 433: reply = ERR_NICKNAMEINUSE(client, reply_arg[1]);													break;

		case 441: reply = ERR_USERNOTINCHANNEL(client, reply_arg[3], reply_arg[2]);									break; 
		case 442: reply = ERR_NOTONCHANNEL(client, reply_arg[2]);													break; 
		case 443: reply = ERR_USERONCHANNEL(client, reply_arg[3], reply_arg[2]);									break; 
		
		case 451: reply = ERR_NOTREGISTERED(client);																break;
		
        case 461: reply = ERR_NEEDMOREPARAMS(client, reply_arg[0]);													break;
        case 462: reply = ERR_ALREADYREGISTERED(client);           													break;
        case 464: reply = ERR_PASSWDMISMATCH(client);																break;
		
		case 471: reply = ERR_CHANNELISFULL(client, reply_arg[2]);													break; 
		case 473: reply = ERR_INVITEONLYCHAN(client, reply_arg[2]);													break;
		case 475: reply = ERR_BADCHANNELKEY(client, reply_arg[2]);													break;
		case 476: reply = ERR_BADCHANMASK(client, reply_arg[2]);													break;

		case 482: reply = ERR_CHANOPRIVSNEEDED(client, reply_arg[2]);												break; 

		case 501: reply = ERR_UMODEUNKNOWNFLAG(client);																break;

		case 696: reply = ERR_INVALIDMODEPARAM(client, reply_arg[2], reply_arg[3], reply_arg[4], reply_arg[5]);		break;
		
		case 1111: reply = NEW_NICK(reply_arg[0], reply_arg[1]);													break; 
		case 2222: reply = NEW_MEMBER(reply_arg[1], reply_arg[2]);													break; 
		case 3333: reply = RPL_PONG(_server_name, reply_arg[1]);													break; 
		case 4444: reply = GOODBYE(reply_arg[1], reply_arg[2], reply_arg[3]);										break;
		case 5555: reply = GET_OUT_OF_HERE(reply_arg[1], reply_arg[2], reply_arg[3], reply_arg[4]); 				break; 
		case 6666: reply = MSGS(reply_arg[1], reply_arg[2], reply_arg[3]); 											break; 
    }
	
	return (reply);
}

void Server::send_reply(int client_socket, uint16_t rpl, std::vector<std::string> const &reply_arg) 
{
	std::string message = wich_rpl(_clients[client_socket], rpl, reply_arg) + "\r\n";

    if (send(client_socket, message.c_str(), message.length(), 0) == -1)
		return ;
}