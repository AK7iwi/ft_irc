/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:32:44 by mfeldman          #+#    #+#             */
/*   Updated: 2024/11/27 16:20:23 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string const &channel_name, std::string const &key) :
	_channel_name(channel_name),
	_key(key),
	_topic(NO_TOPIC),
	_modes(""),
	_mode_l(false),
	_mode_i(false),
	_mode_k(false),
	_mode_t(false),
	_mode_o(false)
{}

Channel::~Channel() {}

/* Remove from list */

void	Channel::remove_from_chan_invited(int client_socket)
{
	for (std::vector<Client*>::iterator it = _invited_clients_of_chan.begin(); it != _invited_clients_of_chan.end();)
    {
		if (client_socket == (*it)->get_socket())
			it = _invited_clients_of_chan.erase(it);
		else
			++it;
	}
}

void	Channel::remove_from_chan_operator(int client_socket)
{
	for (std::vector<Client*>::iterator it = _operator_clients_of_chan.begin(); it != _operator_clients_of_chan.end();)
    {
		if (client_socket == (*it)->get_socket())
			it = _operator_clients_of_chan.erase(it);
		else
			++it;
	}
}

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

/* Add to list */

void	Channel::add_operator_client_to_chan(Client *client)	{_operator_clients_of_chan.push_back(client);}
void	Channel::add_invited_client_to_chan(Client *client)		{_invited_clients_of_chan.push_back(client);}
void	Channel::add_client_to_chan(Client *client)				{_clients_of_chan.push_back(client);}

/* Checker */

bool	Channel::is_client_in_operator_list(int client_socket) const
{
	bool is_operator = false;
	
	for (size_t i = 0; i < _operator_clients_of_chan.size(); ++i)
		if (client_socket == _operator_clients_of_chan[i]->get_socket())
			is_operator = true;
		
	return (is_operator);
}

bool	Channel::is_client_in_invite_list(int client_socket) const
{
	bool found_client = false;
	
	for (size_t j = 0; j < _invited_clients_of_chan.size(); ++j)
		if (client_socket == _invited_clients_of_chan[j]->get_socket())
			found_client = true;

	return (found_client);
}

/* Getter */

bool 	Channel::get_mode(int mode_int) const		
{
	bool mode = false;
	
	switch (mode_int)
	{
		case 1: return (_mode_l); break;
		case 2: return (_mode_i); break;
		case 3: return (_mode_k); break;
		case 4: return (_mode_t); break;
		case 5: return (_mode_o); break;
	}
		
	return (mode);
}

int 						  	Channel::get_nb_max_clients()	const	{return (_nb_max_clients);}
std::string 			const&  Channel::get_channel_modes()	const	{return (_modes);}
std::string 			const&	Channel::get_topic()			const	{return (_topic);}
std::string 			const&	Channel::get_key()				const	{return (_key);}
std::vector<Client*> 	const&	Channel::get_clients_of_chan()	const	{return (_clients_of_chan);}
std::string  			const&	Channel::get_channel_name()		const	{return (_channel_name);}

/* Setter */

void 							Channel::reset_mode(int mode_int)
{
	std::string mode_to_remove;
	switch (mode_int)
	{
		case 1:
			_mode_l = false;
			mode_to_remove = "+l ";
			break;
		case 2: 
			_mode_i = false;
			mode_to_remove = "+i ";
			break;
		case 3:
			_mode_k = false;
			mode_to_remove = "+k ";
			break;
		case 4: 
			_mode_t = false;
			mode_to_remove = "+t ";
			break;
		case 5: 
			_mode_o = false;
			break;
	}
	
	size_t pos = _modes.find(mode_to_remove);
	if (pos != std::string::npos)
		_modes.erase(pos, mode_to_remove.length());
}

void 							Channel::set_mode(int mode_int)
{
	std::string new_mode;
	switch (mode_int)
	{
		case 1:
			_mode_l = true;
			new_mode = "+l ";
			break;
		case 2:
			_mode_i = true;
			new_mode = "+i ";
			break;
		case 3: 
			_mode_k = true;
			new_mode = "+k ";
			break;
		case 4:
			_mode_t = true;
			new_mode = "+t ";
			break;
		case 5:
			_mode_o = true;
			break;
	}
	
	size_t pos = _modes.find(new_mode);
	if (pos == std::string::npos)
		_modes += new_mode;
}

void 							Channel::set_key(std::string const &key)			{_key = key;}
void 							Channel::set_nb_max_clients(int nb_max_clients)  	{_nb_max_clients = nb_max_clients;}
void 							Channel::set_topic(std::string const &topic)		{_topic = topic;}