/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:44:58 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/03 14:30:42 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	Server::handle_invite(int client_socket, Channel *channel, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg)
{
	if (channel->get_mode(MODE_I) && !channel->is_client_in_operator_list(client_socket))
		return (send_reply(client_socket, 482, reply_arg));
	
	/* Check if the target is already in the channel */
	reply_arg.push_back(s_command[1]);
	std::vector <Client*> cpy = channel->get_clients_of_chan();
	for (size_t i = 0; i < cpy.size(); ++i)
		if (s_command[1] == cpy[i]->get_nickname())
			return (send_reply(client_socket, 443, reply_arg));

	/* Find the socket to invite and send RPL */
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (s_command[1] == it->second->get_nickname())
		{
			if (client_socket == it->second->get_socket())
			{
				std::cerr << "You cannot invite yoursel, who do you think you are" << std::endl;
				return ;
			}
			
			int client_to_invite = it->second->get_socket();
			channel->add_invited_client_to_chan(_clients[client_to_invite]);
			send_reply(client_socket, 341, reply_arg);
			return (send_reply(client_to_invite, 341, reply_arg));
		}
	}
	
	std::cerr << "The client target doesn't exist" << std::endl;
}

void 	Server::invite(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);

	if (check_prerequisites(client_socket, s_command, reply_arg))
		return ;

	reply_arg.push_back(_clients[client_socket]->get_prefix());
	reply_arg.push_back(s_command[2]);

	Channel *channel = is_client_in_a_valid_chan(client_socket, s_command[2], reply_arg);
	if (!channel)
		return ;
	
	handle_invite(client_socket, channel, s_command, reply_arg);
}