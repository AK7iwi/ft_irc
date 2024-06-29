/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:39:05 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/29 14:19:54 by mfeldman         ###   ########.fr       */
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
			if (it2->second->get_chan_name() == *it)
			{
				std::cout << "Enter in an existant chan" << std::endl;
				it2->second->add_client(_clients[client_socket]);
				found = true;
				break ;
			}
		}
		if (!found)
		{
			std::cout << "New chan" << std::endl;
			Channel *new_channel = new Channel(*it);
			new_channel->add_client(_clients[client_socket]);
			new_channel->set_id(id);
			std::cout << "id" << id << std::endl;
			id++;
			_channels[new_channel->get_id()] = new_channel;
		}
	}

	/* Test for if _channels and __client_chan are filled */
	std::cout << "Test the channel name:\n" << std::endl;
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		std::cout << "Chan name: " << _channels[i]->get_chan_name() << std::endl;
		std::vector<Client*> cpy_client_chan = _channels[i]->get_client_chan();
		std::cout << "cpy_client_chan.size(): " << cpy_client_chan.size() << std::endl;
		std::cout << "Client belong to the channel:" << std::endl;
		for (size_t j = 0; j <  cpy_client_chan.size(); ++j)
        	std::cout << "Client: " << cpy_client_chan[j]->get_nickname() << std::endl;
	}
	
	std::cout << std::endl; 
	std::cout << "Next join test:\n" << std::endl;
} 