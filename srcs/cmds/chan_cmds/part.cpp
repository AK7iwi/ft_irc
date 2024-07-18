/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:35:41 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/18 16:16:03 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	Server::leave(int client_socket, Channel *channel, std::vector<std::string> &reply_arg)
{	
	/* Send reply */
	std::vector <Client*> cpy = channel->get_clients_of_chan();
	for (size_t i = 0; i < cpy.size(); ++i)
		send_reply(cpy[i]->get_socket(), 4444, reply_arg);
	
	/* Leave channel */
	channel->remove_from_chan(client_socket);
	_clients[client_socket]->leave_channel(channel);

	/* Delete chan if empty */
	if (!channel->get_clients_of_chan().size())
	{
		for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end();)
		{
			if (channel == (*it))
				it = _channels.erase(it);
			else 
				++it;
		}
	}
}

/* Find reason method */
static	std::string	create_reason(std::vector<std::string> &s_command)
{
	std::string reason = "";
	
	if (s_command.size() >= 3) 
	{
		reason = s_command[2];
		if (reason[0] != ':')
			return (ERR_COLON);
		reason.erase(0, 1);
		
		for (size_t i = 3; i < s_command.size(); ++i)
        	reason += " " + s_command[i];
	}
	
	return (reason);
}

void	Server::part(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);
	reply_arg.push_back(_clients[client_socket]->get_prefix());
	
	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg)); 
	else if (s_command.size() < 2)
		return (send_reply(client_socket, 461, reply_arg));
	
	std::vector<std::string> p_channels = split(s_command[1], ',');	
	for (size_t i = 0; i < p_channels.size(); ++i)
	{	
		reply_arg.push_back(p_channels[i]);
		Channel *channel = is_client_in_a_valid_chan(client_socket, p_channels[i], reply_arg);
	
		if (channel)
		{
			std::string reason = create_reason(s_command);
			if (reason == ERR_COLON)
			{
				std::cerr << ERR_COLON << std::endl;
				return ;
			}
			reply_arg.push_back(reason);
			leave(client_socket, channel, reply_arg);
			reply_arg.erase(reply_arg.begin() + 3);
		}
		reply_arg.erase(reply_arg.begin() + 2);
	}
}