/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:30:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/08/27 16:37:51 by mfeldman         ###   ########.fr       */
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
		
		/* Channel method  */
		void		remove_from_list(int client_socket, std::vector <Client*> list);
		void							remove_from_chan_operator(int client_socket);
		void 							remove_from_chan(int client_socket);
		void							add_operator_client_to_chan(Client *client);
		void							add_invited_client_to_chan(Client *client);
		void							add_client_to_chan(Client *client);
		
		/* Getter methods */
		std::vector<Client*>	const	&get_operator_clients_of_chan()	const;
		std::vector<Client*>	const	&get_invited_clients_of_chan()	const;
		int 						  	get_nb_max_clients()			const;
		bool 							get_mode(int mode)				const;			
		std::string				const	&get_channel_params_modes()		const;
		std::string 			const	&get_channel_modes()			const;
		std::string				const 	&get_topic()  					const;
		std::string 			const	&get_key()						const;
		std::vector<Client*>	const	&get_clients_of_chan()			const; 
		std::string 			const	&get_channel_name()				const;
		
		/* Setter methods */
		void 							set_key(std::string const &key);			
		void 							reset_mode(int mode_int);
		void 							set_mode(int mode_int);
		void 							set_nb_max_clients(int nb_max_clients);
		void 							set_topic(std::string const &topic);
		
	private:
		/* Channel infos */
		std::string					_channel_name;
		std::string 				_key;
		std::string 				_topic;
		std::string					_modes;
		std::string 				_params_modes;
		bool 						_mode_l;
		bool 						_mode_i;
		bool 						_mode_k;
		bool 						_mode_t;
		bool 						_mode_o;
		int							_nb_max_clients;

		/* Vector of clients belong to the channel */
		std::vector<Client*>		_clients_of_chan;
		std::vector<Client*>		_invited_clients_of_chan;
		std::vector<Client*>		_operator_clients_of_chan;
};

#endif /* CHANNEL_HPP */