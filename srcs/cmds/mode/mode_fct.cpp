/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_fct.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:45:32 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/08 18:26:05 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::mode_L(Channel *channel, std::vector<std::string> &s_command)
{
	std::cout << "Mode L" << std::endl;
    int nb_max_clients;
			
	if (s_command.size() >= 4)
	{
		std::istringstream iss(s_command[3]);
    	iss >> nb_max_clients;
	}
	else 
		nb_max_clients = CLIENT_MAX;
	
	channel->set_nb_max_clients(nb_max_clients);
}

void Server::mode_I()
{
	std::cout << "Mode I" << std::endl;
	
}

void Server::mode_K()
{
	
}

void Server::mode_T()
{
	
}