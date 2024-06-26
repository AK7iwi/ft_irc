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
	if (_clients[client_socket]->get_nickname() == "DEFAULT")
	{
		std::cout << "Met un nickname frere\n" << std::endl;
		return ;
	}
	
	std::vector<std::string>    reply_arg;
	reply_arg.push_back(s_command[0]);

	std::cout << "s_command.size()" << s_command.size() << std::endl;
	std::cout << "s_command[0]: " << s_command[0] << std::endl;
	std::cout << "s_command[1]: " << s_command[1] << std::endl;
	std::cout << "s_command[2]: " << s_command[2] << std::endl;
	std::cout << "s_command[3]: " << s_command[3] << std::endl;
	std::cout << "s_command[4]: " << s_command[4] << std::endl;
	std::cout << "s_command[5]: " << s_command[5] << std::endl;
	// std::vector<std::string>    reply_arg;

	// if (s_command.size() != 4)
	// 	return (send_reply(client_socket, 461, reply_arg));

	// _clients[client_socket]->set_username(s_command[1]);
    // _clients[client_socket]->set_realname(s_command[4]);
    // // _clients[client_socket]->set_hostname(_hostname);
    // _clients[client_socket]->set_prefix();

	// send_reply(client_socket, 1, reply_arg);
	// send_reply(client_socket, 2, reply_arg);
	// send_reply(client_socket, 3, reply_arg);
	// send_reply(client_socket, 4, reply_arg);
}