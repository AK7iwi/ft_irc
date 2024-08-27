/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:46:24 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/27 14:55:02 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* Create topic method */
static	std::string	create_message(std::vector<std::string> &s_command)
{
	std::string message = "";
	
	if (s_command.size() >= 3) 
	{
		message = s_command[2];
		if (message[0] != ':')
			return (ERR_COLON);
		message.erase(0, 1);
		
		for (size_t i = 3; i < s_command.size(); ++i)
        	message += " " + s_command[i];
	}
	
	return (message);
}


void Server::privmsg(int client_socket, std::vector<std::string> &s_command)
{	
	std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);
	reply_arg.push_back(_clients[client_socket]->get_prefix());
	
	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg)); 
	else if (s_command.size() < 2)
		return (send_reply(client_socket, 411, reply_arg)); 
	else if (s_command.size() < 3)
		return (send_reply(client_socket, 412, reply_arg));
	
	reply_arg.push_back(s_command[1]);
	
	std::string message = create_message(s_command);
	if (message.empty())
		return (send_reply(client_socket, 412, reply_arg));

	reply_arg.push_back(message);
	
	// if (is_valid_prefix(s_command[1])) //check the buffer
	// {
		/* Check is the client is in an existing channel */
	// Channel *channel = is_client_in_a_valid_chan(client_socket, s_command[1], reply_arg);
	// if (!channel)
	// 	return (send_reply(client_socket, 404, reply_arg));
		
	// /* Send reply */
	// std::vector <Client*> cpy = channel->get_clients_of_chan();
	// for (size_t i = 0; i <  cpy.size(); ++i)
	// 	if (client_socket != cpy[i]->get_socket())
	// 		send_reply(cpy[i]->get_socket(), 6666, reply_arg);
	// return ;		
	// // }
	// else
	// {
	// 	/* Find the client and send reply if found */
	// 	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
	// 		if (s_command[1] == it->second->get_nickname())
	// 			return (send_reply(it->second->get_socket(), 6666, reply_arg));
		
	// 	/* The client doesn't exist */
	// 	return (send_reply(client_socket, 401, reply_arg));
	// }
}