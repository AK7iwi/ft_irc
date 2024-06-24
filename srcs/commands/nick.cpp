/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:50:16 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/24 15:27:30 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::nick(int client_socket, std::vector<std::string> &s_command)
{
	(void)client_socket;
	(void)s_command;
	std::cout << "Enter into nick fct" << std::endl;
	// if (password != _password)
	// 	std::cout << "RPL" << std::endl;
}