/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:21:50 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/19 12:23:06 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* Create topic method */
static	std::string	create_topic(std::vector<std::string> &s_command)
{
	std::string new_topic = s_command[2];
	if (new_topic[0] != ':')
		return (ERR_COLON);
	new_topic.erase(0, 1);
		
	for (size_t i = 3; i < s_command.size(); ++i)
        new_topic += " " + s_command[i];
		
	if (new_topic.empty())
		new_topic = "No topic is set";
	
	return (new_topic);
}

void	Server::topic(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;

	reply_arg.push_back(s_command[0]);
	reply_arg.push_back(_clients[client_socket]->get_prefix());
	
	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg)); 
	else if (s_command.size() < 2)
		return (send_reply(client_socket, 461, reply_arg));
	
	reply_arg.push_back(s_command[1]);
	
	Channel *channel = is_client_in_a_valid_chan(client_socket, s_command[1], reply_arg);
	if (channel)
	{
		std::string new_topic = "";

		if (s_command.size() == 2)
		{
			new_topic = channel->get_topic();
			reply_arg.push_back(new_topic);
			return (send_reply(client_socket, 332, reply_arg));
		}
		
		new_topic = create_topic(s_command);
		if (new_topic == ERR_COLON)
		{
			std::cerr << ERR_COLON << std::endl;
			return ;
		}

		reply_arg.push_back(new_topic);
		channel->set_topic(new_topic);
		
		/* Send reply */
		std::vector <Client*> cpy = channel->get_clients_of_chan();
		for (size_t i = 0; i < cpy.size(); ++i)
			send_reply(cpy[i]->get_socket(), 332, reply_arg);
	}
}