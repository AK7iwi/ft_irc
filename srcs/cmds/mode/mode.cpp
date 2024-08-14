/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:44:54 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/14 18:10:19 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool	Server::parse_mode(int client_socket, std::string &mode)
{
	std::vector<std::string>	reply_null;

	if (mode.length() != 2)
		return (false);
		
	if (mode[0] == '+')
	{
		//try to get qnd set_mode 
			
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

    if (is_valid_prefix(s_command[1]))
	{
		std::cout << "Channel mode" << std::endl;
		
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
		
		std::cout << "Modes: " << s_command[2] << std::endl;
		
		if (parse_mode(client_socket, s_command[2]))
			return (send_reply(client_socket, 501, reply_arg));
		
		std::string param_mode = "";
		
		if (s_command.size() == 4)
			param_mode = s_command[3];
			
		if (channel->get_mode(1))
			mode_L(client_socket, channel, s_command, reply_arg);
		else if (channel->get_mode(3))
			mode_K(client_socket, channel, s_command, reply_arg);
	}
	else
	{
		//review the parsing  
		std::cout << "Client mode " << std::endl;

		//check if the user is operator 
		
		// bool operator = false;
		// 	std::vector <Client*> cpy = channel->get_operator_clients_of_chan();
		// 	for (size_t i = 0; i < cpy.size(); ++i)
		// 		if (client_socket == cpy[i]->get_socket())
		// 			operator = true;

		// 	if (!operator)
		// 	//return RPL 482 
		//  	return (send_reply(client_socket, 502, reply_arg));
		
		/* Find the client and send reply if found */
		for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		{
			if (s_command[1] == it->second->get_nickname()) 
            {
				//before 
				if (s_command.size() < 3) 
					return (send_reply(client_socket, 221, reply_arg));
				else if (s_command[2] == "+i")
					return ;
				else if (s_command[2] == "+o")
				{
					// mode_O(channel, s_command, reply_arg);
					return ;
				}
				return (send_reply(client_socket, 501, reply_arg));
            }
		}
		
		/* The client doesn't exist */
		return (send_reply(client_socket, 401, reply_arg));
    }
}
