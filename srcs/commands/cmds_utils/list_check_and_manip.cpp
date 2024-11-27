/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_check_and_manip.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:05:18 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/27 16:30:59 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool		Server::check_prerequisites(int client_socket, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg)
{
	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg), 1); 
	else if (s_command.size() < 2)
		return (send_reply(client_socket, 461, reply_arg), 1);

	return (0);
}

void		Server::send_rpl_to_channel(Channel *channel, int rpl, std::vector<std::string> &reply_arg)
{
	std::vector <Client*> cpy = channel->get_clients_of_chan();
		for (size_t i = 0; i <  cpy.size(); ++i)
			send_reply(cpy[i]->get_socket(), rpl, reply_arg);
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
	if (channel == _clients[client_socket]->get_nickname())
		return (null_chan);
	return (send_reply(client_socket, 403, reply_arg), null_chan);
}