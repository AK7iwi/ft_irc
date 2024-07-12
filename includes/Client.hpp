/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:16 by mfeldman          #+#    #+#             */
/*   Updated: 2024/07/12 17:36:27 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Server.hpp"
#include <iostream>
#include <netinet/in.h>
#include <vector>

#define DEFAULT "DEFAULT"

class Channel;

class Client 
{
	public:
		Client(int socket_fd);
		~Client();
		
		/* Leave all channels belong to client method */
		void							leave_channel(Channel *channel);

		/* Add chan */
		void 							add_chan_to_client(Channel *channel);
		
		/* Checker */
		bool 							is_registered() const;
		bool 							is_valid_pass() const;
		
		/* Getter */
		std::vector<Channel*>	const 	&get_channels_of_client() const;
		std::string 			const 	&get_realname() const;
		std::string 			const 	&get_hostname() const;
		std::string 			const 	&get_username() const;
		std::string 			const 	&get_nickname() const;
		std::string				const 	&get_prefix()	const;
		uint16_t					  	get_socket()	const;

		/* Setter */
		void 			 				set_register();
		void 							set_valid_pass();
		void 							set_realname(std::string const &realname);
		void 							set_hostname(std::string const &hostname);
		void 							set_username(std::string const &username);
		void							set_nickname(std::string const &nickname);
		void							set_prefix();

	private:
		/* Client infos */
		int				_socket_fd;
		std::string 	_prefix;
		std::string 	_nickname;
		std::string 	_username;
		std::string 	_hostname;
		std::string 	_realname;
		bool 			_valid_pass;
		bool 			_register;

		/* Vector of channels that the client belong to */
		std::vector<Channel*>	_channels_of_client;	
};

#endif /* CLIENT_HPP */