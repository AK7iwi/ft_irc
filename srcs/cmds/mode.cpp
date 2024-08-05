/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:44:54 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/05 22:55:26 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool	Server::wich_modes(int client_socket, std::string &modes)
{
	bool modes_flag = 0;
	std::vector<std::string>	reply_null;
	
	uint8_t l = 0;
	uint8_t i = 0;
	uint8_t k = 0;
	uint8_t t = 0;

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
	
	if (l > 0)
	{
		std::cout << "LLL" << std::endl;
		modes_flag |= MODE_L;
	}
	if (i > 0)
	{
		std::cout << "III" << std::endl;
		modes_flag |= MODE_I;
	}
	if (k > 0)
	{
		std::cout << "KKK" << std::endl;	
		modes_flag |= MODE_K;
	}
	if (t > 0)
	{
		std::cout << "TTT" << std::endl;
		modes_flag |= MODE_T;
	}

	if (modes_flag & MODE_L)
	{
		std::cout << "Mode L" << std::endl;
		// mode_L();
	}
	if (modes_flag & MODE_I)
	{
		std::cout << "Mode I" << std::endl;
		// mode_I();
			
	}
	if (modes_flag & MODE_K)
	{
		std::cout << "Mode K" << std::endl;
		// mode_K();
	}
	if (modes_flag & MODE_T)
	{
		std::cout << "Mode T" << std::endl;
		// mode_T();
	}
	
	return (modes_flag);
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
		
		bool	modes_flag = wich_modes(client_socket, s_command[2]);
		
		if (modes_flag & MODE_L)
		{
			std::cout << "Mode L" << std::endl;
			// mode_L();
		}
		// if (modes_flag & MODE_I)
		// {
		// 	std::cout << "Mode I" << std::endl;
		// 	// mode_I();
			
		// }
		// if (modes_flag & MODE_K)
		// {
		// 	std::cout << "Mode K" << std::endl;
		// 	// mode_K();
		// }
		// if (modes_flag & MODE_T)
		// {
		// 	std::cout << "Mode T" << std::endl;
		// 	// mode_T();
		// }
		// if (modes_flag & MODE_O)
		// {
		// 	std::cout << "Mode L brother" << std::endl;
		// 	// mode_O();
			
		// }
		
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
