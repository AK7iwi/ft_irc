/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:44:54 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/25 03:29:46 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::handle_modes(int client_socket, Channel *channel, int8_t mode, std::string &param_mode, std::vector<std::string> &reply_arg)
{
	if (mode == 2)
		mode_L(client_socket, channel, mode, param_mode, reply_arg);
	else if (mode == 4)
		mode_I(channel, mode);
	else if (mode == 6)
		mode_K(client_socket, channel, mode, param_mode, reply_arg);
	else if (mode == 8)
		mode_T(channel, mode);
	else if (mode == 9 || mode == 10)
		mode_O(client_socket, channel, mode, param_mode, reply_arg);
}

int8_t	Server::parse_mode(std::string &mode)
{
	std::cout << "Modes: " << mode << std::endl;
	
	std::vector<std::string>	reply_null;
	uint8_t mode_int;

	if (mode.length() != 2)
		return (-1);
	else if (mode[0] != '+' && mode[0] != '-')
		return (-2);
	
	switch (mode[1])
	{
		case 'l': mode_int = 1; break;
		case 'i': mode_int = 3; break;
		case 'k': mode_int = 5; break;
		case 't': mode_int = 7; break;
		case 'o': mode_int = 9; break;
	}
		
	if (mode[0] == '+')
		mode_int++;
	
	return (mode_int);
}

void	Server::mode(int client_socket, std::vector<std::string> &s_command)
{
    std::vector<std::string>    reply_arg;

	reply_arg.push_back(s_command[0]);
	
	if (check_prerequisites(client_socket, s_command, reply_arg))
		return ;

	reply_arg.push_back(_clients[client_socket]->get_prefix());
    reply_arg.push_back(s_command[1]);
	
	Channel *channel = is_client_in_a_valid_chan(client_socket, s_command[1], reply_arg);
	if (!channel)
		return ;
	
	/* Return modes of channel */
	if (s_command.size() < 3)
	{
		reply_arg.push_back(channel->get_channel_modes());
		return (send_reply(client_socket, 324, reply_arg));
	}
	
	if (!channel->is_client_in_operator_list(client_socket))
		return (send_reply(client_socket, 482, reply_arg));
	
	int8_t mode = parse_mode(s_command[2]);
	if ((mode < 0))
		return (send_reply(client_socket, 501, reply_arg));
	else if (mode % 2 && mode != 9)
		return (channel->reset_mode((mode + 1) / 2));
	
	std::string param_mode = "";
	
	if (s_command.size() == 4)
		param_mode = s_command[3];
	
	handle_modes(client_socket, channel, mode, param_mode, reply_arg);
}
