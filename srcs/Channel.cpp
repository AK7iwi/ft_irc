/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:32:44 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/29 14:16:22 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string const &name) :
	_name(name)
{}

Channel::~Channel()
{
	// for (std::vector<Client*>::iterator it = _clients_chan.begin(); it != _clients_chan.end(); it++)
    //     delete (*it); 
    // _clients_chan.clear();
}

/* Add client method */
void 							Channel::add_client(Client *client) 			{_clients_chan.push_back(client);}

/* Getter methods */
std::vector<Client*> 	const&	Channel::get_client_chan()	const				{return (_clients_chan);}
int								Channel::get_id()			const				{return (_id);}
std::string  const&				Channel::get_chan_name()	const				{return (_name);}

/* Setter methods */
void 							Channel::set_id(int id)							{_id = id;}
void 							Channel::set_topic(std::string const &topic)	{_topic = topic;}