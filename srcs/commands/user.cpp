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
	std::cout << "Enter into user fct" << std::endl;
	(void)client_socket;
	(void)s_command;
	// if (password != _password)
	// 	std::cout << "RPL" << std::endl;
}