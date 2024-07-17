/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:35:41 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/17 18:03:30 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	Server::leave(int client_socket, std::string &v_channel, std::vector<std::string> &reply_arg)
{	
	Channel *channel = NULL;
	
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (v_channel == _channels[i]->get_chan_name())
		{
			channel = _channels[i]; 
			break;
		}
	}
	
	// std::cout << "reply_arg[0]: " << reply_arg[0] << std::endl;
	// std::cout << "reply_arg[1]: " << reply_arg[1] << std::endl;
	// std::cout << "reply_arg[2]: " << reply_arg[2] << std::endl;
	// std::cout << "reply_arg[3]: " << reply_arg[3] << std::endl;
	
	std::vector <Client*> cpy = channel->get_clients_of_chan();
	for (size_t i = 0; i < cpy.size(); ++i)
		send_reply(cpy[i]->get_socket(), 4444, reply_arg);
	
	channel->remove_from_chan(client_socket);
	_clients[client_socket]->leave_channel(channel);

	if (!channel->get_clients_of_chan().size())
	{
		for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end();)
		{
			if (channel == (*it))
				it = _channels.erase(it);
			else 
				++it;
		}
	}
}

void	Server::part(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);
	reply_arg.push_back(_clients[client_socket]->get_prefix());
	
	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg)); 
	else if (s_command.size() < 2)
		return (send_reply(client_socket, 461, reply_arg));

	std::vector<std::string> p_channels = split(s_command[1], ',');	
	std::vector<std::string> valid_channels; 
	
	for (size_t i = 0; i < p_channels.size(); ++i)
	{	
		reply_arg.push_back(p_channels[i]);
		if (is_client_in_a_valid_chan(client_socket, p_channels[i], reply_arg))
			valid_channels.push_back(p_channels[i]);
		reply_arg.erase(reply_arg.begin() + 2); //bad RPL
	}

	std::string reason = "";
	if (s_command.size() >= 3) 
	{
		reason = s_command[2];
		if (reason[0] != ':')
		{
			std::cerr << "You should set the reason with a "":"" before bro, be rigorous please" << std::endl;
			return ;
		}
		reason.erase(0, 1);
		
		for (size_t i = 3; i < s_command.size(); ++i)
        	reason += " " + s_command[i];
	}
	
	reply_arg.push_back(reason);
	for (size_t i = 0; i < valid_channels.size(); ++i)
		leave(client_socket, valid_channels[i], reply_arg);
	reply_arg.erase(reply_arg.begin() + 3);
}