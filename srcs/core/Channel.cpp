/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:32:44 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/04 20:03:17 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string const &name, std::string const &key) :
	_name(name),
	_key(key),
	_topic(NO_TOPIC),
	_mode(""),
	_param_mode("") 
	{}

Channel::~Channel() {}

/* Mode method*/
// void 							Channel::add_param_mode(std::string const &param)		{_param_mode += param;}
// void 							Channel::remove_param_mode(std::string const &param)	{_param_mode = param;}

// void 							Channel::add_channel_mode(std::string const &mode)		{_mode += mode;}
// void 							Channel::remove_channel_mode(std::string const &mode)	{_mode = mode;}

/* Channel method */
void	Channel::remove_from_chan(int client_socket)
{
	for (std::vector<Client*>::iterator it = _clients_of_chan.begin(); it != _clients_of_chan.end();)
    {
		if (client_socket == (*it)->get_socket())
			it = _clients_of_chan.erase(it);
		else
			++it;
	}
}

void	Channel::add_client_to_chan(Client *client)	{_clients_of_chan.push_back(client);}

/* Getter methods */
std::string 			const&	Channel::get_param_mode()		const 				{return (_param_mode);}
std::string 			const&	Channel::get_channel_mode()		const 				{return (_mode);}
std::string 			const&	Channel::get_topic()			const				{return (_topic);}
std::string 			const&	Channel::get_key()				const				{return (_key);}
std::vector<Client*> 	const&	Channel::get_clients_of_chan()	const				{return (_clients_of_chan);}
std::string  			const&	Channel::get_chan_name()		const				{return (_name);}

/* Setter methods */
void 							Channel::set_topic(std::string const &topic)		{_topic = topic;}