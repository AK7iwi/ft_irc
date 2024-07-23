/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:44:54 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/23 16:25:34 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static	std::vector<std::string> wich_modes(std::string &modes)
{
	//parse s_command[2]
	std::vector<std::string>    modes;
	
}

void	Server::mode(int client_socket, std::vector<std::string> &s_command)
{
    std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);
	reply_arg.push_back(_clients[client_socket]->get_prefix());
	
	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg));
	else if (s_command.size() < 2) 
		return (send_reply(client_socket, 461, reply_arg));

    reply_arg.push_back(s_command[1]);

    if (is_valid_prefix(s_command[1]))
	{
		std::cout << "Channel mode" << std::endl;
		
		/* Check is the client is in an existing channel */
		Channel *channel = is_client_in_a_valid_chan(client_socket, s_command[1], reply_arg);
		if (!channel)
			return ;
		
		reply_arg.push_back(channel->get_channel_mode());
		reply_arg.push_back(channel->get_param_mode());
		if (s_command.size() < 3) 
			return (send_reply(client_socket, 324, reply_arg));
		reply_arg.erase(reply_arg.begin() + 3);
		reply_arg.erase(reply_arg.begin() + 4);


		std::cout << "s_command[2]: " << s_command[2] << std::endl;
		
		std::vector<std::string> modes = wich_modes(s_command[2]); //s_command
		for (size_t i = 0; i <  modes.size(); ++i)
		{
			switch (modes[i])
			{
				case "i": mode_i();										break;
				case "t": mode_t();										break;
				case "k": mode_k();										break;
				case "o": mode_o();										break;
				case "l": mode_l();										break;
				default : send_reply(client_socket, 501, reply_arg);	break;
			}
		}
		
	}
	else
	{
		std::cout << "Client mode " << std::endl;
		/* Find the client and send reply if found */
		for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		{
			if (s_command[1] == it->second->get_nickname()) 
            {
                if (it->second->get_socket() != client_socket)
				    return (send_reply(client_socket, 502, reply_arg));
				else if (s_command.size() < 3) 
					return (send_reply(client_socket, 221, reply_arg));
				else if (s_command[2] == "+i")
					return ;
				
				std::cout << "No mode for user" << std::endl;
				return (send_reply(client_socket, 501, reply_arg));
            }
		}
		
		/* The client doesn't exist */
		return (send_reply(client_socket, 401, reply_arg));
    }
}
