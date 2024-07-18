/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:03:19 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/18 23:30:41 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	Server::kicked(int client_socket, Channel *channel, std::vector<std::string> &reply_arg)
{
	
	// reply_arg.push_back(comment);
	
	std::vector <Client*> cpy = channel->get_clients_of_chan();
	for (size_t i = 0; i <  cpy.size(); ++i)
		send_reply(cpy[i]->get_socket(), 4444, reply_arg);
	
	reply_arg.erase(reply_arg.begin() + 3);
	(void)channel;
	(void)client_socket;
	// channel->remove_from_chan(client_socket); /
	// _clients[client_socket]->leave_channel(channel);
}

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
	reply_arg.push_back(_clients[client_socket]->get_prefix());

	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg)); 
	else if (s_command.size() < 3)
		return (send_reply(client_socket, 461, reply_arg));

	reply_arg.push_back(s_command[1]);

	Channel *channel = is_client_in_a_valid_chan(client_socket, s_command[1], reply_arg);
	if (channel)
	{
		std::vector <Client*> cpy = channel->get_clients_of_chan();
		for (size_t i = 0; i < cpy.size(); ++i)
			if (s_command[2] == cpy[i]->get_nickname())
				kicked(client_socket, channel, reply_arg);
		
		return (send_reply(client_socket, 441, reply_arg)); 
	}
	
	// std::vector<std::string> clients_list = split(s_command[2], ',')
}