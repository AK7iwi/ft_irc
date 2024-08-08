/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:44:54 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/08 18:52:19 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::vector<int>	Server::parse_modes(int client_socket, std::string &modes)
{
	std::cout << "Modes: " << modes << std::endl;
	
	/* Parse the modes*/
	std::vector<std::string>	reply_null;
	
	int	l = 0, i = 0, k = 0, t = 0;

	for (size_t j = 0; j < modes.length(); ++j)
	{
		if (modes[j] == '+')
		{
			j++;
			for (; j < modes.length() && modes[j] != '-' ; ++j) 
			{
				switch (modes[j])
				{
					case 'l': l++; break;
					case 'i': i++; break;
					case 'k': k++; break;
					case 't': t++; break;
					default: send_reply(client_socket, 501, reply_null);
				}
			}	
		}
		if (modes[j] == '-')
		{
			j++;
			for (; j < modes.length() && modes[j] != '+' ; ++j)
			{
				switch (modes[j]) 
				{
					case 'l': l--; break;
					case 'i': i--; break;
					case 'k': k--; break;
					case 't': t--; break;
					default: send_reply(client_socket, 501, reply_null);
				}
			}
		}
	}
	
	/* Fill the vector */
	std::vector<int> modes_vector;
	
	modes_vector.push_back(l);
	modes_vector.push_back(i);
	modes_vector.push_back(k);
	modes_vector.push_back(t);

	return (modes_vector);	
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
		//fct channel mode 
		std::cout << "Channel mode" << std::endl;
		
		/* Check is the client is in an existing channel */
		Channel *channel = is_client_in_a_valid_chan(client_socket, s_command[1], reply_arg);
		if (!channel)
			return ;
		
		// reply_arg.push_back(channel->get_channel_modes());
		// reply_arg.push_back(channel->get_param_mode());
		
		// if (s_command.size() < 3) 
		// 	return (send_reply(client_socket, 324, reply_arg));
		
		// reply_arg.erase(reply_arg.begin() + 3);
		// reply_arg.erase(reply_arg.begin() + 4);

		std::cout << "s_command[2]: " << s_command[2] << std::endl;
		
		std::vector<int> modes_vector = parse_modes(client_socket, s_command[2]);
		
		for (size_t i = 0; i < modes_vector.size(); ++i)
		{
			if (modes_vector[i] > 0)
				channel->set_mode(i + 1);
			else if (modes_vector[i] < 0)
				channel->reset_mode(i + 1);
		}
		
		if (channel->get_mode(1))
			mode_L(channel, s_command);
		if (channel->get_mode(2))
			mode_I();

		if (channel->get_mode(3))
		{
			std::cout << "Mode K" << std::endl;
			// mode_K();
		}
		if (channel->get_mode(4))
		{
			std::cout << "Mode T" << std::endl;
			// mode_T();
		}
		
		//Check active flag of modes_flag
	}
	else
	{
		//fct user mode 
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
				else if (s_command[2] == "+o")
					return ;
					
				std::cout << "No mode for user" << std::endl;
				return (send_reply(client_socket, 501, reply_arg));
            }
		}
		
		/* The client doesn't exist */
		return (send_reply(client_socket, 401, reply_arg));
    }
}
