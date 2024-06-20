/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:16 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/20 21:10:00 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Server.hpp"
#include <iostream>
#include <netinet/in.h>

class Client 
{
	public:
		Client(int socket_fd);
		~Client();
 				
		/* Getter */
		int 					get_socket()	const;
		std::string 	const	&get_nickname() const;
		std::string 	const	&get_username() const;
		std::string 	const	&get_realname() const;
		std::string 	const	&get_hostname() const;
		std::string		const 	&get_prefix()	const;

		/* Setter */

		void					set_prefix(); 

	private:
		int				_socket_fd;
		std::string 	_nickname;
		std::string 	_username;
		std::string 	_realname;
		std::string 	_hostname;
		std::string 	_prefix;
};

#endif /* CLIENT_HPP */