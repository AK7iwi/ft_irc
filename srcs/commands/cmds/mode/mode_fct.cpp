// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   mode_fct.cpp                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/08 17:45:32 by mfeldman          #+#    #+#             */
// /*   Updated: 2024/08/23 15:14:49 by mfeldman         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "Server.hpp"

void Server::mode_O(int client_socket, Channel *channel, uint8_t mode, std::string &param_mode, std::vector<std::string> &reply_arg)
{
	std::cout << "Mode O" << std::endl;

	reply_arg.push_back("+o");
	reply_arg.push_back(param_mode);

	/* Check that the client target is already in the chan and not operator */

	bool found_client = false;
	int client_socket_operator;
	
	std::vector <Client*> cpy = channel->get_clients_of_chan();
	for (size_t j = 0; j < cpy.size(); ++j)
	{
		if (param_mode == cpy[j]->get_nickname())
		{
			found_client = true;		
			client_socket_operator = cpy[j]->get_socket();
		}
	}
	if (!found_client)
	{
		reply_arg.push_back("Client target is not in the channel");
		return (send_reply(client_socket, 696, reply_arg));
	}

	bool found_operator = false;
	std::vector <Client*> cpy2 = channel->get_operator_clients_of_chan();
	for (size_t j = 0; j < cpy2.size(); ++j)
		if (client_socket_operator == cpy2[j]->get_socket())
			found_operator = true;
	
	if (mode == 9)
	{
		if (!found_operator)
		{
			reply_arg.push_back("Targte is alreday not opeator");
			return (send_reply(client_socket, 696, reply_arg)); 
		}
		channel->remove_from_chan_operator(client_socket_operator);
	}
	else if (mode == 10)
	{
		if (found_operator)
		{
			reply_arg.push_back("Target is already operator");
			return (send_reply(client_socket, 696, reply_arg)); 
		}
		channel->add_operator_client_to_chan(_clients[client_socket_operator]);
	}
	
	channel->set_mode(mode / 2);
}

void Server::mode_T(Channel *channel, uint8_t mode)
{
	std::cout << "Mode T" << std::endl;

	channel->set_mode(mode / 2);
}

void Server::mode_K(int client_socket, Channel *channel, uint8_t mode, std::string &param_mode, std::vector<std::string> &reply_arg)
{
	std::cout << "Mode K" << std::endl;
	
	reply_arg.push_back("+k");
	reply_arg.push_back(param_mode); 
	
	if (!param_mode.length())
	{
		reply_arg.push_back("Put a key bro");
		return (send_reply(client_socket, 696, reply_arg));
	}
	
	if (param_mode == "x")
	{
		reply_arg.push_back("You cannot use 'x' as key");
		return (send_reply(client_socket, 696, reply_arg));
	}
	
	channel->set_mode(mode / 2);
	channel->set_key(param_mode);
}

void Server::mode_I(Channel *channel, uint8_t mode)
{
	std::cout << "Mode I" << std::endl;
	
	channel->set_mode(mode / 2);
}

void Server::mode_L(int client_socket, Channel *channel, uint8_t mode, std::string &param_mode, std::vector<std::string> &reply_arg)
{
	std::cout << "Mode L" << std::endl;
	
	reply_arg.push_back("+l");
	reply_arg.push_back(param_mode);
	 
	if (!param_mode.length())
	{
		reply_arg.push_back("Put a limit bro");
		return (send_reply(client_socket, 696, reply_arg));
	}
	//test with alpha parameter 
	
    int nb_max_clients;
	
	std::istringstream iss(param_mode);
    iss >> nb_max_clients;
		
	if (nb_max_clients < 0)
	{
		reply_arg.push_back("Client limit can be negative or empty");
		return (send_reply(client_socket, 696, reply_arg));
	}
	
	channel->set_mode(mode / 2);
	channel->set_nb_max_clients(nb_max_clients);
}