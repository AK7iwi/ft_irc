/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:50:09 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/27 09:20:37 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::user(int client_socket, std::vector<std::string> &s_command)
{
	/* Need to set-up a nickname before */
	if (_clients[client_socket]->get_nickname() == "DEFAULT")
	{
		std::cout << "You have to set a nickname\n" << std::endl;
		return ;
	}

	std::vector<std::string>    reply_arg;
	
	if (s_command.size() != 5 && s_command.size() != 6)
	{	
		reply_arg.push_back(s_command[0]);
		return (send_reply(client_socket, 461, reply_arg));
	}
	else if (_clients[client_socket]->is_registered())
    	return (send_reply(client_socket, 462, reply_arg));

	_clients[client_socket]->set_username(s_command[1]);
    _clients[client_socket]->set_hostname(s_command[3]);

	std::string realname = s_command[4];
	/*  <realname> should be prefixed with a colon (:) */
	if (realname[0] != ':') 
	{
		std::cout << ERR_COLON << std::endl;
		return ;
	}
	realname.erase(0, 1);

	if (realname.empty())
	{
		reply_arg.push_back(s_command[0]);
		return (send_reply(client_socket, 461, reply_arg));
	}

	if (s_command.size() == 6)
		realname += " " + s_command[5];

	_clients[client_socket]->set_realname(realname);
    _clients[client_socket]->set_prefix();
	_clients[client_socket]->set_register();

	std::cout << "Welcome " << _clients[client_socket]->get_nickname() <<std::endl;

	send_reply(client_socket, 1, reply_arg);
	send_reply(client_socket, 2, reply_arg);
	send_reply(client_socket, 3, reply_arg);
	send_reply(client_socket, 4, reply_arg);
}