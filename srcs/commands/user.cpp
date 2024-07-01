/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:50:09 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/20 00:23:22 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::user(int client_socket,  std::vector<std::string> &s_command)
{
	/* Need to set-up a nickname before */
	if (_clients[client_socket]->get_nickname() == "DEFAULT")
	{
		std::cout << "Met un nickname frere\n" << std::endl; //RPL 
		return ;
	}

	std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);

	if (s_command.size() != 5 && s_command.size() != 6)
		return (send_reply(client_socket, 461, reply_arg));
	else if (_clients[client_socket]->is_registered())
    	return (send_reply(client_socket, 462, reply_arg));

	_clients[client_socket]->set_username(s_command[1]);
    _clients[client_socket]->set_hostname(s_command[2]);

	std::string realname = s_command[4];

	for (size_t i = 5; i < s_command.size(); ++i)
        realname += " " + s_command[i];
	
	/*  <realname> should be prefixed with a colon (:) */
	if (realname[0] != ':') 
	{
		std::cout << "You should set the realname with a "":"" before bro, be rigorous please" << std::endl; //RPL
		return ;
	}
	realname.erase(0, 1);

	_clients[client_socket]->set_realname(realname);
    _clients[client_socket]->set_prefix();
	_clients[client_socket]->set_register();

	send_reply(client_socket, 1, reply_arg);
	send_reply(client_socket, 2, reply_arg);
	send_reply(client_socket, 3, reply_arg);
	send_reply(client_socket, 4, reply_arg);

	std::cout << "Bienvenue chez moi " << _clients[client_socket]->get_nickname() <<std::endl; //RPL
}