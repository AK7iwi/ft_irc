/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:35:41 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/16 10:39:31 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	Server::leave(int client_socket, Channel *channel, std::vector<std::string> &reply_arg, std::vector<std::string> &s_command)
{	
	std::string reason = "";
	
	if (s_command.size() >= 3) 
	{
		reason = s_command[2];
		if (reason[0] != ':')
		{
			std::cerr << "You should set the reason with a "":"" before bro, be rigorous please" << std::endl;
			return ;
		}
		reason.erase(0, 1);
		
		for (size_t i = 3; i < s_command.size(); ++i)
        	reason += " " + s_command[i];
	}
	
	reply_arg.push_back(reason);
	
	std::vector <Client*> cpy_clients_of_chan = channel->get_clients_of_chan();
	for (size_t i = 0; i <  cpy_clients_of_chan.size(); ++i)
		send_reply(cpy_clients_of_chan[i]->get_socket(), 4444, reply_arg);

	reply_arg.erase(reply_arg.begin() + 3);
	
	channel->remove_from_chan(client_socket);
	_clients[client_socket]->leave_channel(channel);

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

void	Server::part(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);
	reply_arg.push_back(_clients[client_socket]->get_prefix());
	
	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg)); 
	else if (s_command.size() < 2)
		return (send_reply(client_socket, 461, reply_arg));

	std::vector<std::string> v_channels = split(s_command[1], ',');	
	
	for (size_t i = 0; i < v_channels.size(); ++i)
	{	
		bool chan_found = false;
		reply_arg.push_back(v_channels[i]);
		
		for (size_t j = 0; j < _channels.size(); ++j)
		{	
			if (v_channels[i] == _channels[j]->get_chan_name())
			{
				chan_found = true;
				bool client_found = false;
				
				std::vector <Client*> cpy_clients_of_chan = _channels[j]->get_clients_of_chan();
				for (size_t k = 0; k < cpy_clients_of_chan.size(); ++k)
				{	
					if (client_socket == cpy_clients_of_chan[k]->get_socket())
					{
						client_found = true;
						leave(client_socket, _channels[j], reply_arg, s_command);
						break;
					}
				}
				
				if (!client_found)
					send_reply(client_socket, 442, reply_arg);
				
				break;
			}
		}
		
		if (!chan_found)
			send_reply(client_socket, 403, reply_arg);

		reply_arg.erase(reply_arg.begin() + 2);
	}
}