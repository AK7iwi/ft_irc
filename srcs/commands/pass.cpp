/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:50:12 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/25 16:52:38 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::pass(int client_socket, std::vector<std::string> &s_command)
{	
	if (s_command.size() != 2)
		return (send_reply(client_socket, 461, s_command));
	else if (_clients[client_socket]->get_nickname() != "DEFAULT")
		return (send_reply(client_socket, 462, s_command));
	else if (s_command[1] != _password)
		return (send_reply(client_socket, 464, s_command));

	_clients[client_socket]->set_valid_pass();	
	std::cout << "Password OK" << std::endl;
}