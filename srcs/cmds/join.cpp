/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:39:05 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/13 18:01:42 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::add_client(int client_socket, Channel *channel, std::vector<std::string> &reply_arg)
{
	channel->add_client_to_chan(_clients[client_socket]);
	_clients[client_socket]->add_chan_to_client(channel);
	
	std::vector <Client*> cpy_clients_of_chan = channel->get_clients_of_chan();
	for (size_t i = 0; i <  cpy_clients_of_chan.size(); ++i)
		send_reply(cpy_clients_of_chan[i]->get_socket(), 2222, reply_arg);
	
	reply_arg.push_back(channel->get_topic());
	send_reply(client_socket, 332, reply_arg);
	reply_arg.erase(reply_arg.begin() + 3);
}

static bool inline is_valid_prefix(std::string const &potential_new_channels)
{return (potential_new_channels[0] == '#' || potential_new_channels[0] == '&');}

std::map<std::string, std::string>	Server::create_channel_map(int client_socket, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg)
{
	std::map<std::string, std::string> channel_key_map;
	std::vector<std::string> potential_new_channels = split(s_command[1], ',');
	
    if (s_command.size() >= 3)
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
			reply_arg.erase(reply_arg.begin() + 2);
        	std::map<std::string, std::string>::iterator erase_it = it;
        	++it;
        	channel_key_map.erase(erase_it);
    	} 
		else
    		++it;
	}
	
	return (channel_key_map);
}

void	Server::join(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;
	
	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg));
	
	reply_arg.push_back(s_command[0]);
	reply_arg.push_back(_clients[client_socket]->get_prefix());
	
	if (s_command.size() < 2)
		return (send_reply(client_socket, 461, reply_arg));

	std::map<std::string, std::string> channel_key_map = create_channel_map(client_socket, s_command, reply_arg);
		
	/* Check if the channel already exist and add client if exist */
	for (std::map<std::string, std::string>::iterator it = channel_key_map.begin(); it != channel_key_map.end(); it++)
	{
		bool found = false;
		bool zero = false;
		
		if (it->first == "#0")
		{
			zero = true;
			
			// _clients[client_socket]->get_channels_of_client();
			//loop to have the chan_name
			// part(client_socket, );
		}
		//RPL 405??
		
		//if #0 check if there are others channel_name after
		reply_arg.push_back(it->first);
		for (size_t i = 0; i < _channels.size(); ++i)
		{
			if (it->first == _channels[i]->get_chan_name())
			{
				std::cout << "The channel exist" << std::endl;
				found = true;
				if (it->second != _channels[i]->get_key())
				{
					std::cout << "The key is wrong" << std::endl;
					send_reply(client_socket, 475, reply_arg);
					break ;
				}
				else if (_channels[i]->get_clients_of_chan().size() >= CLIENT_MAX) //to modify with MODE
				{
					send_reply(client_socket, 471, reply_arg);
					break;
				}
				add_client(client_socket, _channels[i], reply_arg);
				break ;
			}
		}
		
		if (!found && !zero)
		{
			std::cout << "A new hannel has been created" << std::endl;
			send_reply(client_socket, 403, reply_arg);
			Channel *new_channel = new Channel(it->first, it->second);
			add_client(client_socket, new_channel, reply_arg);
			_channels.push_back(new_channel);
		}
		reply_arg.erase(reply_arg.begin() + 2);
	}
	
	/* Test if _channels and _client_chan are correctly filled */
	std::cout << std::endl; 
	std::cout << "Test the channel name from JOIN:\n" << std::endl;
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		std::cout << "Chan name: " << _channels[i]->get_chan_name() << std::endl;
		std::cout << "Chan key: " << _channels[i]->get_key() << std::endl;
		std::vector<Client*> cpy_client_chan = _channels[i]->get_clients_of_chan();
		std::cout << "cpy_client_chan.size(): " << cpy_client_chan.size() << std::endl;
		std::cout << "Client belong to the channel:" << std::endl;
		for (size_t j = 0; j <  cpy_client_chan.size(); ++j)
        	std::cout << "Client: " << cpy_client_chan[j]->get_nickname() << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;
	// for (size_t i = 0; i < _clients.size(); ++i)
	// {
	// 	std::cout << "Channels belong to the client:" << _clients[i]->get_nickname() << std::endl;
	// 	std::vector<Channel*> cpy = _clients[i]->get_channels_of_client();
	// 	for (size_t j = 0; j <  cpy.size(); ++j)
    //     std::cout << "Channel: " << cpy[j]->get_chan_name() << std::endl;
	// 	std::cout << std::endl;
	// }
	
	std::cout << std::endl; 
	std::cout << "Next join test:\n" << std::endl;
} 