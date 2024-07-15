/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:35:41 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/15 14:36:19 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	Server::leave(int client_socket, Channel *channel, std::vector<std::string> &reply_arg)
{	
	std::vector <Client*> cpy_clients_of_chan = channel->get_clients_of_chan();
	for (size_t i = 0; i <  cpy_clients_of_chan.size(); ++i)
		send_reply(cpy_clients_of_chan[i]->get_socket(), 4444, reply_arg);
	
	channel->remove_from_chan(client_socket);
	_clients[client_socket]->leave_channel(channel);

	std::cout << "Size: " << channel->get_clients_of_chan().size() << std::endl;
	if (channel->get_clients_of_chan().size() == 0)
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
	
	if (s_command.size() < 2)
		return (send_reply(client_socket, 461, reply_arg));

	std::vector<std::string> v_channels = split(s_command[1], ',');	
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
						reply_arg.push_back(reason);
						leave(client_socket, _channels[j], reply_arg);
						reply_arg.erase(reply_arg.begin() + 3);
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

		/* Test if _channels and _client_chan are correctly filled */
	std::cout << std::endl; 
	std::cout << "Test the channel name from JOIN:\n" << std::endl;
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		std::cout << "Chan name: " << _channels[i]->get_chan_name() << std::endl;
		std::cout << "Chan key: " << _channels[i]->get_key() << std::endl;
		std::vector<Client*> cpy_client_chan = _channels[i]->get_clients_of_chan();
		std::cout << "cpy_client_chan.size(): " << cpy_client_chan.size() << std::endl;
		std::cout << "Client belong to the channel:" << std::endl;
		for (size_t j = 0; j <  cpy_client_chan.size(); ++j)
        	std::cout << "Client: " << cpy_client_chan[j]->get_nickname() << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;
	
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		std::cout << "Channels belong to the client " << it->second->get_nickname() << std::endl;
		std::vector<Channel*> cpy = it->second->get_channels_of_client();
		for (size_t l = 0; l <  cpy.size(); ++l)
    		std::cout << "Channel: " << cpy[l]->get_chan_name() << std::endl;
		std::cout << std::endl;	
	}
	
	std::cout << std::endl; 
	std::cout << "Next join test:\n" << std::endl;
}