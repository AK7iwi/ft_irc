/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:32:44 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/28 12:48:04 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string const &name) :
	_name(name)
{}

Channel::~Channel() {}

/* Add client method */
void Channel::add_client(Client *client)
{_clients_chan[client->get_socket()] = client;}


/* Getter methods */

std::string  const&	Channel::get_chan_name()	const				{return (_name);}

/* Setter methods */

void 				Channel::set_topic(std::string const &topic)	{_topic = topic;}