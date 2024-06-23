/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:50:12 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/23 17:21:47 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::pass(int client_socket, std::string &password)
{	
	(void)client_socket;
	if (password != _password)
	{
		send_reply(client_socket, 464, _void_str);	
	}
}