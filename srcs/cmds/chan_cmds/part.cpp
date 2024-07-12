/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:35:41 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/12 17:43:36 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::part(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);
	reply_arg.push_back(_clients[client_socket]->get_prefix());
	
	if (s_command.size() < 2)
		return (send_reply(client_socket, 461, reply_arg));
	
	
	for (size_t i = 0; i < s_command.size(); ++i)
	{	
		bool chan_found = false;
		
		for (size_t j = 0; j < _channels.size(); ++j)
		{	
			if (s_command[i] == _channels[j]->get_chan_name())
			{
				chan_found = true;
				bool client_found = false;
				
				std::vector <Client*> cpy_clients_of_chan = _channels[j]->get_clients_of_chan();
				for (size_t k = 0; k < cpy_clients_of_chan.size(); ++k)
				{	
					if (client_socket == cpy_clients_of_chan[k]->get_socket())
					{
						client_found = true;
						// fct
						_channels[j]->remove_from_chan(client_socket);
						_clients[client_socket]->leave_channel(_channels[j]);
						reply_arg.push_back(_channels[j]->get_chan_name());
						// reply_arg.push_back(message);
						//RPL 4444 loop on clients_of_chan
						reply_arg.erase(reply_arg.begin() + 2);
						
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
	}
		
	/* Test if _channels and _client_chan are correctly filled */
	std::cout << std::endl; 
	std::cout << "Test the channel name from part:\n" << std::endl;
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
	std::cout << "Channels belong to the client:" << std::endl;
	std::vector<Channel*> cpy = _clients[client_socket]->get_channels_of_client();
	for (size_t j = 0; j <  cpy.size(); ++j)
        std::cout << "Channel: " << cpy[j]->get_chan_name() << std::endl;
	
	std::cout << std::endl; 
	std::cout << "Next join test:\n" << std::endl;
}