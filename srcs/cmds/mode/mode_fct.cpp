/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_fct.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:45:32 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/14 15:50:24 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::mode_L(int client_socket, Channel *channel, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg)
{
	std::cout << "Mode L" << std::endl;
	
    int nb_max_clients;
	
	//check if its a number 
	if (s_command.size() == 4)
	{
		std::istringstream iss(s_command[3]);
    	iss >> nb_max_clients;
		
		if (nb_max_clients < 0)
		{
			reply_arg.push_back("l");
			reply_arg.push_back(s_command[3]); // not exactly correct
			reply_arg.push_back("Client limit can be negative");
			return (send_reply(client_socket, 696, reply_arg));
		}
	}
	else 
		nb_max_clients = CLIENT_MAX;
	
	channel->set_nb_max_clients(nb_max_clients);
}

void Server::mode_K(int client_socket, Channel *channel, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg)
{
	std::cout << "Mode K" << std::endl;
	
	if (s_command.size() == 4)
	{
		if (s_command[3] == "x")
		{
			reply_arg.push_back("k");
			reply_arg.push_back(s_command[3]); // not exactly correct
			reply_arg.push_back("You cannot use x as key");
			return (send_reply(client_socket, 696, reply_arg));
		}
		
		channel->set_key(s_command[3]);
	}
}

// void Server::mode_O(Channel *channel, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg)
// {
// 	std::cout << "Mode O" << std::endl;
	
// }