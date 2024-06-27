/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:39:05 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/27 20:13:59 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::join(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>	stock_channels_name;
	std::vector<std::string>    reply_arg;

	if (s_command.size() < 2)
		return (send_reply(client_socket, 431, reply_arg)); //wrong RPL
	
	for (uint8_t i = 1; i < s_command.size(); ++i)
		stock_channels_name.push_back(s_command[i]);
	
	for (std::vector<std::string>::iterator it = stock_channels_name.begin(); it != stock_channels_name.end(); it++)
	{
		for (std::map<int, Channel*>::iterator it2 = _channels.begin(); it2 != _channels.end(); it2++)
		{
			std::cout << "*it: " << *it << std::endl;
			std::cout << "Enter in the loop2" << std::endl;
			// if (it2->second->get_chan_name() == *it)  join the channel (push_back user to _clients_chan)
			std::cout << "*it2: " << it2->second->get_chan_name() << std::endl;
		}
	}
	
	//create channel (push_back channel in _channels and push_back user to _clients_chan)
}