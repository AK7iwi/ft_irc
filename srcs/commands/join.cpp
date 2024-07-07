/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:39:05 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/07 19:01:49 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static bool inline is_valid_prefix(std::string const &potential_new_channels)
{return (potential_new_channels[0] == '#' || potential_new_channels[0] == '&');}

std::map<std::string, std::string> Server::create_channel_map(int client_socket, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg)
{
	std::map<std::string, std::string> channel_key_map;
	std::vector<std::string> potential_new_channels = split(s_command[1], ',');
	
    if (s_command.size() == 3)
	{
        std::vector<std::string> v_key = split(s_command[2], ',');
		size_t len = 0;
		
        for (; len < v_key.size() && len < potential_new_channels.size(); ++len)
            channel_key_map[potential_new_channels[len]] = v_key[len];
		for (; len < potential_new_channels.size(); ++len)
			channel_key_map[potential_new_channels[len]] = "";	
	}
	else 
		for (size_t i = 0; i < potential_new_channels.size(); ++i)
            channel_key_map[potential_new_channels[i]] = "";

	for (std::map<std::string, std::string>::iterator it = channel_key_map.begin(); it != channel_key_map.end();) 
	{
		if (!is_valid_prefix(it->first)) 
		{
			reply_arg.push_back(it->first);
			send_reply(client_socket, 476, reply_arg);
			reply_arg.erase(reply_arg.begin() + 1);
        	std::map<std::string, std::string>::iterator erase_it = it;
        	++it;
        	channel_key_map.erase(erase_it);
    	} 
		else
    		++it;
	}
	
	return (channel_key_map);
}

void Server::join(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;
	
	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg));
	
	reply_arg.push_back(s_command[0]);
	
	if (s_command.size() < 2)
		return (send_reply(client_socket, 461, reply_arg));

	std::map<std::string, std::string> channel_key_map = create_channel_map(client_socket, s_command, reply_arg);
	
	/* Check if the channel already exist and add client if exist */
	for (std::map<std::string, std::string>::iterator it = channel_key_map.begin(); it != channel_key_map.end(); it++)
	{
		bool found = false;
		reply_arg.push_back(it->first);
		for (size_t i = 0; i < _channels.size(); ++i)
		{
			if (_channels[i]->get_chan_name() == it->first)
			{
				std::cout << "Existant chan" << std::endl;
				found = true;
				if (_channels[i]->get_key() != it->second)
				{
					std::cout << "Bad key" << std::endl;
					send_reply(client_socket, 475, reply_arg);
					break ;
				}
				_channels[i]->add_client(_clients[client_socket]);
				send_reply(client_socket, 332, reply_arg);
				break ;
			}
		}
		if (!found)
		{
			std::cout << "New channel" << std::endl;
			Channel *new_channel = new Channel(it->first, it->second);
			new_channel->add_client(_clients[client_socket]);
			_channels.push_back(new_channel);
			send_reply(client_socket, 403, reply_arg);
			reply_arg.push_back(new_channel->get_topic());
			send_reply(client_socket, 332, reply_arg);
			reply_arg.erase(reply_arg.begin() + 2);
		}
		reply_arg.erase(reply_arg.begin() + 1);
	}

	/* Test if _channels and __client_chan are filled */
	std::cout << "Test the channel name:\n" << std::endl;
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		std::cout << "Chan name: " << _channels[i]->get_chan_name() << std::endl;
		std::cout << "Chan key: " << _channels[i]->get_key() << std::endl;
		std::vector<Client*> cpy_client_chan = _channels[i]->get_client_chan();
		std::cout << "cpy_client_chan.size(): " << cpy_client_chan.size() << std::endl;
		std::cout << "Client belong to the channel:" << std::endl;
		for (size_t j = 0; j <  cpy_client_chan.size(); ++j)
        	std::cout << "Client: " << cpy_client_chan[j]->get_nickname() << std::endl;
	}
	std::cout << std::endl; 
	std::cout << "Next join test:\n" << std::endl;
} 