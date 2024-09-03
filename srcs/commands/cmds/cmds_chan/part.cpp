/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:35:41 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/03 14:30:33 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	Server::goodbye(int client_socket, Channel *channel, std::vector<std::string> &reply_arg)
{	
	/* Send reply */
	send_rpl_to_channel(channel, 4444, reply_arg);
	
	/* Leave channel */
	channel->remove_from_chan(client_socket);
	channel->remove_from_chan_operator(client_socket);
	channel->remove_from_chan_invited(client_socket);
	
	_clients[client_socket]->leave_channel(channel);

	/* Delete channel if empty */
	if (!channel->get_clients_of_chan().size())
		remove_channel(channel);
}

void	Server::handle_part(int client_socket, std::vector<std::string> potential_channels, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg)
{
	for (size_t i = 0; i < potential_channels.size(); ++i)
	{	
		reply_arg.push_back(potential_channels[i]);
		Channel *channel = is_client_in_a_valid_chan(client_socket, potential_channels[i], reply_arg); 
		if (channel)
		{
			std::string reason = create_message(s_command, 3);
			if (reason == ERR_COLON)
			{
				std::cerr << ERR_COLON << std::endl;
				return ;
			}
			reply_arg.push_back(reason);
			goodbye(client_socket, channel, reply_arg);
			reply_arg.erase(reply_arg.begin() + 3);
		}
		reply_arg.erase(reply_arg.begin() + 2);
	}
}

void	Server::part(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);
	
	if (check_prerequisites(client_socket, s_command, reply_arg))
		return ;
	
	reply_arg.push_back(_clients[client_socket]->get_prefix());
	
	std::vector<std::string> potential_channels = split(s_command[1], ',');
	
	handle_part(client_socket, potential_channels, s_command, reply_arg);
}