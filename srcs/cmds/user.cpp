/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:50:09 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/13 17:03:41 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::user(int client_socket,  std::vector<std::string> &s_command)
{
	/* Need to set-up a nickname before */
	if (_clients[client_socket]->get_nickname() == "DEFAULT")
	{
		std::cout << "Put a nickname bro\n" << std::endl; //RPL 462
		return ;
	}

	std::vector<std::string>    reply_arg;
	reply_arg.push_back(s_command[0]);

	if (s_command.size() != 5 && s_command.size() != 6)
		return (send_reply(client_socket, 461, reply_arg));
	else if (_clients[client_socket]->is_registered())
    	return (send_reply(client_socket, 462, reply_arg));

	_clients[client_socket]->set_username(s_command[1]);
    _clients[client_socket]->set_hostname(s_command[3]);

	std::string realname = s_command[4];
	/*  <realname> should be prefixed with a colon (:) */
	if (realname[0] != ':') 
	{
		std::cout << "You should set the realname with a "":"" before bro, be rigorous please" << std::endl;
		return ;
	}
	realname.erase(0, 1);

	if (s_command.size() == 6)
		realname += " " + s_command[5];

	std::cout << "realname: " << realname << std::endl;
	if (realname.empty())
	{
		std::cout << "You should set a realname with a "":"" before bro, be rigorous please" << std::endl;
		return ;
	}

	_clients[client_socket]->set_realname(realname);
    _clients[client_socket]->set_prefix();
	_clients[client_socket]->set_register();

	std::cout << "Welcome home " << _clients[client_socket]->get_nickname() <<std::endl;

	send_reply(client_socket, 1, reply_arg);
	send_reply(client_socket, 2, reply_arg);
	send_reply(client_socket, 3, reply_arg);
	send_reply(client_socket, 4, reply_arg);
}