/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:30:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/07 20:16:06 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"
#include <vector>
#include <stdint.h>

#define NO_TOPIC "No topic is set"
#define NO_MODE  "No Mode"

class Client;

class Channel 
{
	public:
		Channel(std::string const &name, std::string const &key);
		~Channel();
		
		/* Mode method */
		void 							add_param_mode(std::string const &param);
		void 							remove_param_mode(std::string const &param);
		
		void 							add_channel_mode(std::string const &mode);
		void 							remove_channel_mode(std::string const &mode);
		
		/* Channel method  */
		void 							remove_from_chan(int client_socket);
		void							add_client_to_chan(Client *client);
		
		/* Getter methods */
		int 						  	get_nb_max_clients()		const;
		bool 							get_mode(int mode)			const;			
		std::string				const	&get_param_mode()			const;
		std::string 			const	&get_channel_modes()		const;
		std::string				const 	&get_topic()  				const;
		std::string 			const	&get_key()					const;
		std::vector<Client*>	const	&get_clients_of_chan()		const; 
		std::string 			const	&get_chan_name()			const;
		
		/* Setter methods */
		void 							reset_mode(bool _mode);
		void 							set_mode(bool _mode);
		void 							set_nb_max_clients(int nb_max_clients);
		void 							set_topic(std::string const &topic);	
		
	private:
		/* Channel infos */
		std::string					_name;
		std::string 				_key;
		std::string 				_topic;
		std::string					_mode;
		std::string 				_param_mode;
		bool 						_mode_l;
		bool 						_mode_i;
		bool 						_mode_k;
		bool 						_mode_t;
		int							_nb_max_clients;

		/* Vector of clients belong to the channel */
		std::vector<Client*>		_clients_of_chan;
		std::vector<Client*>		_invited_clients_of_chan;
};

#endif /* CHANNEL_HPP */