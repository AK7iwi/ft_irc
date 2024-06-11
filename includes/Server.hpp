/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:10 by mfeldman          #+#    #+#             */
/*   Updated: 2024/06/11 16:15:20 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "utils.hpp"
#include <Client.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <cstring>
#include <fcntl.h>
#include <vector>
#include <poll.h>
#include <netinet/in.h>

class Server 
{
	public:
		Server(uint16_t port, std::string const &password);
		~Server();


		// bool 	is_running;
		
		void	run();
		void	init_server();

	private:
		uint16_t 			_port;
    	std::string 		_password;
		
		/* Struct for init server */
		struct sockaddr_in6	_server_addr;

		/* Socket of the server */
		int 				_server_socket;
		
		/* Vector of fds */
		std::vector<struct pollfd> _fds;

		/* Vector of clients */ //Probably to modify
		// std::vector<Client> _clients;
		
		/* Handle client method */
		void	handle_client(int client_cocket);
		void	handle_new_connections();
		
		/* Init struct address*/
		void	init_address_structures();
    
};

#endif /* SERVER_HPP */