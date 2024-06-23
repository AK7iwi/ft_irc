/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:50:12 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/23 18:03:41 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::pass(int client_socket, std::string &password)
{	
	// std::cout << "password: " << password << std::endl;
	if (password.empty() == 0)
	{
		std::cout << "111111111111" << std::endl;
		// send_reply(client_socket, 461);
	}
	else if (_clients[client_socket]->get_nickname() != "DEFAULT")
	{
		std::cout << "22222222" << std::endl;
		// send_reply(client_socket, 462);
		
	}
	else if (password != _password)
	{
		std::cout << "333333333" << std::endl;
		// send_reply(client_socket, 464);	
		
	}
	// std::cout << "ouiiiiiii" << std::endl;
}