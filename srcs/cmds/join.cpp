/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:39:05 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/08 18:53:56 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::add_client(int client_socket, Channel *channel, std::vector<std::string> &reply_arg)
{
	channel->add_client_to_chan(_clients[client_socket]);
	_clients[client_socket]->add_chan_to_client(channel);
	
	std::vector <Client*> cpy = channel->get_clients_of_chan();
	for (size_t i = 0; i <  cpy.size(); ++i)
		send_reply(cpy[i]->get_socket(), 2222, reply_arg);
	
	reply_arg.push_back(channel->get_topic());
	send_reply(client_socket, 332, reply_arg);
	reply_arg.erase(reply_arg.begin() + 3);
}

std::map<std::string, std::string>	Server::create_channel_map(int client_socket, std::vector<std::string> &s_command, std::vector<std::string> &reply_arg)
{
	std::map<std::string, std::string> channel_key_map;
	std::vector<std::string> potential_new_channels = split(s_command[1], ',');
	
    if (s_command.size() >= 3)
	{
        std::vector<std::string> v_key = split(s_command[2], ',');
		
        for (size_t i = 0; i < potential_new_channels.size(); ++i)
            channel_key_map[potential_new_channels[i]] = v_key[i]; //x
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
	
	reply_arg.push_back(s_command[0]);
	reply_arg.push_back(_clients[client_socket]->get_prefix());
	
	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg)); 
	else if (s_command.size() < 2) //!=2 && !=3
		return (send_reply(client_socket, 461, reply_arg));

	std::map<std::string, std::string> channel_key_map = create_channel_map(client_socket, s_command, reply_arg);
		
	/* Check if the channel already exist and add client if exist */
	for (std::map<std::string, std::string>::iterator it = channel_key_map.begin(); it != channel_key_map.end(); it++)
	{
		bool found = false;
		
		reply_arg.push_back(it->first);
		for (size_t i = 0; i < _channels.size(); ++i)
		{
			if (it->first == _channels[i]->get_chan_name())
			{
				std::cout << "The channel exist" << std::endl;
				found = true;
				if (_channels[i]->get_mode(1) && (int)_channels[i]->get_clients_of_chan().size() >= _channels[i]->get_nb_max_clients()) //to test 
				{
					send_reply(client_socket, 471, reply_arg);
					break;
				}
				if (_channels[i]->get_mode(2))
				{
					//check if client in invite vector 
					
				}
				if (_channels[i]->get_mode(3) && it->second != _channels[i]->get_key())
				{
					std::cout << "The key is wrong" << std::endl;
					send_reply(client_socket, 475, reply_arg);
					break ;
				}
				add_client(client_socket, _channels[i], reply_arg);
				break ;
			}
		}
		
		//fct create new channel
		if (!found)
		{
			std::cout << "A new hannel has been created" << std::endl;
			send_reply(client_socket, 403, reply_arg);
			Channel *new_channel = new Channel(it->first, it->second);
			add_client(client_socket, new_channel, reply_arg);
			_channels.push_back(new_channel);
		}

		//fct rage_quit
		if (it->first == "#0")
		{
			std::vector<std::string> channels_name;
			std::vector<Channel*> cpy = _clients[client_socket]->get_channels_of_client();
			std::string channels_name_str = cpy[0]->get_chan_name();
			for (size_t i = 1; i < cpy.size(); ++i)
				channels_name_str += "," + cpy[i]->get_chan_name();
			channels_name.push_back("PART");
			channels_name.push_back(channels_name_str);
			part(client_socket, channels_name);
		}
		
		reply_arg.erase(reply_arg.begin() + 2);
	}
} 