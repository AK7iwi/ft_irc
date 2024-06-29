/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:30:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/29 14:14:55 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"
#include <vector>

class Client;

class Channel 
{
	public:
		Channel(std::string const &name);
		~Channel();

		/* Add client method */
		void					add_client(Client *client);
		
		/* Getter methods */
		
		
		std::vector<Client*> 	const	&get_client_chan() const; //test method

		
		int 				 	get_id() 			const; //no really needed for now 
		std::string 	const	&get_chan_name()	const;
		
		/* Setter methods */
		void 					set_id(int id); //no really needed for now 
		void 					set_topic(std::string const &topic);	
		
	private:
		/* Channel infos */
		std::string				_name;
		std::string 			_topic;
		std::string 			_password;
		int 					_id; //no really needed for now 

		std::vector<Client*>	_clients_chan;
};


#endif /* CHANNEL_HPP */