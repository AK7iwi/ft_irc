/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:30:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/07 18:31:45 by mfeldman         ###   ########.fr       */
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
		Channel(std::string const &name, std::string const &key);
		~Channel();

		/* Add client method */
		void							add_client(Client *client);
		
		/* Getter methods */
		std::string				const 	&get_topic()  const;
		std::string 			const	&get_key()	const;
		std::vector<Client*> 	const	&get_client_chan() const; 
		std::string 			const	&get_chan_name()	const;
		
		/* Setter methods */
		// void 							set_topic(std::string const &topic);	
		
	private:
		/* Channel infos */
		std::string				_name;
		std::string 			_key;
		std::string 			_topic;

		/* Vector of clients belong to the channel */
		std::vector<Client*>	_clients_chan;
};


#endif /* CHANNEL_HPP */