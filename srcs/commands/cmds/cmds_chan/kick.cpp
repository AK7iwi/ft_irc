/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:03:19 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/29 19:59:07 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	Server::kicked(int client_socket_to_kick, Channel *channel, std::vector<std::string> &reply_arg)
{
	/* Send reply */
	std::vector <Client*> cpy = channel->get_clients_of_chan();
	for (size_t i = 0; i <  cpy.size(); ++i)
		send_reply(cpy[i]->get_socket(), 5555, reply_arg);
	
	/* Leave channel */

	//print before 
	std::cout << "Before:\n" << std::endl;
	std::vector <Client*> cpy2 = channel->get_clients_of_chan();
	std::cout << "Size: " << cpy2.size() << std::endl;
	for (size_t i = 0; i < cpy2.size(); ++i)
		std::cout << "Nickname:" << cpy2[i]->get_nickname() << std::endl;
	
	// channel->remove_from_chan(client_socket_to_kick);
	channel->remove_from_list(client_socket_to_kick, channel->get_clients_of_chan());

	//print after 
	std::cout << "After:\n" << std::endl;
	std::vector <Client*> cpy3 = channel->get_clients_of_chan();
	std::cout << "Size: " << cpy3.size() << std::endl;
	for (size_t i = 0; i < cpy3.size(); ++i)
		std::cout << "Nickname:" << cpy3[i]->get_nickname() << std::endl;

	_clients[client_socket_to_kick]->leave_channel(channel);
}

/* Create comment method */
static	std::string	create_comment(std::vector<std::string> &s_command)
{
	std::string comment = "";
	
	if (s_command.size() >= 4) 
	{
		comment = s_command[3];
		if (comment[0] != ':')
			return (ERR_COLON);
		comment.erase(0, 1);
		
		for (size_t i = 4; i < s_command.size(); ++i)
        	comment += " " + s_command[i];
	}

	return (comment);
}

void 	Server::kick(int client_socket, std::vector<std::string> &s_command)
{	
	std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);

	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg)); 
	else if (s_command.size() < 3)
		return (send_reply(client_socket, 461, reply_arg));

	reply_arg.push_back(_clients[client_socket]->get_prefix());
	reply_arg.push_back(s_command[1]);

	Channel *channel = is_client_in_a_valid_chan(client_socket, s_command[1], reply_arg);
	if (!channel)
		return ;
	
	//split and loop on s_command[2]
	reply_arg.push_back(s_command[2]);
	
	//check if client is operator, rpl 482
	
	std::vector <Client*> cpy = channel->get_clients_of_chan(); 
	for (size_t i = 0; i < cpy.size(); ++i)
	{
		if (s_command[2] == cpy[i]->get_nickname())
		{
			if (cpy[i]->get_socket() == client_socket)
			{
				std::cerr << "You cannot kick yourself" << std::endl;
				return ;
			}
			//check if target not operator
			std::string comment = create_comment(s_command);
			if (comment == ERR_COLON)
			{
				std::cerr << ERR_COLON << std::endl;
				return ;
			}
			reply_arg.push_back(comment);
			kicked(cpy[i]->get_socket(), channel, reply_arg);
		}

	}
	
	std::cerr << "The target is not in the channel" << std::endl;
 	return (send_reply(client_socket, 441, reply_arg));
}