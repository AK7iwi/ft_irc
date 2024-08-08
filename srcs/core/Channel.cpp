/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:32:44 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/08 17:07:44 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string const &name, std::string const &key) :
	_name(name),
	_key(key),
	_topic(NO_TOPIC),
	_mode(""),
	_param_mode(""),
	_mode_l(false),
	_mode_i(false),
	_mode_k(false),
	_mode_t(false)
{}

Channel::~Channel() {}

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

bool 							Channel::get_mode(int mode_int) const		
{
	bool mode = false;
	
	switch (mode_int)
	{
		case 1: return (_mode_l); break;
		case 2: return (_mode_i); break;
		case 3: return (_mode_k); break;
		case 4: return (_mode_t); break;
	}
		
	return (mode);
}

int 						  	Channel::get_nb_max_clients()	const				{return (_nb_max_clients);}
std::string 			const&	Channel::get_topic()			const				{return (_topic);}
std::string 			const&	Channel::get_key()				const				{return (_key);}
std::vector<Client*> 	const&	Channel::get_clients_of_chan()	const				{return (_clients_of_chan);}
std::string  			const&	Channel::get_chan_name()		const				{return (_name);}

/* Setter methods */
void 							Channel::reset_mode(int mode_int)
{
	switch (mode_int)
	{
		case 1: _mode_l = false; break;
		case 2: _mode_i = false; break;
		case 3: _mode_k = false; break;
		case 4: _mode_t = false; break;
	}
}

void 							Channel::set_mode(int mode_int)
{
	switch (mode_int)
	{
		case 1: _mode_l = true; break;
		case 2: _mode_i = true; break;
		case 3: _mode_k = true; break;
		case 4: _mode_t = true; break;
	}
}


void 							Channel::set_nb_max_clients(int nb_max_clients)  	{_nb_max_clients = nb_max_clients;}
void 							Channel::set_topic(std::string const &topic)		{_topic = topic;}