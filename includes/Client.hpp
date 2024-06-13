/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:16 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/13 17:15:47 by mfeldman         ###   ########.fr       */
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
		int 				get_socket() const;
		sockaddr_in6 const	&get_address() const;
		std::string	 const 	&get_buffer() const;

	private:
		int				_socket_fd;
    	sockaddr_in6	_client_addr;

		std::string 	_buffer;
};

#endif /* CLIENT_HPP */