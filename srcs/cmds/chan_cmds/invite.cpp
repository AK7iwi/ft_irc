/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:44:58 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/08 18:33:44 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	Server::invite(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);
	reply_arg.push_back(_clients[client_socket]->get_prefix());

	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg)); 
	else if (s_command.size() < 3)
		return (send_reply(client_socket, 461, reply_arg));

	reply_arg.push_back(s_command[2]);
	reply_arg.push_back(s_command[1]);

	Channel *channel = is_client_in_a_valid_chan(client_socket, s_command[2], reply_arg);
	if (!channel)
		return ;
	
	/* Check if the target is already in the channel */
	std::vector <Client*> cpy = channel->get_clients_of_chan();
	for (size_t i = 0; i < cpy.size(); ++i)
		if (s_command[1] == cpy[i]->get_nickname())
			return (send_reply(client_socket, 443, reply_arg));

	/* Find the socket to invite and send RPL */
	int client_to_kick;
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (s_command[1] == it->second->get_nickname())
		{
			if (client_socket == it->second->get_socket())
			{
				std::cerr << "You cannot invite yoursel, who do you think you are" << std::endl;
				return ;
			}
			client_to_kick = it->second->get_socket();
			//add client to invite channel
			send_reply(client_socket, 341, reply_arg);
			return (send_reply(client_to_kick, 341, reply_arg));
		}
	}
	
	std::cerr << "The client target doesn't exist" << std::endl;
}