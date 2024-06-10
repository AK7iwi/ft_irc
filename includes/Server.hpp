/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:10 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/10 17:55:46 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "utils.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <cstring>
#include <fcntl.h>
#include <netinet/in.h>

class Server 
{
	public:
		Server(uint16_t port, std::string const &password);
		~Server();


		void	init_server();

	private:
		uint16_t 			_port;
    	std::string 		_password;
		int 				_server_socket;
		
		struct sockaddr_in6	_server_addr;
		
		/* Init struct address*/
		
		void	init_address_structures();
    
};

#endif /* SERVER_HPP */