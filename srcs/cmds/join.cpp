/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:39:05 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/28 13:48:48 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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
	
	std::vector <Client*> cpy = channel->get_clients_of_chan();
	for (size_t i = 0; i <  cpy.size(); ++i)
		send_reply(cpy[i]->get_socket(), 2222, reply_arg);
	
	reply_arg.push_back(channel->get_topic());
	send_reply(client_socket, 332, reply_arg);
	reply_arg.erase(reply_arg.begin() + 3);
}

/* Check if modes are active and if client have acces */

bool 	Server::check_client_access(int client_socket, Channel *channel, std::string const &key, std::vector<std::string> &reply_arg)
{
	if (channel->get_mode(MODE_L) && (int)channel->get_clients_of_chan().size() >= channel->get_nb_max_clients()) 
		return (send_reply(client_socket, 471, reply_arg), false);
	else if (channel->get_mode(MODE_I) && !is_client_in_invite_list(client_socket, channel))
		return (send_reply(client_socket, 473, reply_arg), false);
	else if (channel->get_mode(MODE_K) && key != channel->get_key())
		return (send_reply(client_socket, 475, reply_arg), false);

	return (true);
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

/* Check if the channel name is valid */

static inline bool is_valid_prefix(std::string const &channel) 
{return (channel[0] == '#' || channel[0] == '&');}

/* Create a vector with the valid channels */

std::vector<std::string> Server::get_valid_channels(int client_socket, std::string const &potential_new_channels, std::vector<std::string> &reply_arg)
{
	std::vector<std::string> v_potential_new_channels = split(potential_new_channels, ',');
    std::vector<std::string> valid_channels;

    for (std::vector<std::string>::const_iterator it = v_potential_new_channels.begin(); it != v_potential_new_channels.end(); ++it)
    {
        if (is_valid_prefix(*it))
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
	
	if (!_clients[client_socket]->is_registered())
		return (send_reply(client_socket, 451, reply_arg)); 
	else if (s_command.size() < 2)
		return (send_reply(client_socket, 461, reply_arg));

	reply_arg.push_back(_clients[client_socket]->get_prefix());
	
	std::vector<std::string> valid_channels = get_valid_channels(client_socket, s_command[1], reply_arg);
	std::map<std::string, std::string> m_channel_key = create_channel_map(valid_channels, s_command);
		
	/* Check if the channel already exist and add client if exist */
	for (std::map<std::string, std::string>::iterator it = m_channel_key.begin(); it != m_channel_key.end(); it++)
	{
		bool found_chan = false;
		
		reply_arg.push_back(it->first);
		for (size_t i = 0; i < _channels.size(); ++i)
		{
			if (it->first == _channels[i]->get_channel_name())
			{
				std::cout << "Channel " << it->first << " found" << std::endl;
				
				found_chan = true;
				
				if (!check_client_access(client_socket, _channels[i], it->second, reply_arg))
					return ;
				
				add_client(client_socket, _channels[i], reply_arg);
				break ;
			}
		}
		
		if (!found_chan)
			create_new_channel(client_socket, it->first, it->second, reply_arg);
		
		// continue when part no leaks 
		// if (it->first == "#0")
		// {
		// 	std::vector<std::string> channels_name;
		// 	std::vector<Channel*> cpy = _clients[client_socket]->get_channels_of_client();
		// 	std::string channels_name_str = cpy[0]->get_channel_name();
		// 	for (size_t i = 1; i < cpy.size(); ++i)
		// 		channels_name_str += "," + cpy[i]->get_channel_name();
		// 	channels_name.push_back("PART");
		// 	channels_name.push_back(channels_name_str);
		// 	part(client_socket, channels_name);
		// }
		
		reply_arg.erase(reply_arg.begin() + 2);
	}
} 