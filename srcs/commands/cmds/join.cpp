/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:39:05 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/03 16:45:30 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* Leave all channel */

void	Server::join_zero(int client_socket)
{
	std::vector<std::string> channels_name;
	
	std::vector<Channel*> cpy = _clients[client_socket]->get_channels_of_client();
	if (!cpy.size())
		return ;
	
	std::string channels_name_str = cpy[0]->get_channel_name();
	for (size_t i = 1; i < cpy.size(); ++i)
		channels_name_str += "," + cpy[i]->get_channel_name();
	
	channels_name.push_back("PART");
	channels_name.push_back(channels_name_str);
	part(client_socket, channels_name);
}

/* Create a new channel */

void 	Server::create_new_channel(int client_socket, std::string const &channel_name, std::string const &key, std::vector<std::string> &reply_arg)
{
	std::cout << "A new hannel has been created: " << channel_name << std::endl;
	
	send_reply(client_socket, 403, reply_arg);
	Channel *new_channel = new Channel(channel_name, key);
	add_client(client_socket, new_channel, reply_arg);
	new_channel->add_operator_client_to_chan(_clients[client_socket]);
	_channels.push_back(new_channel);
}

/* Add client to the channel */

void	Server::add_client(int client_socket, Channel *channel, std::vector<std::string> &reply_arg)
{
	channel->add_client_to_chan(_clients[client_socket]);
	_clients[client_socket]->add_chan_to_client(channel);
	
	send_rpl_to_channel(channel, 2222, reply_arg);
	
	reply_arg.push_back(channel->get_topic());
	send_reply(client_socket, 332, reply_arg);
	reply_arg.erase(reply_arg.begin() + 3);
}

/* Check if modes are active and if client have acces */

bool 	Server::check_client_access(int client_socket, Channel *channel, std::string const &key, std::vector<std::string> &reply_arg)
{
	if (channel->get_mode(MODE_L) && (int)channel->get_clients_of_chan().size() >= channel->get_nb_max_clients()) 
		return (send_reply(client_socket, 471, reply_arg), false);
	else if (channel->get_mode(MODE_I) && !channel->is_client_in_invite_list(client_socket))
		return (send_reply(client_socket, 473, reply_arg), false);
	else if (channel->get_mode(MODE_K) && key != channel->get_key())
		return (send_reply(client_socket, 475, reply_arg), false);

	return (true);
}

void	Server::handle_join(int client_socket, std::map<std::string, std::string> m_channel_key, std::vector<std::string> &reply_arg)
{
	for (std::map<std::string, std::string>::iterator it = m_channel_key.begin(); it != m_channel_key.end(); it++)
	{
		bool channel_found = false;
		
		reply_arg.push_back(it->first);
		for (size_t i = 0; i < _channels.size(); ++i)
		{
			if (it->first == _channels[i]->get_channel_name())
			{
				std::cout << "Channel " << it->first << " found" << std::endl;
				
				channel_found = true;
				
				if (!check_client_access(client_socket, _channels[i], it->second, reply_arg))
					return ;
				
				add_client(client_socket, _channels[i], reply_arg);
				break ;
			}
		}
		
		if (!channel_found)
			create_new_channel(client_socket, it->first, it->second, reply_arg);
		
		if (it->first == "#0")
			join_zero(client_socket);
		
		reply_arg.erase(reply_arg.begin() + 2);
	}
}

/* Create a map with channels and keys based on incoming commands from clients*/

std::map<std::string, std::string>	Server::create_channel_map(std::vector<std::string> const &valid_channels, std::vector<std::string> &s_command)
{	
	std::map<std::string, std::string> channel_key_map;
	
	/* If key(s) is(are) supplied */
    if (s_command.size() >= 3)
	{
        std::vector<std::string> v_key = split(s_command[2], ',');

        for (size_t i = 0; i < valid_channels.size(); ++i)
		{
			if (v_key[i] == "x")
				v_key[i] = "";
            channel_key_map[valid_channels[i]] = v_key[i];
		}
	}
	else 
		for (size_t i = 0; i < valid_channels.size(); ++i)
            channel_key_map[valid_channels[i]] = "";
	
	return (channel_key_map);
}

/* Create a vector with the valid channels */

std::vector<std::string> Server::get_valid_channels(int client_socket, std::string const &potential_new_channels, std::vector<std::string> &reply_arg)
{
	std::vector<std::string> v_potential_new_channels = split(potential_new_channels, ',');
    std::vector<std::string> valid_channels;

    for (std::vector<std::string>::const_iterator it = v_potential_new_channels.begin(); it != v_potential_new_channels.end(); ++it)
    {
        if (is_valid_prefix(*it) && (*it).size() >= 2)
            valid_channels.push_back(*it);
        else
        {
            reply_arg.push_back(*it);
            send_reply(client_socket, 476, reply_arg);
            reply_arg.erase(reply_arg.begin() + 2);
        }
    }

    return (valid_channels);
}

void	Server::join(int client_socket, std::vector<std::string> &s_command)
{
	std::vector<std::string>    reply_arg;
	
	reply_arg.push_back(s_command[0]);
	
	if (check_prerequisites(client_socket, s_command, reply_arg))
		return ;
	
	reply_arg.push_back(_clients[client_socket]->get_prefix());
	
	std::vector<std::string> valid_channels = get_valid_channels(client_socket, s_command[1], reply_arg);
	std::map<std::string, std::string> m_channel_key = create_channel_map(valid_channels, s_command);
		
	/* Check if the channel already exist and add client if exist */
	handle_join(client_socket, m_channel_key, reply_arg);
}