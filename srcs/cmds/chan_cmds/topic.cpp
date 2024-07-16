/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:21:50 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/15 19:30:19 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	Server::send_topic(int client_socket, Channel *channel, std::vector<std::string> &reply_arg)
{
	std::cout << "reply_arg[2]: " << reply_arg[2] << std::endl;
	std::cout << "reply_arg[3]: " << reply_arg[3] << std::endl;
	(void)client_socket;
	std::vector <Client*> cpy_clients_of_chan = channel->get_clients_of_chan();
	for (size_t i = 0; i <  cpy_clients_of_chan.size(); ++i)
		send_reply(cpy_clients_of_chan[i]->get_socket(), 332 , reply_arg);
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
	
	std::string new_topic = "";

	if (s_command.size() >= 3) //put in send_topic 
	{
		new_topic = s_command[2];
		if (new_topic[0] == ':')
			new_topic.erase(0, 1);
		
		for (size_t i = 3; i < s_command.size(); ++i)
        	new_topic += " " + s_command[i];
	}

	bool chan_found = false;
	
	for (size_t j = 0; j < _channels.size(); ++j)
	{	
		if (s_command[1] == _channels[j]->get_chan_name())
		{
			chan_found = true;
			bool client_found = false;
				
			std::vector <Client*> cpy_clients_of_chan = _channels[j]->get_clients_of_chan();
			for (size_t k = 0; k < cpy_clients_of_chan.size(); ++k)
			{	
				if (client_socket == cpy_clients_of_chan[k]->get_socket())
				{
					client_found = true;
					reply_arg.push_back(new_topic);
					send_topic(client_socket, _channels[j], reply_arg);
					reply_arg.erase(reply_arg.begin() + 3);
					break;
				}
			}
				
			if (!client_found)
				send_reply(client_socket, 442, reply_arg);
				
			break;
		}
	}
		
	if (!chan_found)
		send_reply(client_socket, 403, reply_arg);
}