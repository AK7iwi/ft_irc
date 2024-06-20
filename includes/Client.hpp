/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:16 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/20 18:41:36 by mfeldman         ###   ########.fr       */
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
		Client(int socket_fd, sockaddr_in6 const &client_addr);
		~Client();
 				
		/* Getter */
		int 					get_socket()	const;
		sockaddr_in6	const	&get_address()	const;
		std::string 	const	&get_nickname() const;
		std::string 	const	&get_username() const;
		std::string 	const	&get_realname() const;
		std::string 	const	&get_hostname() const;
		std::string		const 	&get_prefix()	const;

		/* Setter */

		void					set_prefix(); 

	private:
		int				_socket_fd;
    	sockaddr_in6	_client_addr;
		std::string 	_nickname;
		std::string 	_username;
		std::string 	_realname;
		std::string 	_hostname;
		std::string 	_prefix;
};

#endif /* CLIENT_HPP */