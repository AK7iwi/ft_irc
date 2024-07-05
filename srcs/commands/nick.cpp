/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:50:16 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/05 15:23:26 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static	bool	contains_invalid_chars(std::string const &nickname)
{
	if (nickname[0] == '$' || nickname[0] == ':' || nickname[0] == '#')
		return (true);

	std::string invalid_chars = " ,*?!@.";

	return (nickname.find_first_of(invalid_chars) != std::string::npos);
}

void Server::nick(int client_socket, std::vector<std::string> &s_command)
{
	if (!(_clients[client_socket]->is_valid_pass()))
	{
		std::cout << "Met un mot de passe frere\n" << std::endl; //RPL 451 
		return ;
	}
	
	std::vector<std::string>    reply_arg;
	
	if (s_command.size() != 2)
		return (send_reply(client_socket, 431, reply_arg));
	
	reply_arg.push_back(_clients[client_socket]->get_prefix());
	reply_arg.push_back(s_command[1]);
	
	if (contains_invalid_chars(s_command[1]))
		return (send_reply(client_socket, 432, reply_arg));
	
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		if (it->second->get_nickname() == s_command[1]) 
			return (send_reply(client_socket, 433, reply_arg));
	
	if (_clients[client_socket]->is_registered())
		for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
        	if (it->second->is_registered())
           		send_reply(it->first, 1111, reply_arg);

	_clients[client_socket]->set_nickname(s_command[1]);
	_clients[client_socket]->set_prefix();

	std::cout << "Your nickname is: " << _clients[client_socket]->get_nickname() << std::endl; //RPL
}