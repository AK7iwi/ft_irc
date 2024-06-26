/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:50:12 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/26 20:49:29 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::pass(int client_socket, std::vector<std::string> &s_command)
{	
	std::vector<std::string>    reply_arg;

	reply_arg.push_back(s_command[0]);
	
	if (s_command.size() != 2)
		return (send_reply(client_socket, 461, reply_arg));
	else if (_clients[client_socket]->get_nickname() != "DEFAULT")
		return (send_reply(client_socket, 462, reply_arg));
	else if (s_command[1] != _password)
		return (send_reply(client_socket, 464, reply_arg));
	
	_clients[client_socket]->set_valid_pass();	
	std::cout << "Password OK" << std::endl;
}