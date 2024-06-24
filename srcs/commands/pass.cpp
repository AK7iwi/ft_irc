/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:50:12 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/24 16:20:38 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::pass(int client_socket, std::vector<std::string> &s_command)
{	
	if (s_command.size() != 2)
	{
		std::cout << "111111111111" << std::endl;
		return (send_reply(client_socket, 461));
	}
	else if (_clients[client_socket]->get_nickname() != "DEFAULT") //to test
	{
		std::cout << "22222222" << std::endl;
		return (send_reply(client_socket, 462));
	}
	else if (s_command[1] != _password)
	{
		std::cout << "333333333" << std::endl;
		return (send_reply(client_socket, 464));	
	}

	std::cout << "Password OK" << std::endl;
}