/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:39:05 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/28 14:53:36 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::join(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;
	std::vector<std::string>    v_new_channel;
	
	reply_arg.push_back(s_command[0]);
	
	if (s_command.size() < 2)
		return (send_reply(client_socket, 461, reply_arg));
	
	/* Check if the channel already exist and add client if exist */
	for (std::vector<std::string>::iterator it = s_command.begin() + 1; it != s_command.end(); it++)
	{
		if (_channels.empty())
			v_new_channel.push_back(*it);
		
		for (std::map<int, Channel*>::iterator it2 = _channels.begin(); it2 != _channels.end(); it2++)
		{
			std::cout << "*it_second_loop: " << *it << std::endl;
			std::cout << "*it2: " << it2->second->get_chan_name() << std::endl;
			if (it2->second->get_chan_name() == *it)
			{
				std::cout << "Enter in the cond" << std::endl;
				it2->second->add_client(_clients[client_socket]);
			}
			else 
				v_new_channel.push_back(*it);
		}
	}
	
	std::cout << "v_new_channel.size(): " << v_new_channel.size() << std::endl;
	/* Create channel and add client. The channel have the same id as its creator Client */
	for (uint8_t i = 0; i < v_new_channel.size(); ++i)
	{
		std::cout << "v_new_channel[i]: " << v_new_channel[i] << std::endl;
		Channel * new_channel = new Channel(v_new_channel[i]);
		new_channel->add_client(_clients[client_socket]);
		_channels[client_socket] = new_channel;
	}
	std::cout << std::endl; 
	std::cout << "Next join test:\n" << std::endl;
} 