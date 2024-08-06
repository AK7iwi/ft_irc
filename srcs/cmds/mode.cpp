/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:44:54 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/06 23:37:45 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
//refacto
void	Server::wich_modes(int client_socket, std::string &modes, Channel *channel)
{
	std::vector<std::string>	reply_null;
	
	uint8_t l = 0, i = 0, k = 0, t = 0;

	std::cout << "Modes: " << modes << std::endl;
		
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
	
	std::vector<int> modes;
	modes.push_back();
	if (l > 0)
		channel->set_mode(channel->get_mode("l"));
	else if (l < 0)
		channel->reset_mode(channel->get_mode("l"));
	if (i > 0)
		channel->set_mode(channel->get_mode_i);
	else if (i < 0)
		channel->reset_mode(channel->get_mode_i);
	if (k > 0)
		channel->set_mode(channel->get_mode_k);
	else if (k < 0)
		channel->reset_mode(channel->get_mode_k);
	if (t > 0)
		channel->set_mode(channel->get_mode_t);
	else if (t < 0)
		channel->reset_mode(channel->get_mode_t);
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
		
		reply_arg.push_back(channel->get_channel_modes());
		reply_arg.push_back(channel->get_param_mode());
		
		if (s_command.size() < 3) 
			return (send_reply(client_socket, 324, reply_arg));
		
		reply_arg.erase(reply_arg.begin() + 3);
		reply_arg.erase(reply_arg.begin() + 4);

		std::cout << "s_command[2]: " << s_command[2] << std::endl;
		
		wich_modes(client_socket, s_command[2], channel);
		
		if (channel->get_mode("l"))
		{
			std::cout << "Mode L" << std::endl;
			std::istringstream iss(s_command[3]);
    		int nb_max_clients;
    		iss >> nb_max_clients;
			channel->set_nb_max_clients(nb_max_clients);
		}
		if (channel->get_mode("i"))
		{
			std::cout << "Mode I" << std::endl;
			// mode_I();
			
		}
		if (channel->get_mode("k"))
		{
			std::cout << "Mode K" << std::endl;
			// mode_K();
		}
		if (channel->get_mode("t"))
		{
			std::cout << "Mode T" << std::endl;
			// mode_T();
		}
		
		//Check active flag of modes_flag
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
