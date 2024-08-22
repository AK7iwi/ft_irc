/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_fct.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:45:32 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/22 19:14:15 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


void Server::set_or_reset(Channel *channel, uint8_t mode)
{
	if (mode % 2)
		channel->set_mode(mode);
	else 
		channel->reset_mode(mode - 1)
	
}

void Server::mode_L(int client_socket, Channel *channel, uint8_t mode, std::string &param_mode, std::vector<std::string> &reply_arg)
{
	std::cout << "Mode L" << std::endl;
	
    int nb_max_clients;
	
	//set, reset 
	//check if its a number, if empty 
	std::istringstream iss(param_mode);
    iss >> nb_max_clients;
		
	if (nb_max_clients < 0)
	{
		reply_arg.push_back("l");
		reply_arg.push_back(param_mode); // not exactly correct
		reply_arg.push_back("Client limit can be negative");
		return (send_reply(client_socket, 696, reply_arg));
	}
	// }
	// else 
	// 	nb_max_clients = CLIENT_MAX;
	
	channel->set_nb_max_clients(nb_max_clients);
}

void Server::mode_K(int client_socket, Channel *channel, uint8_t mode, std::string &param_mod, std::vector<std::string> &reply_arg)
{
	std::cout << "Mode K" << std::endl;
	
	if (param_mode == "x")
	{
		reply_arg.push_back("k");
		reply_arg.push_back(param_mode); // not exactly correct
		reply_arg.push_back("You cannot use x as key");
		return (send_reply(client_socket, 696, reply_arg));
	}
		
	channel->set_key(param_mode);
}

// void Server::mode_O(Channel *channel, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg)
// {
// 	std::cout << "Mode O" << std::endl;
	
// }