/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:30:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/23 11:59:58 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"
#include <vector>

#define NO_TOPIC "No topic is set"
#define NO_MODE  "No Mode"

class Client;

class Channel 
{
	public:
		Channel(std::string const &name, std::string const &key);
		~Channel();
		
		/* Remove client from chan method */
		void 							remove_from_chan(int client_socket);
		
		/* Add client to chan method */
		void							add_client_to_chan(Client *client);
		
		/* Getter methods */
		std::string 			const	&get_channel_mode()		const;
		std::string				const 	&get_topic()  			const;
		std::string 			const	&get_key()				const;
		std::vector<Client*> 	const	&get_clients_of_chan()	const; 
		std::string 			const	&get_chan_name()		const;
		
		/* Setter methods */
		void 							set_channel_mode(std::string const &mode);
		void 							set_topic(std::string const &topic);	
		
	private:
		/* Channel infos */
		std::string				_name;
		std::string 			_key;
		std::string 			_topic;
		std::string 			_channel_mode; //vector of string

		/* Vector of clients belong to the channel */
		std::vector<Client*>	_clients_of_chan;
};


#endif /* CHANNEL_HPP */