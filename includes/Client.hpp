/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:16 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/11 16:15:06 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Server.hpp"
#include <netinet/in.h>

class Client 
{
	public:
		Client(int socket_fd, sockaddr_in6 const &client_addr);
		~Client();

		/* Getter */
		int inline					get_socket() const;
		sockaddr_in6 inline const	&get_address() const;

	private:
		int				_socket_fd;
    	sockaddr_in6	_client_addr;
    
};

#endif /* CLIENT_HPP */