/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:44:54 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/05 18:58:06 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool	Server::wich_modes(int client_socket, std::string &modes)
{
	bool modes_flag = 0;
	std::vector<std::string>	reply_null;
	
	uint8_t l;
	uint8_t i;
	uint8_t t;
	uint8_t k;
	
	for (size_t j = 0; j < modes.length(); ++j)
	{
		if (modes[j] == "+") //fct 
		{
			while (modes[j] != "-")
			{
				if (modes[j] == "l")
					l++;
				else if (modes[j] == "i")
					i++;
				else if (modes[j] == "t")
					t++;
				else if (modes[j] == "k")
					k++;
				else
					send_reply(client_socket, 501, reply_null);
				j++;
			}
		}
		if (modes[j] == "-") //fct 
		{
			while (modes[j] != "+")
			{
				if (modes[j] == "l")
					l--;
				else if (modes[j] == "i")
					i--;
				else if (modes[j] == "t")
					t--;
				else if (modes[j] == "k")
					k--;
				else
					send_reply(client_socket, 501, reply_null);
				j++;
			}
		}
	}

	if (l > 0)
		modes_flag |= MODE_T;
	if (i > 0)
		modes_flag |= MODE_I;
	if (t > 0)
		modes_flag |= MODE_T;
	if (k > 0)
		modes_flag |= MODE_K;
	
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
			std::cout << "Mode L brother" << std::endl;
			// mode_L();
		}
		// if (modes_flag & MODE_I)
		// 	mode_I();
		// if (modes_flag & MODE_K)
		// 	mode_K();
		// if (modes_flag & MODE_T)
		// 	mode_T();
		// if (modes_flag & MODE_O)
		// 	mode_O();
		
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
