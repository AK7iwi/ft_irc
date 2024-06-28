/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:30:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/28 19:51:35 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"
#include <map>

class Client;

class Channel 
{
	public:
		Channel(std::string const &name);
		~Channel();

		/* Add client method */
		void	add_client(Client *client);
		
		/* Getter methods */
		int 				 	get_id() const;
		std::string 	const	&get_chan_name() const;
		
		/* Setter methods */
		void 					set_id(int id);
		void 					set_topic(std::string const &topic);	
		
	private:
		std::string 				_name;
		std::string 				_topic;
		std::string 				_password;
		int 						_id;

		std::map<int, Client*> 		_clients_chan;
};


#endif /* CHANNEL_HPP */