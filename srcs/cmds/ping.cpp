/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:59:27 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/22 22:34:34 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::ping(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);
	
	if (s_command.size() < 2)
		return (send_reply(client_socket, 461, reply_arg));

	std::cout << "PONG" << std::endl;
	
	reply_arg.push_back(s_command[1]);
	
	send_reply(client_socket, 3333, reply_arg);
}