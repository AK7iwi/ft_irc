/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:50:16 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/25 17:03:11 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::nick(int client_socket, std::vector<std::string> &s_command)
{
	if (!_clients[client_socket]->get_valid_pass())
	{
		std::cout << "Pas bien le reuf" << std::endl;
		return ;
	}
		
	std::vector<std::string>    reply_arg;
	
	if (s_command.size() != 2)
		return (send_reply(client_socket, 431, reply_arg));
	
	reply_arg.push_back(s_command[1]);
	
	if (contains_invalid_chars(s_command[1]))
		return (send_reply(client_socket, 432, reply_arg));
	
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		if (it->second->get_nickname() == s_command[1]) 
			return (send_reply(client_socket, 433, reply_arg));
		
	_clients[client_socket]->set_nickname(s_command[1]);
	_clients[client_socket]->set_prefix();

	std::cout << "Your nickname is: " << _clients[client_socket]->get_nickname();
}