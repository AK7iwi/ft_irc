/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:44:54 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/22 15:28:30 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool	Server::parse_mode(int client_socket, std::string &mode)
{
	std::vector<std::string>	reply_null;

	std::cout << "Modes: " << mode << std::endl;

	if (mode.length() != 2)
		return (false);
		
	if (mode[0] == '+')
	{
		
	}
	else if (mode[0] == '-')
	{
		
	}
	else
		return (false);
}

//map to have mode with param mode 

void	Server::mode(int client_socket, std::vector<std::string> &s_command)
{
    std::vector<std::string>    reply_arg;

	reply_arg.push_back(s_command[0]);
	
	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg));
	else if (s_command.size() < 2)
		return (send_reply(client_socket, 461, reply_arg));

	reply_arg.push_back(_clients[client_socket]->get_prefix());
    reply_arg.push_back(s_command[1]);

	/* Check is the client is in an existing channel */
	Channel *channel = is_client_in_a_valid_chan(client_socket, s_command[1], reply_arg);
	if (!channel)
		return ;
		
	/* Return modes and parameters of channel */
	if (s_command.size() < 3)
	{
		reply_arg.push_back(channel->get_channel_modes());
		reply_arg.push_back(channel->get_channel_params_modes());
		return (send_reply(client_socket, 324, reply_arg));
	}
	
	//return the mode 
	if (parse_mode(client_socket, s_command[2]))
		return (send_reply(client_socket, 501, reply_arg));
	
	std::string param_mode = "";
		
	if (s_command.size() == 4)
		param_mode = s_command[3];
			
	//switch 
	if () 
		mode_L(client_socket, channel, s_command, reply_arg);
	else if () //false 
		mode_K(client_socket, channel, s_command, reply_arg);
		
}
