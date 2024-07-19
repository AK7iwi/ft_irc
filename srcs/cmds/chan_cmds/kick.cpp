/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:03:19 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/19 16:26:51 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	Server::kicked(int client_socket_to_kick, Channel *channel, std::vector<std::string> &reply_arg)
{
	/* Send reply */
	std::vector <Client*> cpy = channel->get_clients_of_chan();
	for (size_t i = 0; i <  cpy.size(); ++i)
		send_reply(cpy[i]->get_socket(), 5555, reply_arg); //REVIEW
	
	/* Leave channel */
	channel->remove_from_chan(client_socket_to_kick);
	_clients[client_socket_to_kick]->leave_channel(channel);

	//PART if RPL doesnt work
}

/* Create comment method */
static	std::string	create_comment(std::vector<std::string> &s_command)
{
	std::string comment = "";
	
	if (s_command.size() >= 4) 
	{
		comment = s_command[3];
		if (comment[0] != ':')
			return (ERR_COLON);
		comment.erase(0, 1);
		
		for (size_t i = 4; i < s_command.size(); ++i)
        	comment += " " + s_command[i];
	}

	return (comment);
}

void 	Server::kick(int client_socket, std::vector<std::string> &s_command)
{	
	std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);
	reply_arg.push_back(_clients[client_socket]->get_prefix());

	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg)); 
	else if (s_command.size() < 3)
		return (send_reply(client_socket, 461, reply_arg));

	reply_arg.push_back(s_command[1]);

	Channel *channel = is_client_in_a_valid_chan(client_socket, s_command[1], reply_arg);
	if (!channel)
		return ;
	
	std::vector <Client*> cpy = channel->get_clients_of_chan(); //fct 
	reply_arg.push_back(s_command[2]);
	for (size_t i = 0; i < cpy.size(); ++i)
	{
		if (s_command[2] == cpy[i]->get_nickname())
		{
			if (cpy[i]->get_socket() == client_socket)
			{
				std::cerr << "You cannot kick yourself" << std::endl;
				return ;
			}
				
			std::string comment = create_comment(s_command);
			if (comment == ERR_COLON)
			{
				std::cerr << ERR_COLON << std::endl;
				return ;
			}
			reply_arg.push_back(comment);
			return (kicked(cpy[i]->get_socket(), channel, reply_arg));
		}

	}
	
	std::cerr << "The target is not in the channel" << std::endl;
 	return (send_reply(client_socket, 441, reply_arg));
}