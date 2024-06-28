/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:39:05 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/28 20:08:56 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::join(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;
	std::vector<std::string>    v_new_channel;
	static uint16_t				id = 0;
	
	reply_arg.push_back(s_command[0]);
	
	if (s_command.size() < 2)
		return (send_reply(client_socket, 461, reply_arg));
		
	/* Check if the channel already exist and add client if exist */
	
	for (std::vector<std::string>::iterator it = s_command.begin() + 1; it != s_command.end(); it++)
	{
		bool found = false;
		for (std::map<int, Channel*>::iterator it2 = _channels.begin(); it2 != _channels.end(); it2++)
		{
			std::cout << "*it: " << *it << std::endl;
			std::cout << "*it2: " << it2->second->get_chan_name() << std::endl;
			std::cout << "*it2->first: " << it2->first << std::endl;
			if (it2->second->get_chan_name() == *it)
			{
				std::cout << "Enter in the cond" << std::endl;
				it2->second->add_client(_clients[client_socket]);
				found = true;
				break ;
			}
		}
		if (!found)
		{
			Channel *new_channel = new Channel(*it);
			new_channel->add_client(_clients[client_socket]);
			new_channel->set_id(id);
			std::cout << "id" << id << std::endl;
			id++;
			_channels[new_channel->get_id()] = new_channel;
			std::cout << "New chan" << std::endl;
		}
	}

	std::cout << std::endl; 
	std::cout << "Next join test:\n" << std::endl;
} 