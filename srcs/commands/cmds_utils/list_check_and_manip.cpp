/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_check_and_manip.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:05:18 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/29 20:37:40 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* Send mesage to all client of a channel */

void Server::send_rpl_to_channel(Channel *channel, int rpl, std::vector<std::string> &reply_arg)
{
	std::vector <Client*> cpy = channel->get_clients_of_chan();
		for (size_t i = 0; i <  cpy.size(); ++i)
			send_reply(cpy[i]->get_socket(), rpl, reply_arg);
}

/* Check if client is operator of the channel */

bool	Server::is_client_in_operator_list(int client_socket, Channel *channel)
{
	bool is_operator = false;
	std::vector <Client*> cpy = channel->get_operator_clients_of_chan();
	for (size_t i = 0; i < cpy.size(); ++i)
		if (client_socket == cpy[i]->get_socket())
			is_operator = true;
		
	return (is_operator);
}

/* Check if client is in invite client list */

bool	Server::is_client_in_invite_list(int client_socket, Channel *channel)
{
	bool found_client = false;
	
	std::vector <Client*> cpy = channel->get_invited_clients_of_chan();
	for (size_t j = 0; j < cpy.size(); ++j)
		if (client_socket == cpy[j]->get_socket())
			found_client = true;

	return (found_client);
}

Channel*	Server::is_client_in_a_valid_chan(int client_socket, std::string &channel, std::vector<std::string> &reply_arg)
{
	Channel *null_chan = NULL;
	for (size_t i = 0; i < _channels.size(); ++i)
	{	
		if (channel == _channels[i]->get_channel_name())
		{
			std::vector <Client*> cpy = _channels[i]->get_clients_of_chan();
			for (size_t j = 0; j < cpy.size(); ++j)
				if (client_socket == cpy[j]->get_socket())
					return (_channels[i]);
			
			return (send_reply(client_socket, 442, reply_arg), null_chan);
		}
	}

	return (send_reply(client_socket, 403, reply_arg), null_chan);
}