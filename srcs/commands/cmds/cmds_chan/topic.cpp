/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:21:50 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/02 22:26:35 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	Server::set_new_topic(int client_socket, Channel *channel, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg)
{
	/* Check if the mode is active and client can change the topic */
	if (channel->get_mode(MODE_T) && !channel->is_client_in_operator_list(client_socket))
		return (send_reply(client_socket, 482, reply_arg)); 
	
	/* Create the new topic */
	std::string new_topic = create_message(s_command, 3);
	if (new_topic == ERR_COLON)
	{
		std::cerr << ERR_COLON << std::endl;
		return ;
	}
	else if (new_topic.empty())
		new_topic = "No topic is set";

	reply_arg.push_back(new_topic);
	channel->set_topic(new_topic);
		
	send_rpl_to_channel(channel, 332, reply_arg);
}

void 	Server::return_topic(int client_socket, Channel *channel, std::vector<std::string> &reply_arg)
{
	std::string topic = channel->get_topic();
	reply_arg.push_back(topic);
	return (send_reply(client_socket, 332, reply_arg));
}

void	Server::topic(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;

	reply_arg.push_back(s_command[0]);
	
	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg)); 
	else if (s_command.size() < 2)
		return (send_reply(client_socket, 461, reply_arg));
	
	reply_arg.push_back(_clients[client_socket]->get_prefix());
	reply_arg.push_back(s_command[1]);
	
	Channel *channel = is_client_in_a_valid_chan(client_socket, s_command[1], reply_arg);
	if (!channel)
		return ;

	/* Return the actual topic */ 
	if (s_command.size() == 2)
		return (return_topic(client_socket, channel, reply_arg));
	
	set_new_topic(client_socket, channel, s_command, reply_arg);
}