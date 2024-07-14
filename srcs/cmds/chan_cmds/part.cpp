/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:35:41 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/14 12:47:00 by mfeldman         ###   ########.fr       */
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
		
		std::cout << "repy_arg[0]: " << reply_arg[0] << std::endl;
		std::cout << "repy_arg[1]: " << reply_arg[1] << std::endl;
		std::cout << "repy_arg[2]: " << reply_arg[2] << std::endl;
		// std::cout << "repy_arg[3]: " << reply_arg[3] << std::endl;
		
		if (!chan_found)
		{
			std::cout << "Ca passe a la 403" << std::endl;
			send_reply(client_socket, 403, reply_arg);
		}

		reply_arg.erase(reply_arg.begin() + 2);
	}
}