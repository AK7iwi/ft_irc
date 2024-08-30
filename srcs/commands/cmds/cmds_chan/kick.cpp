/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:03:19 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/30 17:15:44 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	Server::kicked(int client_socket_to_kick, Channel *channel, std::vector<std::string> &reply_arg)
{
	/* Send reply */
	send_rpl_to_channel(channel, 5555, reply_arg);
	
	/* Leave channel */
	channel->remove_from_chan(client_socket_to_kick);
	channel->remove_from_chan_operator(client_socket_to_kick);
	channel->remove_from_chan_invited(client_socket_to_kick);

	_clients[client_socket_to_kick]->leave_channel(channel);
}

void 	Server::kick(int client_socket, std::vector<std::string> &s_command)
{	
	std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);

	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg)); 
	else if (s_command.size() < 3)
		return (send_reply(client_socket, 461, reply_arg));

	reply_arg.push_back(_clients[client_socket]->get_prefix());
	reply_arg.push_back(s_command[1]);

	Channel *channel = is_client_in_a_valid_chan(client_socket, s_command[1], reply_arg);
	if (!channel)
		return ;
	
	if (!channel->is_client_in_operator_list(client_socket))
		return (send_reply(client_socket, 482, reply_arg)); 
	
	std::vector<std::string> clients_to_kick = split(s_command[2], ',');
	std::vector <Client*> cpy = channel->get_clients_of_chan(); 
	
	for (size_t i = 0; i < clients_to_kick.size(); ++i)
	{
		bool client_to_kick = false;
		reply_arg.push_back(clients_to_kick[i]);
		
		for (size_t j = 0; j < cpy.size(); ++j)
		{
			if (clients_to_kick[i] == cpy[j]->get_nickname())
			{
				client_to_kick = true;
				if (cpy[j]->get_socket() == client_socket)
				{
					std::cerr << "You cannot kick yourself" << std::endl;
					break ;
				}
				
				std::string comment = create_message(s_command, 4);
				if (comment == ERR_COLON)
				{
					std::cerr << ERR_COLON << std::endl;
					return ;
				}
				reply_arg.push_back(comment);
				kicked(cpy[j]->get_socket(), channel, reply_arg);
				reply_arg.erase(reply_arg.begin() + 4);
			}
		}
		
		if (!client_to_kick)
			send_reply(client_socket, 441, reply_arg);
		
		reply_arg.erase(reply_arg.begin() + 3);
	}
}