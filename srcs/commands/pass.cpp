/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:50:12 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/25 13:58:04 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::pass(int client_socket, std::vector<std::string> &s_command)
{	
	if (s_command.size() != 2)
		return (send_reply(client_socket, 461));
	else if (_clients[client_socket]->get_nickname() != "DEFAULT") //to test
		return (send_reply(client_socket, 462));
	else if (s_command[1] != _password)
		return (send_reply(client_socket, 464));	

	std::cout << "Password OK" << std::endl;
}