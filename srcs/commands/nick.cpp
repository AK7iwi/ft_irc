/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:50:16 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/21 14:29:11 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::nick(int client_socket, std::string &nick)
{
	(void)client_socket;
	(void)nick;
	std::cout << "Enter into nick fct" << std::endl;
	// if (password != _password)
	// 	std::cout << "RPL" << std::endl;
}